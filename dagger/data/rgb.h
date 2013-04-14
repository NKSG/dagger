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

    rgb(int16_t height, int16_t width)
      : r(height, width)
      , g(height, width)
      , b(height, width)
    {
    }

    int16_t height() const
    {
        return r.height();
    }

    int16_t width() const
    {
        return r.width();
    }

    struct diff
    {
        channel::diff r, g, b;

        diff()
        {
        }

        diff(const rgb& i1, const rgb& i2)
          : r(i1.r, i2.r)
          , g(i1.g, i2.g)
          , b(i1.b, i2.b)
        {
        }

        void apply(rgb* d)
        {
            r.apply(&d->r);
            g.apply(&d->g);
            b.apply(&d->b);
        }
    };
};

}}
