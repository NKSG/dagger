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


channel apply_alpha(const channel& c1, const channel& c2, const channel& alpha)
{
    if (c1.height() != c2.height())
        throw channel::invalid_channel_error();

    if (c1.width() != c2.width())
        throw channel::invalid_channel_error();

    if (alpha.empty() == true)
        return channel(c1);

    channel d(c1.height(), c1.width());
    int32_t image_size = c1.height() * c1.width();

    const int32_t* _c1 = c1.data().get();
    const int32_t* _c2 = c2.data().get();
    const int32_t* _a = alpha.data().get();

    int32_t* _d = d.data().get();
        
    for (int32_t i = 0; i < image_size; i++)
    {
        int64_t v1 = _c1[i];
        int64_t v2 = _c2[i];
        int64_t a = _a[i];

        assert(v1 > 0);
        assert(v2 > 0);
        assert(a > 0);

        _d[i] = (v1 * a + v2 * (channel::max_value - a)) / channel::max_value;
    }

    return d;
}

}}
