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


channel box_scale(const channel& c, int16_t new_width, int16_t new_height)
{
    channel d(new_width, new_height);
    
    if (c.empty() == true)
        return d;

    double width_scale = static_cast<double>(c.width()) / new_width;
    double height_scale = static_cast<double>(c.height()) / new_height;

    for (int16_t y = 0; y < new_height; y++)
    {
        int16_t source_y = y * height_scale;
        
        for (int16_t x = 0; x < new_width; x++)
        {
            int16_t source_x = x * width_scale;

            int64_t value = 0;

            value += c.get_value(source_x-1, source_y-1, 0);
            value += c.get_value(source_x+0, source_y-1, 0);
            value += c.get_value(source_x+1, source_y-1, 0);
            value += c.get_value(source_x-1, source_y+0, 0);
            value += c.get_value(source_x+0, source_y+0, 0);
            value += c.get_value(source_x+1, source_y+0, 0);
            value += c.get_value(source_x-1, source_y+1, 0);
            value += c.get_value(source_x+0, source_y+1, 0);
            value += c.get_value(source_x+1, source_y+1, 0);

            d.set_value(x, y, value / 9);
        }
    }

    return d;
}

}}
