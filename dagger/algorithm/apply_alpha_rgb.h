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


#include <dagger/algorithm/apply_alpha.h>
#include <dagger/data/rgb.h>


namespace dagger {
namespace algorithm {


data::rgb apply_alpha(const data::rgb& i1, const data::rgb& i2, const channel& alpha)
{
    data::rgb d;
    
    d.r = apply_alpha(i1.r, i2.r, alpha);
    d.g = apply_alpha(i1.g, i2.g, alpha);
    d.b = apply_alpha(i1.b, i2.b, alpha);

    return d;
}

}}
