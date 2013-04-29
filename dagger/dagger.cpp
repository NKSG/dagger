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
#include <dagger/algorithm/threshold/grayscale.h>


using namespace dagger;


int main()
{
    auto input = image::load_png("test.png");

    ////////////////////////////////////////
    algorithm::gamma::rgb o2_gamma;

    o2_gamma.r_gamma = 0.4545;
    o2_gamma.g_gamma = 0.4545;
    o2_gamma.b_gamma = 0.4545;

    input.first = o2_gamma(input.first);
    ////////////////////////////////////////
    algorithm::levels::rgb o3_levels;

    o3_levels.r_input_low = channel::max_value / 2;
    o3_levels.g_input_low = channel::max_value / 2;
    o3_levels.b_input_low = channel::max_value / 2;
    /*
    o6_levels.r_output_low = channel::max_value / 2;
    o6_levels.g_output_low = channel::max_value / 2;
    o6_levels.b_output_low = channel::max_value / 2;
    */
    //o6_levels.adjust_individual_channels = true;

    input.first = o3_levels(input.first);
    ////////////////////////////////////////
    algorithm::gamma::rgb o4_gamma;

    o4_gamma.r_gamma = 2.2;
    o4_gamma.g_gamma = 2.2;
    o4_gamma.b_gamma = 2.2;

    input.first = o4_gamma(input.first);

    image::save_png("test1.png", input.first);

    return 0;
}

