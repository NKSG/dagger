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
namespace levels {


int32_t calculate(int32_t v, int32_t input_low, int32_t input_high, int32_t output_low, int32_t output_high)
{
    int64_t _v = 0;

    _v = static_cast<int64_t>(v);

    _v = std::min(_v, static_cast<int64_t>(input_high));
    _v = std::max(_v, static_cast<int64_t>(input_low));

    _v -= input_low;

    _v = _v * (output_high - output_low);

    if (input_high - input_low != 0)
        _v /= (input_high - input_low);

    _v += output_low;

    v = static_cast<int32_t>(_v);

    assert(v >= 0 && v <= channel::max_value);

    return v;
}


channel calculate(const channel& c, int32_t input_low, int32_t input_high, int32_t output_low, int32_t output_high)
{
    assert(c.empty() == false);

    assert(input_low >= 0 && input_low <= channel::max_value);
    assert(input_high >= 0 && input_high <= channel::max_value);

    assert(output_low >= 0 && output_low <= channel::max_value);
    assert(output_high >= 0 && output_high <= channel::max_value);

    assert(input_high >= input_low);
    assert(output_high >= output_low);

    channel d(c.width(), c.height());

    const int32_t* _c = c.data().get();

    int32_t* _d = d.data().get();

    int32_t image_size = c.image_size();

    for (int32_t i = 0; i < image_size; i++)
    {
        int64_t v = _c[i];

        assert(v >= 0 && v <= channel::max_value);

        _d[i] = calculate(v, input_low, input_high, output_low, output_high);
    }

    return d;
}

}}}
