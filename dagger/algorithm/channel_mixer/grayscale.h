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
#include <dagger/data/grayscale.h>
#include <dagger/algorithm/channel_mixer/base.h>


namespace dagger {
namespace algorithm {
namespace channel_mixer {


struct grayscale
{
    double r_into_g, g_into_g, b_into_g;

    grayscale()
      : r_into_g(1), g_into_g(0), b_into_g(0)
    {
    }

    data::grayscale operator()(const data::rgb& s)
    {
        data::grayscale d;

        d.g = calculate(s.r, r_into_g, s.g, g_into_g, s.b, b_into_g);

        return d;
    }
};

}}}
