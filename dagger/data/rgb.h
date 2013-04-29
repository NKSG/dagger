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
namespace data {


struct rgb
{
    channel r, g, b;

    rgb()
    {
    }

    rgb(int16_t width, int16_t height)
      : r(width, height)
      , g(width, height)
      , b(width, height)
    {
    }

    int16_t width() const
    {
        return r.width();
    }

    int16_t height() const
    {
        return r.height();
    }
};

}}
