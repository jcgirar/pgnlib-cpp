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

#ifndef PGN_LIB_REF_OBJECT_HPP
#define PGN_LIB_REF_OBJECT_HPP

#include "export_decl.hpp"

namespace pgn
{

class PGN_LIB_API IRefObject
{
public:
    virtual unsigned addRef() = 0;
    virtual unsigned release() = 0;

protected:
    virtual ~IRefObject() {}
};

void intrusive_ptr_add_ref(IRefObject* object)
{
    object->addRef();
}

void intrusive_ptr_release(IRefObject* object)
{
    object->release();
}

} /* namespace pgn */

#endif /* #ifndef PGN_LIB_REF_OBJECT_HPP */

