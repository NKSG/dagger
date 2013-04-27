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


#include <dagger/channel.h>


namespace dagger {
namespace algorithm {
namespace alpha {
namespace source {


struct values
{
    double r_alpha;
    double g_alpha;
    double b_alpha;

    values(double _r_alpha, double _g_alpha, double _b_alpha)
      : r_alpha(_r_alpha)
      , g_alpha(_g_alpha)
      , b_alpha(_b_alpha)
    {
        assert(r_alpha >= 0 && r_alpha <= 1);
        assert(g_alpha >= 0 && g_alpha <= 1);
        assert(b_alpha >= 0 && b_alpha <= 1);
    }

    values(double _alpha)
      : values(_alpha, _alpha, _alpha)
    {
    }

    void prepare()
    {
    }

    int32_t r() const
    {
        return r_alpha * dagger::channel::max_value;
    }

    int32_t g() const
    {
        return g_alpha * dagger::channel::max_value;
    }

    int32_t b() const
    {
        return b_alpha * dagger::channel::max_value;
    }
};

}}}}
