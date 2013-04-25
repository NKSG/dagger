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


int32_t calculate(int32_t v1, int32_t v1_into,
                  int32_t v2, int32_t v2_into,
                  int32_t v3, int32_t v3_into)
{
        int64_t v = 0;

        v += std::max(static_cast<int64_t>(v1) * v1_into, static_cast<int64_t>(0));
        v += std::max(static_cast<int64_t>(v2) * v2_into, static_cast<int64_t>(0));
        v += std::max(static_cast<int64_t>(v3) * v3_into, static_cast<int64_t>(0));

        v /= 1000;

        assert(v >= 0 && v <= channel::max_value);

        return v;
}


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

    int32_t v1_into = c1_into_d * 1000;
    int32_t v2_into = c2_into_d * 1000;
    int32_t v3_into = c3_into_d * 1000;

    for (int32_t i = 0; i < image_size; i++)
    {
        int32_t v1 = _c1[i];
        int32_t v2 = _c2[i];
        int32_t v3 = _c3[i];

        assert(v1 >= 0 && v1 <= channel::max_value);
        assert(v2 >= 0 && v2 <= channel::max_value);
        assert(v3 >= 0 && v3 <= channel::max_value);

        _d[i] = calculate(v1, v1_into, v2, v2_into, v3, v3_into);
    }

    return d;
}

}}}
