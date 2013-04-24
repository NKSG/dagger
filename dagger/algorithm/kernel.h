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


channel kernel(const channel& c, const channel& k, bool normalize)
{
    assert(c.empty() == false);
    assert(k.empty() == false);
    
    assert(k.width() <= 8192);
    assert(k.height() <= 8129);
    
    channel d(c.width(), c.height());
    channel v(k.width(), k.height());

    const int32_t* kernel_data = k.data().get();
    const int32_t* data = v.data().get();

    int32_t kernel_size = k.image_size();

    int16_t width = c.width();
    int16_t height = c.height();

    for (int16_t y = 0; y < height; y++)
    {
        for (int16_t x = 0; x < width; x++)
        {
            v.view(c, x-1, y-1);

            int64_t value = 0;

            for (int i = 0; i < kernel_size; i++)
                value += static_cast<int64_t>(kernel_data[i]) * data[i];
            
            value /= 1000;
            
            if (normalize == true)
                value /= kernel_size;
            
            value = std::min(value, static_cast<int64_t>(channel::max_value));
            value = std::max(value, static_cast<int64_t>(0));

            d.set_value(x, y, value);
        }
    }

    return d;
}

}}
