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


int32_t calculate(int32_t v, int32_t input_low, int32_t input_span, int32_t output_low, int32_t output_span)
{
    v -= input_low;

    v = std::max(v, 0);
    v = std::min(v, input_span);

    v = static_cast<int64_t>(v) * output_span / input_span;

    v += output_low;

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

    int32_t input_span = input_high - input_low;
    int32_t output_span = output_high - output_low;

    if (input_span == 0)
        input_span = 1;

    for (int32_t i = 0; i < image_size; i++)
        _d[i] = calculate(_c[i], input_low, input_span, output_low, output_span);

    return d;
}

}}}
