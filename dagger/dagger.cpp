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
#include <dagger/operations/gamma.h>


using namespace dagger;


int main()
{
    auto input = image::load_png("test.png");
    operation<data::rgb> o1(std::get<0>(input));

    operations::gamma_rgb o2_gamma(2.2);
    operation<data::rgb> o2(&o1, &o2_gamma);

    data::rgb result;
    o2.render(&result);
    
    image::save_png("test1.png", result, std::get<1>(input));
    
    return 0;
}
