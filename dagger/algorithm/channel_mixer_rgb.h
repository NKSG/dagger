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
#include <dagger/algorithm/channel_mixer.h>


namespace dagger {
namespace algorithm {
namespace channel_mixer {


struct rgb : public unary<data::rgb>::function
{
    double r_into_r, g_into_r, b_into_r;
    double r_into_g, g_into_g, b_into_g;
    double r_into_b, g_into_b, b_into_b;

    rgb(double _r_into_r, double _g_into_r, double _b_into_r,
        double _r_into_g, double _g_into_g, double _b_into_g,
        double _r_into_b, double _g_into_b, double _b_into_b)
      : r_into_r(_r_into_r), g_into_r(_g_into_r), b_into_r(_b_into_r)
      , r_into_g(_r_into_g), g_into_g(_g_into_g), b_into_g(_b_into_g)
      , r_into_b(_r_into_b), g_into_b(_g_into_b), b_into_b(_b_into_b)
    {
    }

    data::rgb operator()(const data::rgb& s)
    {
        data::rgb d;
    
        d.r = calculate(s.r, r_into_r, s.g, g_into_r, s.b, b_into_r);
        d.g = calculate(s.r, r_into_g, s.g, g_into_g, s.b, b_into_g);
        d.b = calculate(s.r, r_into_b, s.g, g_into_b, s.b, b_into_b);

        return d;
    }
};

}}}
