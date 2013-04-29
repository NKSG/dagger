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
namespace threshold {


int32_t calculate(int32_t v, int32_t threshold)
{
    if (v >= threshold)
        v = channel::max_value;
    else
        v = 0;

    return v;
}


channel calculate(const channel& c, int32_t threshold)
{
    assert(c.empty() == false);

    assert(threshold >= 0 && threshold <= channel::max_value);

    channel d(c.width(), c.height());

    const int32_t* _c = c.data().get();

    int32_t* _d = d.data().get();

    int32_t image_size = c.image_size();

    for (int32_t i = 0; i < image_size; i++)
        _d[i] = calculate(_c[i], threshold);

    return d;
}

}}}
