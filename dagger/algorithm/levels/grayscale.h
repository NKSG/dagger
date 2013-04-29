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


#include <dagger/data/rgb.h>
#include <dagger/algorithm/levels/base.h>


namespace dagger {
namespace algorithm {
namespace levels {


struct grayscale
{
    int32_t g_input_low, g_input_high;
    int32_t g_output_low, g_output_high;

    grayscale()
      : g_input_low(0)
      , g_input_high(channel::max_value)
      , g_output_low(0)
      , g_output_high(channel::max_value)
    {
    }

    data::grayscale operator()(const data::grayscale& s)
    {
        data::grayscale d;

        d.g = levels::calculate(s.g, g_input_low, g_input_high, g_output_low, g_output_high);

        return d;
    }
};

}}}
