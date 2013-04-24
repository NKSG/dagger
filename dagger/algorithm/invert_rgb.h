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
#include <dagger/algorithm/invert.h>


namespace dagger {
namespace algorithm {
namespace invert {


struct rgb : public unary<data::rgb>::function
{
    data::rgb operator()(const data::rgb& s)
    {
        data::rgb d;

        d.r = calculate(s.r);
        d.g = calculate(s.g);
        d.b = calculate(s.b);

        return d;
    }
};

}}}
