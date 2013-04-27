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

#include <dagger/algorithm/gamma/grayscale.h>


namespace dagger {
namespace algorithm {
namespace gamma {


struct grayscale : public unary<data::grayscale>::function
{
    double g_gamma;

    grayscale(double _g_gamma)
      : g_gamma(_g_gamma)
    {
    }

    data::grayscale operator()(const data::grayscale& s)
    {
        data::grayscale d;

        d.g = calculate(s.g, g_gamma);

        return d;
    }
};

}}}
