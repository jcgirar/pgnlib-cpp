/**
 * Copyright (C) 2010 Nikita Manovich <nikita.manovich@gmail.com>
 * 
 * This file is part of C++ PGN parser, http://code.google.com/p/pgnparser-cpp
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PGN_PARSER_IMPL_HPP
#define PGN_PARSER_IMPL_HPP

#include "parser.hpp"
#include "ref_object_impl.hpp"

#include <set>
#include <functional>
#include <vector>

#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/spirit/include/qi.hpp>

namespace pgn
{

/* All interface methods of the class should be protected by global lock. There
 * is no reason to introduce more complex lock strategy for the class. Its
 * methods should be called very rarely. */
class ErrorHandler
{
public:
    void setErrorHandler(IErrorHandlerCallback* callback)
    {
        boost::mutex::scoped_lock lock(m_glbSyncPoint);
        m_callback = callback;
    }

    bool operator()(bool isCritical, syntax_error_t code,
        wchar_t const* description, unsigned long long line, unsigned column)
    {
        boost::mutex::scoped_lock lock(m_glbSyncPoint);
        if ( m_callback != NULL )
        {
            if ( !isErrorReported(code, line, column) )
            {
                saveErrorReport(code, line, column);
                return (*m_callback)(isCritical, code, description, line,
                    column);
            }
        } else
        {
            return true;
        }
    }

private:
    void saveErrorReport(syntax_error_t code, unsigned long long line,
        unsigned column)
    {
        ErrorReport report(code, line, column);
        m_errorReportSet.insert(report);
    }

    bool isErrorReported(syntax_error_t code, unsigned long long line,
        unsigned column) const
    {
        ErrorReport report(code, line, column);
        return m_errorReportSet.find(report) != m_errorReportSet.end();
    }

    struct ErrorReport
    {
        ErrorReport(syntax_error_t _code, unsigned long long _line,
            unsigned _column) : code(_code), line(_line), column(_column) {}

        syntax_error_t code;
        unsigned long long line;
        unsigned column;
    };

    struct ErrorReportLess
        : public std::binary_function<ErrorReport, ErrorReport, bool>
    {
    public:
        bool operator()(ErrorReport const& lhs, ErrorReport const& rhs) const
        {
#define SIMPLE_CHECK(x, y, condition) \
    ( ( (x) < (y) ) || ( ( (x) == (y) ) && (condition) ) )
            return SIMPLE_CHECK(lhs.line, rhs.line,
               SIMPLE_CHECK(lhs.column, rhs.column, lhs.code < rhs.code));
#undef SIMPLE_CHECK
        }
    };
    typedef std::set<ErrorReport, ErrorReportLess> ErrorReportSet;
    ErrorReportSet m_errorReportSet;

    boost::mutex m_glbSyncPoint;
    boost::intrusive_ptr<IErrorHandlerCallback> m_callback;
};

namespace qi = boost::spirit::qi;

/* The grammar is used for light weight parsing of PGN file. Here we should
 * skip comments, escape (%), spaces. */
class LightWeightSkipper : public qi::grammar<char const*>
{
public:
    typedef qi::rule<char const*> RuleType;

    RuleType entryPoint; /* entry point into the grammar */
    LightWeightSkipper() : LightWeightSkipper::base_type(entryPoint)
    {
        initialize();
    }

protected:
    void initialize();

private:
    RuleType m_comment;
    RuleType m_ignoredLine;
};

/* The grammar is used for light weight parsing of PGN file. */
class LightWeightGrammar : public qi::grammar<char const*, LightWeightSkipper>
{
public:
    typedef qi::rule<char const*, LightWeightSkipper> RuleType;

    RuleType entryPoint; /* entry point into the grammar */
    LightWeightGrammar() : LightWeightGrammar::base_type(entryPoint)
    {
        initialize();
    }

protected:
    void initialize();

private:
    RuleType m_tagName;
    RuleType m_tagValue;
    RuleType m_tagPair;
    RuleType m_tagPairSection;
};

class MappedFile
{
public:
    typedef boost::iostreams::mapped_file_source::size_type size_type;
    static const size_type DEFAULT_MAPPED_SIZE = 2 * 1024 * 1024; /* 2 Mb */

    MappedFile() : m_offset() {}

    void open(std::string const& path, boost::intmax_t offset = 0,
        size_type length = DEFAULT_MAPPED_SIZE)
    {
        m_shift  = offset % m_mappedFileImpl.alignment();
        m_offset = offset - m_shift;
        m_mappedFileImpl.open(path, length + m_shift, m_offset);
    }

    void open(std::wstring const& path, boost::intmax_t offset = 0,
        size_type length = DEFAULT_MAPPED_SIZE)
    {
        m_shift  = offset % m_mappedFileImpl.alignment();
        m_offset = offset - m_shift;
    }

    void close() { m_mappedFileImpl.close(); }
    bool isOpen() const { return m_mappedFileImpl.is_open(); }
    char const* getData() const { return m_mappedFileImpl.data() + m_shift; }
    size_type getMappedSize() const { return m_mappedFileImpl.size(); }

    boost::intmax_t getOffsetInFile() const { return m_offset; }
private:
    unsigned m_shift;
    boost::intmax_t m_offset;
    boost::iostreams::mapped_file_source m_mappedFileImpl;
};

class Parser : public RefObject<IParser>
{
public:
    Parser(char const* pgnfile, bool isStrict)
    {
        initialize(pgnfile, isStrict);
    }

    Parser(wchar_t const* pgnfile, bool isStrict)
    {
        initialize(pgnfile, isStrict);
    }

    void setErrorHandler(IErrorHandlerCallback* callback)
    {
        m_errorHandler.setErrorHandler(callback);
    }

    unsigned getGameCount() const
    {
        /* It isn't critical if another thread will set the variable to true.
         * doLightWeightParsing has lock inside. */
        if ( !m_isLightweightParsingDone )
        {
            const_cast<Parser*>(this)->doLightWeightParsing();
        }

        return m_gameCount;
    }

    IGame const* readGame(unsigned gameN);

protected:
    Parser(Parser const& ); /* without implementation */
    Parser& operator=(Parser const& ); /* without implementation */

    void doLightWeightParsing(unsigned gameN = 0 /* 0 - parse till the eof */);
    template <typename T> void initialize(T const* pgnfile, bool isStrict);
    unsigned getGameInFileCacheSize() const
    {
        boost::shared_lock<boost::shared_mutex> lock(m_gameInFileCacheLock);
        return m_gameInFileCache.size();
    }

private:
    bool m_isStrict; /* is the parser strict (report about each error) */
    unsigned m_gameCount; /* number of games in the PGN file */

    typedef enum
    {
        goTagPairSection,
        goMoveTextSection,
        goGameOffsetCount
    } game_offset_t;

    /* It should be as minimal as possible because it will contain information
     * for all games in the PGN file. We should include quickhash field
     * because we want to detect cases than a requested game was changed on
     * disk. The main purpose of the field is to prevent incorrect parsing
     * of PGN file in case our cache isn't up to date. */
    struct GameInFile
    {
        unsigned quickhash; /* check that the game was not changed */
        unsigned long long offset[goGameOffsetCount];
        unsigned size; /* size of the game in bytes */
    };

    mutable boost::shared_mutex m_gameInFileCacheLock;
    MappedFile m_mappedFile; /* it is used for light weight parsing */
    bool m_isLightweightParsingDone; /* the PGN file was parsed till eof */

    std::vector<GameInFile> m_gameInFileCache;
    ErrorHandler m_errorHandler;
};

} /* namespace pgn */

#endif /* #ifndef PGN_PARSER_HPP */

