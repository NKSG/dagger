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
namespace scale {


channel calculate(const channel& c, int16_t new_width, int16_t new_height)
{
    assert(c.empty() == false);
    
    channel d(new_width, new_height);
    
    channel v(3, 3);
    
    int32_t* data = v.data().get();
    
    int16_t old_width = c.width();
    int16_t old_height = c.height();
    
    for (int16_t y = 0; y < new_height; y++)
    {
        int16_t source_y = static_cast<int64_t>(y) * old_height / new_height;
        
        for (int16_t x = 0; x < new_width; x++)
        {
            int16_t source_x = static_cast<int64_t>(x) * old_width / new_width;

            v.view(c, source_x-1, source_y-1);

            int64_t value = std::accumulate(data, data + 9, static_cast<int64_t>(0));

            d.set_value(x, y, value / 9);
        }
    }

    return d;
}

}}}
