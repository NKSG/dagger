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

#include <dagger/external/png/lodepng.h>

#include <dagger/data/rgb.h>
#include <dagger/algorithm/value/source.h>
#include <dagger/algorithm/value/destination.h>


namespace dagger {
namespace image {


std::pair<data::rgb, channel> load_png(const std::string& file_name)
{
    uint32_t width = 0;
    uint32_t height = 0;

    std::vector<uint8_t> image_data;

    uint32_t error = lodepng::decode(image_data, width, height, file_name);

    if (error != 0)
        throw std::runtime_error(file_name + ": " + lodepng_error_text(error));

    data::rgb image(width, height);
    channel alpha(width, height);

    int32_t* _r = image.r.data().get();
    int32_t* _g = image.g.data().get();
    int32_t* _b = image.b.data().get();
    int32_t* _a = alpha.data().get();

    for (int32_t i = 0; i < image.r.image_size(); i++)
    {
        int32_t offset = i * 4;

        int32_t r = image_data[offset+0];
        int32_t g = image_data[offset+1];
        int32_t b = image_data[offset+2];
        int32_t a = image_data[offset+3];

        _r[i] = algorithm::value::source(r, 255);
        _g[i] = algorithm::value::source(g, 255);
        _b[i] = algorithm::value::source(b, 255);
        _a[i] = algorithm::value::source(a, 255);
    }

    return std::make_pair(image, alpha);
}

void save_png(const std::string& file_name, const data::rgb& image, const channel& alpha)
{
    std::vector<uint8_t> image_data;
    image_data.resize(image.r.image_size() * 4);

    const int32_t* _r = image.r.data().get();
    const int32_t* _g = image.g.data().get();
    const int32_t* _b = image.b.data().get();

    const int32_t* _a = nullptr;

    if (alpha.empty() == false)
    {
        if (channel::equal_dimensions(image.r, alpha) == false)
            throw channel::invalid_alpha_channel_error();

        _a = alpha.data().get();
    }

    for (int32_t i = 0; i < image.r.image_size(); i++)
    {
        int32_t offset = i * 4;

        int32_t r = _r[i];
        int32_t g = _g[i];
        int32_t b = _b[i];
        int32_t a = channel::max_value;

        if (_a != nullptr)
            a = _a[i];

        image_data[offset+0] = algorithm::value::destination(r, 255);
        image_data[offset+1] = algorithm::value::destination(g, 255);
        image_data[offset+2] = algorithm::value::destination(b, 255);
        image_data[offset+3] = algorithm::value::destination(a, 255);
    }

    uint32_t error = lodepng::encode(file_name, image_data, image.width(), image.height());

    if (error != 0)
        throw std::runtime_error(file_name + ": " + lodepng_error_text(error));
}

void save_png(const std::string& file_name, const data::rgb& image)
{
    save_png(file_name, image, channel());
}

}}
