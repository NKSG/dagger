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
namespace algorithm {
namespace alpha {


struct rgb : public binary<data::rgb>::function
{
    channel r_alpha;
    channel g_alpha;
    channel b_alpha;

    rgb(const channel& _r_alpha, const channel& _g_alpha, const channel& _b_alpha)
      : r_alpha(_r_alpha)
      , g_alpha(_g_alpha)
      , b_alpha(_b_alpha)
    {
    }
    
    rgb(const channel& _alpha)
      : rgb(_alpha, _alpha, _alpha)
    {
    }

    data::rgb operator()(const data::rgb& s1, const data::rgb& s2)
    {
        data::rgb d;
    
        d.r = calculate(s1.r, s2.r, r_alpha);
        d.g = calculate(s1.g, s2.g, g_alpha);
        d.b = calculate(s1.b, s2.b, b_alpha);

        return d;
    }
};

}}}
