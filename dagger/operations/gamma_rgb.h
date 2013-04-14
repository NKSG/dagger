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
#include <dagger/algorithm/gamma.h>


namespace dagger {
namespace operations {


struct gamma_rgb : public unary<data::rgb>::function
{
    double r;
    double g;
    double b;
    
    gamma_rgb(double _r, double _g, double _b)
      : r(_r)
      , g(_g)
      , b(_b)
    {
    }

    gamma_rgb(double g)
      : gamma_rgb(g, g, g)
    {
    }
    
    gamma_rgb()
      : gamma_rgb(1)
    {
    }
    
    data::rgb operator()(const data::rgb& source)
    {
        data::rgb d(source);
        
        d.r = algorithm::gamma(d.r, r);
        d.g = algorithm::gamma(d.g, g);
        d.b = algorithm::gamma(d.b, b);

        return d;
    }
};

}}
