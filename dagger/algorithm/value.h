/*
 * Copyright (c) 2013 Hrvoje Zeba <zeba.hrvoje@gmail.com>
 *
 *    This file is part of dagger.
 *
 *    dagger is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once


#include <dagger/channel.h>


namespace dagger {
namespace algorithm {
namespace value {

int32_t calculate_source_value(int32_t source_value, int32_t source_scale)
{
    assert(source_value >= 0 && source_value <= source_scale);
    
    return (static_cast<int64_t>(source_value) * channel::max_value) / source_scale;
}

int32_t calculate_destination_value(int32_t value, int32_t destination_scale)
{
    assert(value >= 0 && value <= channel::max_value);
    
    return (static_cast<int64_t>(value) * destination_scale) / channel::max_value;
}

}}}
