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
namespace channel_mixer {


channel calculate(const channel& c1, double c1_into_d,
                  const channel& c2, double c2_into_d,
                  const channel& c3, double c3_into_d)
{
    assert(c1.empty() == false);
    assert(c2.empty() == false);
    assert(c3.empty() == false);
    
    if (channel::equal_dimensions(c1, c2) == false)
        throw channel::different_channels_error();

    if (channel::equal_dimensions(c2, c3) == false)
        throw channel::different_channels_error();

    channel d(c1.width(), c1.height());

    const int32_t* _c1 = c1.data().get();
    const int32_t* _c2 = c2.data().get();
    const int32_t* _c3 = c3.data().get();
    
    int32_t* _d = d.data().get();

    int32_t image_size = c1.image_size();

    int64_t c1_d = c1_into_d * 1000;
    int64_t c2_d = c2_into_d * 1000;
    int64_t c3_d = c3_into_d * 1000;

    for (int32_t i = 0; i < image_size; i++)
    {
        int64_t value = 0;

        value += std::max(_c1[i] * c1_d, static_cast<int64_t>(0));
        value += std::max(_c2[i] * c2_d, static_cast<int64_t>(0));
        value += std::max(_c3[i] * c3_d, static_cast<int64_t>(0));

        value /= 1000;

        _d[i] = std::min(static_cast<int32_t>(value), channel::max_value);
    }

    return d;
}

}}}
