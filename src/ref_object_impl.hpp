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

#include "ref_object.hpp"
#include <boost/thread/mutex.hpp>

namespace pgn
{

void intrusive_ptr_add_ref(IRefObject* obj)
{
    obj->addRef();
}

void intrusive_ptr_release(IRefObject* obj)
{
    obj->release();
}

template <typename T>
class RefObject : public T
{
public:
    RefObject() : m_counter(0) {}

    unsigned addRef()
    {
        boost::mutex::scoped_lock lock(m_mutex);
        return ++m_counter;
    }

    unsigned release()
    {
        boost::mutex::scoped_lock lock(m_mutex);
        if ( --m_counter == 0 )
        {
            delete this;
            return 0;
        }

        return m_counter;
    }

private:
    unsigned m_counter;
    boost::mutex m_mutex;
};

} /* namespace pgn */

#endif /* #ifndef PGN_REF_OBJECT_IMPL_HPP */

