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

#include <dagger/image/png.h>

#include <dagger/operations/gamma_rgb.h>
#include <dagger/operations/alpha_rgb.h>
#include <dagger/operations/box_scale_rgb.h>
#include <dagger/operations/kernel_rgb.h>


using namespace dagger;


int main()
{
    auto input = image::load_png("test.png");
    
    data::rgb& i = std::get<0>(input);
    channel& alpha = std::get<1>(input);

    ////////////////////////////////////////
    root<data::rgb> o1_image(i);
    root<data::rgb> o1_background(data::rgb(i.width(), i.height()));
    
    ////////////////////////////////////////
    operations::alpha_rgb o2_alpha(alpha);
    binary<data::rgb> o2(&o1_image, &o1_background, &o2_alpha);

    ////////////////////////////////////////
    operations::gamma_rgb o3_gamma(0.4545);
    unary<data::rgb> o3(&o2, &o3_gamma);

    ////////////////////////////////////////
    operations::box_scale_rgb o4_scale(0.3);
    transform<data::rgb, data::rgb> o4(&o3, &o4_scale);

    ////////////////////////////////////////
    channel test_kernel(3, 3);
    
    test_kernel.set_value(0, 0, 1000);
    test_kernel.set_value(1, 0, 1000);
    test_kernel.set_value(2, 0, 1000);
    test_kernel.set_value(0, 1, 1000);
    test_kernel.set_value(1, 1, 1000);
    test_kernel.set_value(2, 1, 1000);
    test_kernel.set_value(0, 2, 1000);
    test_kernel.set_value(1, 2, 1000);
    test_kernel.set_value(2, 2, 1000);
    
    operations::kernel_rgb o5_kernel(test_kernel, true);
    unary<data::rgb> o5(&o4, &o5_kernel);

    ////////////////////////////////////////
    operations::gamma_rgb o6_gamma(2.2);
    unary<data::rgb> o6(&o5, &o6_gamma);

    ////////////////////////////////////////
    data::rgb result;
    o6.render(false, &result);
    
    image::save_png("test1.png", result);

    return 0;
}

