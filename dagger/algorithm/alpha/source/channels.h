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


struct channels
{
    dagger::channel r_alpha;
    dagger::channel g_alpha;
    dagger::channel b_alpha;

    channels(const dagger::channel& _r_alpha, const dagger::channel& _g_alpha, const dagger::channel& _b_alpha)
      : r_alpha(_r_alpha)
      , g_alpha(_g_alpha)
      , b_alpha(_b_alpha)
    {
    }

    void prepare()
    {
    }

    const dagger::channel& r() const
    {
        return r_alpha;
    }

    const dagger::channel& g() const
    {
        return g_alpha;
    }

    const dagger::channel& b() const
    {
        return b_alpha;
    }
};

}}}}
