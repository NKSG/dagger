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

#include <dagger/algorithm/levels/base.h>


namespace dagger {
namespace algorithm {
namespace levels {


struct rgb : public unary<data::rgb>::function
{
    int32_t r_input_low, r_input_high;
    int32_t g_input_low, g_input_high;
    int32_t b_input_low, b_input_high;

    int32_t r_output_low, r_output_high;
    int32_t g_output_low, g_output_high;
    int32_t b_output_low, b_output_high;

    rgb()
      : r_input_low(0), r_input_high(channel::max_value)
      , g_input_low(0), g_input_high(channel::max_value)
      , b_input_low(0), b_input_high(channel::max_value)
      , r_output_low(0), r_output_high(channel::max_value)
      , g_output_low(0), g_output_high(channel::max_value)
      , b_output_low(0), b_output_high(channel::max_value)
    {
    }

    data::rgb operator()(const data::rgb& s)
    {
        data::rgb d;

        d.r = levels::calculate(s.r, r_input_low, r_input_high, r_output_low, r_output_high);
        d.g = levels::calculate(s.g, g_input_low, g_input_high, g_output_low, g_output_high);
        d.b = levels::calculate(s.b, b_input_low, b_input_high, b_output_low, b_output_high);

        return d;
    }
};

}}}
