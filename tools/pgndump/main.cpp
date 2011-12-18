/**
 * Copyright (C) 2010-2012 Nikita Manovich <nikita.manovich@gmail.com>
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

#include <pgn/parser.hpp>

#include <cstdlib>
#include <iostream>
#include <boost/intrusive_ptr.hpp>

#ifdef _WIN32
#define ucerr wcerr
#define _U(X) L##X
int wmain(int argc, wchar_t* argv[])
#else
#define ucerr cerr
#define _U(X) X
int main(int argc, char* argv[])
#endif
{
    if (argc < 2)
    {
        std::ucerr << _U("Usage: ") << argv[0] << _U(" <pgnfile>") << std::endl;
        return EXIT_FAILURE;
    }

    boost::intrusive_ptr<pgn::IParser> pgnparser;
    pgnparser = pgn::IParser::create(argv[1]);

    if (pgnparser == NULL)
    {
        std::ucerr << _U("Critical error: can't open ") << argv[1] <<
            _U(" file") << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
