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
#include <dagger/data/grayscale.h>

#include <dagger/algorithm/scale/base.h>


namespace dagger {
namespace algorithm {
namespace scale {


struct grayscale : public transform<data::grayscale, data::grayscale>::function
{
    int16_t new_width;
    int16_t new_height;

    double width_scale;
    double height_scale;

    grayscale(int16_t _new_width, int16_t _new_height)
      : new_width(_new_width)
      , new_height(_new_height)
      , width_scale(0)
      , height_scale(0)
    {
    }

    grayscale(double _width_scale, double _height_scale)
      : new_width(0)
      , new_height(0)
      , width_scale(_width_scale)
      , height_scale(_height_scale)
    {
    }

    grayscale(double scale)
      : grayscale(scale, scale)
    {
    }

    data::grayscale operator()(const data::grayscale& s)
    {
        data::grayscale d;

        if (width_scale != 0)
            new_width = s.width() * width_scale;

        if (height_scale != 0)
            new_height = s.height() * height_scale;

        d.g = scale::calculate(s.g, new_width, new_height);

        return d;
    }
};

}}}
