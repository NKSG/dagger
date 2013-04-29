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
#include <dagger/algorithm/gamma/base.h>


namespace dagger {
namespace algorithm {
namespace gamma {


struct rgb
{
    double r_gamma;
    double g_gamma;
    double b_gamma;

    rgb()
      : r_gamma(1)
      , g_gamma(1)
      , b_gamma(1)
    {
    }

    data::rgb operator()(const data::rgb& s)
    {
        data::rgb d;

        d.r = calculate(s.r, r_gamma);
        d.g = calculate(s.g, g_gamma);
        d.b = calculate(s.b, b_gamma);

        return d;
    }
};

}}}
