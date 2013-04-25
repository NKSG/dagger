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


struct from_values
{
    double r_alpha;
    double g_alpha;
    double b_alpha;
    
    from_values(double _r_alpha, double _g_alpha, double _b_alpha)
      : r_alpha(_r_alpha)
      , g_alpha(_g_alpha)
      , b_alpha(_b_alpha)
    {
        assert(r_alpha >= 0 && r_alpha <= 1);
        assert(g_alpha >= 0 && g_alpha <= 1);
        assert(b_alpha >= 0 && b_alpha <= 1);
    }

    from_values(double _alpha)
      : from_values(_alpha, _alpha, _alpha)
    {
    }

    int32_t r() const
    {
        return r_alpha * channel::max_value;
    }

    int32_t g() const
    {
        return g_alpha * channel::max_value;
    }

    int32_t b() const
    {
        return b_alpha * channel::max_value;
    }
};


struct from_channels
{
    channel r_alpha;
    channel g_alpha;
    channel b_alpha;
    
    from_channels(const channel& _r_alpha, const channel& _g_alpha, const channel& _b_alpha)
      : r_alpha(_r_alpha)
      , g_alpha(_g_alpha)
      , b_alpha(_b_alpha)
    {
    }

    const channel& r() const
    {
        return r_alpha;
    }

    const channel& g() const
    {
        return g_alpha;
    }

    const channel& b() const
    {
        return b_alpha;
    }
};


struct from_channel
{
    channel alpha;
    
    from_channel(const channel& _alpha)
      : alpha(_alpha)
    {
    }

    const channel& r() const
    {
        return alpha;
    }

    const channel& g() const
    {
        return alpha;
    }

    const channel& b() const
    {
        return alpha;
    }
};


template<typename source>
struct rgb : public binary<data::rgb>::function
{
    source s;

    rgb(const source& _s)
      : s(_s)
    {
    }

    data::rgb operator()(const data::rgb& s1, const data::rgb& s2)
    {
        data::rgb d;
    
        d.r = calculate(s1.r, s2.r, s.r());
        d.g = calculate(s1.g, s2.g, s.g());
        d.b = calculate(s1.b, s2.b, s.b());

        return d;
    }
};

}}}
