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


struct channel
{
    dagger::channel alpha;

    channel(const dagger::channel& _alpha)
      : alpha(_alpha)
    {
    }

    void prepare()
    {
    }

    const dagger::channel& r() const
    {
        return alpha;
    }

    const dagger::channel& g() const
    {
        return alpha;
    }

    const dagger::channel& b() const
    {
        return alpha;
    }
};

}}}}
