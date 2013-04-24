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
#include <dagger/algorithm/kernel.h>


namespace dagger {
namespace operations {


struct kernel_rgb : public unary<data::rgb>::function
{
    channel r_kernel;
    channel g_kernel;
    channel b_kernel;

    bool normalize;

    kernel_rgb(const channel& _r_kernel, const channel& _g_kernel, const channel& _b_kernel, bool _normalize)
      : r_kernel(_r_kernel)
      , g_kernel(_g_kernel)
      , b_kernel(_b_kernel)
      , normalize(_normalize)
    {
    }
    
    kernel_rgb(const channel& _kernel, bool _normalize)
      : kernel_rgb(_kernel, _kernel, _kernel, _normalize)
    {
    }

    data::rgb operator()(const data::rgb& s)
    {
        data::rgb d;
    
        d.r = algorithm::kernel(s.r, r_kernel, normalize);
        d.g = algorithm::kernel(s.g, g_kernel, normalize);
        d.b = algorithm::kernel(s.b, b_kernel, normalize);

        return d;
    }
};

}}
