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

#include <dagger/algorithm/scale/base.h>


namespace dagger {
namespace algorithm {
namespace scale {


struct rgb : public transform<data::rgb, data::rgb>::function
{
    int16_t new_width;
    int16_t new_height;

    double width_scale;
    double height_scale;

    rgb()
      : new_width(0)
      , new_height(0)
      , width_scale(1)
      , height_scale(1)
    {
    }

    data::rgb operator()(const data::rgb& s)
    {
        data::rgb d;

        if (width_scale != 0)
            new_width = s.width() * width_scale;

        if (height_scale != 0)
            new_height = s.height() * height_scale;

        d.r = calculate(s.r, new_width, new_height);
        d.g = calculate(s.g, new_width, new_height);
        d.b = calculate(s.b, new_width, new_height);

        return d;
    }
};

}}}
