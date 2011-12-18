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

#ifndef PGN_REF_OBJECT_IMPL_HPP
#define PGN_REF_OBJECT_IMPL_HPP

#include <pgn/ref_object.hpp>
#ifndef PGN_LIB_SINGLE_THREAD
#include <boost/thread/mutex.hpp>
#endif

namespace pgn
{

template <typename T>
class RefObject : public T
{
public:
    RefObject() : m_counter(0) {}

    unsigned addRef()
    {
#ifndef PGN_LIB_SINGLE_THREAD
        boost::mutex::scoped_lock lock(m_mutex);
#endif
        return ++m_counter;
    }

    unsigned release()
    {
        if ( _release() == 0 )
        {
            delete this;
            return 0;
        }

        return m_counter;
    }

protected:
    unsigned _release()
    {
#ifndef PGN_LIB_SINGLE_THREAD
        boost::mutex::scoped_lock lock(m_mutex);
#endif
        return --m_counter;
    }

private:
    unsigned m_counter;
#ifndef PGN_LIB_SINGLE_THREAD
    boost::mutex m_mutex;
#endif
};

} /* namespace pgn */

#endif /* #ifndef PGN_REF_OBJECT_IMPL_HPP */

