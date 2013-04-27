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

#include <dagger/algorithm/gamma/rgb.h>
#include <dagger/algorithm/gamma/grayscale.h>
#include <dagger/algorithm/alpha/rgb.h>
#include <dagger/algorithm/alpha/source/channel.h>
#include <dagger/algorithm/alpha/source/channels.h>
#include <dagger/algorithm/alpha/source/values.h>
#include <dagger/algorithm/alpha/source/rgb_operation.h>
#include <dagger/algorithm/alpha/source/grayscale_operation.h>
#include <dagger/algorithm/alpha/grayscale.h>
#include <dagger/algorithm/scale/rgb.h>
#include <dagger/algorithm/scale/grayscale.h>
#include <dagger/algorithm/kernel/rgb.h>
#include <dagger/algorithm/kernel/grayscale.h>
#include <dagger/algorithm/invert/rgb.h>
#include <dagger/algorithm/invert/grayscale.h>
#include <dagger/algorithm/channel_mixer/rgb.h>
#include <dagger/algorithm/channel_mixer/grayscale.h>
#include <dagger/algorithm/levels/rgb.h>
#include <dagger/algorithm/levels/grayscale.h>
#include <dagger/algorithm/auto_levels/rgb.h>
#include <dagger/algorithm/auto_levels/grayscale.h>


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
    algorithm::alpha::source::channel bla(alpha);
    algorithm::alpha::rgb<algorithm::alpha::source::channel> o2_alpha(&bla);
    binary<data::rgb> o2(&o1_image, &o1_background, &o2_alpha);

    ////////////////////////////////////////
    algorithm::gamma::rgb o3_gamma;

    //o3_gamma.r_gamma = 0.4545;
    //o3_gamma.g_gamma = 0.4545;
    //o3_gamma.b_gamma = 0.4545;

    unary<data::rgb> o3(&o2, &o3_gamma);

    ////////////////////////////////////////
    algorithm::scale::rgb o4_scale;

    o4_scale.width_scale = 0.5;
    o4_scale.height_scale = 0.5;

    transform<data::rgb, data::rgb> o4(&o3, &o4_scale);

    ////////////////////////////////////////
    algorithm::kernel::matrix test_kernel(3, 3);

    test_kernel.set_value(0, 0, 1);
    test_kernel.set_value(1, 0, 1);
    test_kernel.set_value(2, 0, 1);
    test_kernel.set_value(0, 1, 1);
    test_kernel.set_value(1, 1, 1);
    test_kernel.set_value(2, 1, 1);
    test_kernel.set_value(0, 2, 1);
    test_kernel.set_value(1, 2, 1);
    test_kernel.set_value(2, 2, 1);

    algorithm::kernel::rgb o5_kernel;

    o5_kernel.normalize = true;
    o5_kernel.r_kernel = test_kernel;
    o5_kernel.g_kernel = test_kernel;
    o5_kernel.b_kernel = test_kernel;

    unary<data::rgb> o5(&o4, &o5_kernel);

    ////////////////////////////////////////
    algorithm::levels::rgb o6_levels;

    o6_levels.r_input_low = channel::max_value / 2;
    o6_levels.r_input_high = channel::max_value / 2;
    o6_levels.g_input_low = channel::max_value / 2;
    o6_levels.g_input_high = channel::max_value / 2;
    o6_levels.b_input_low = channel::max_value / 2;
    o6_levels.b_input_high = channel::max_value / 2;
    /*
    o6_levels.r_output_low = channel::max_value / 2;
    o6_levels.g_output_low = channel::max_value / 2;
    o6_levels.b_output_low = channel::max_value / 2;
    */
    //o6_levels.adjust_individual_channels = true;

    unary<data::rgb> o6(&o5, &o6_levels);

    ////////////////////////////////////////
    algorithm::gamma::rgb o7_gamma;

    //o7_gamma.r_gamma = 2.2;
    //o7_gamma.g_gamma = 2.2;
    //o7_gamma.b_gamma = 2.2;

    unary<data::rgb> o7(&o6, &o7_gamma);

    ////////////////////////////////////////
    data::rgb result;
    o7.render(&result);

    image::save_png("test1.png", result);

    return 0;
}

