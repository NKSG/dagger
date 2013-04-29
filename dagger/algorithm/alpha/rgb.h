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
#include <dagger/algorithm/alpha/base.h>


namespace dagger {
namespace algorithm {
namespace alpha {


template<typename source>
struct rgb
{
    source* s;

    rgb(source* _s)
      : s(_s)
    {
    }

    data::rgb operator()(const data::rgb& s1, const data::rgb& s2)
    {
        data::rgb d;

        s->prepare();

        d.r = calculate(s1.r, s2.r, s->r());
        d.g = calculate(s1.g, s2.g, s->g());
        d.b = calculate(s1.b, s2.b, s->b());

        return d;
    }
};

}}}
