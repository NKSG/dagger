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
namespace alpha {


channel calculate(const channel& c1, const channel& c2, const channel& a)
{
    assert(c1.empty() == false);
    assert(c2.empty() == false);
    assert(a.empty() == false);
    
    if (channel::equal_dimensions(c1, c2) == false)
        throw channel::different_channels_error();

    if (channel::equal_dimensions(c1, a) == false)
        throw channel::invalid_alpha_channel_error();

    channel d(c1.width(), c1.height());

    const int32_t* _c1 = c1.data().get();
    const int32_t* _c2 = c2.data().get();
    const int32_t* _a = a.data().get();

    int32_t* _d = d.data().get();
    
    int32_t image_size = c1.image_size();

    for (int32_t i = 0; i < image_size; i++)
    {
        int64_t v1 = _c1[i];
        int64_t v2 = _c2[i];
        int64_t va = _a[i];

        assert(v1 >= 0);
        assert(v2 >= 0);
        assert(va >= 0);

        _d[i] = (v1 * va + v2 * (channel::max_value - va)) / channel::max_value;
    }

    return d;
}

}}}
