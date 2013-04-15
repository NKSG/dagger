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
#include <dagger/algorithm/alpha.h>


namespace dagger {
namespace operations {


struct alpha_rgb : public binary<data::rgb>::function
{
    channel r_a;
    channel g_a;
    channel b_a;

    alpha_rgb(const channel& _r_a, const channel& _g_a, const channel& _b_a)
      : r_a(_r_a)
      , g_a(_g_a)
      , b_a(_b_a)
    {
    }
    
    alpha_rgb(const channel& _a)
      : alpha_rgb(_a, _a, _a)
    {
    }

    alpha_rgb()
      : alpha_rgb(channel())
    {
    }
    
    data::rgb operator()(const data::rgb& s1, const data::rgb& s2)
    {
        data::rgb d;
    
        d.r = algorithm::alpha(s1.r, s2.r, r_a);
        d.g = algorithm::alpha(s1.g, s2.g, g_a);
        d.b = algorithm::alpha(s1.b, s2.b, b_a);

        return d;
    }
};

}}
