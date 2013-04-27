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


#include <dagger/operation.h>
#include <dagger/data/rgb.h>

#include <dagger/algorithm/value/minmax.h>
#include <dagger/algorithm/levels/base.h>


namespace dagger {
namespace algorithm {
namespace auto_levels {


struct rgb : public unary<data::rgb>::function
{
    bool adjust_individual_channels;

    rgb()
      : adjust_individual_channels(false)
    {
    }

    data::rgb operator()(const data::rgb& s)
    {
        data::rgb d;

        auto r_minmax = value::minmax(s.r);
        auto g_minmax = value::minmax(s.g);
        auto b_minmax = value::minmax(s.b);

        if (adjust_individual_channels == false)
        {
            int low = channel::max_value;

            low = std::min(low, r_minmax.first);
            low = std::min(low, g_minmax.first);
            low = std::min(low, b_minmax.first);

            r_minmax.first = low;
            g_minmax.first = low;
            b_minmax.first = low;

            int32_t high = 0;

            high = std::max(high, r_minmax.second);
            high = std::max(high, g_minmax.second);
            high = std::max(high, b_minmax.second);

            r_minmax.second = high;
            g_minmax.second = high;
            b_minmax.second = high;
        }

        d.r = levels::calculate(s.r, r_minmax.first, r_minmax.second, 0, channel::max_value);
        d.g = levels::calculate(s.g, g_minmax.first, g_minmax.second, 0, channel::max_value);
        d.b = levels::calculate(s.b, b_minmax.first, b_minmax.second, 0, channel::max_value);

        return d;
    }
};

}}}
