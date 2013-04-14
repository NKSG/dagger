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

#include <dagger/algorithm/scale_value.h>
#include <dagger/rgb.h>


namespace dagger {
namespace image {


std::tuple<data::rgb, channel> load_png(const std::string& file_name)
{
    uint32_t height = 0;
    uint32_t width = 0;

    std::vector<uint8_t> image_data;
    
    uint32_t error = lodepng::decode(image_data, width, height, file_name);

    if (error != 0)
        throw std::runtime_error(file_name + ": " + lodepng_error_text(error));

    data::rgb image(height, width);
    channel alpha(height, width);

    int32_t image_size = height * width;
    
    int32_t* _r = image.r.data().get();
    int32_t* _g = image.g.data().get();
    int32_t* _b = image.b.data().get();
    int32_t* _a = alpha.data().get();

    for (int32_t i = 0; i < image_size; i++)
    {
        int32_t offset = i * 4;
        
        int32_t r = image_data[offset+0];
        int32_t g = image_data[offset+1];
        int32_t b = image_data[offset+2];
        int32_t a = image_data[offset+3];

        _r[i] = algorithm::scale_source_value(r, 255);
        _g[i] = algorithm::scale_source_value(g, 255);
        _b[i] = algorithm::scale_source_value(b, 255);
        _a[i] = algorithm::scale_source_value(a, 255);
    }

    return std::make_tuple(image, alpha);
}

void save_png(const std::string& file_name, const data::rgb& image, const channel& alpha)
{
    int32_t height = image.height();
    int32_t width = image.width();

    int32_t image_size = height * width;

    std::vector<uint8_t> image_data;
    image_data.resize(image_size * 4);

    const int32_t* _r = image.r.data().get();
    const int32_t* _g = image.g.data().get();
    const int32_t* _b = image.b.data().get();

    const int32_t* _a = nullptr;

    if (alpha.empty() == false)
    {
        if (height != alpha.height())
            throw operation<data::rgb>::invalid_alpha_channel_error();

        if (width != alpha.width())
            throw operation<data::rgb>::invalid_alpha_channel_error();

        _a = alpha.data().get();
    }

    for (int32_t i = 0; i < image_size; i++)
    {
        int32_t offset = i * 4;

        int32_t r = _r[i];
        int32_t g = _g[i];
        int32_t b = _b[i];
        int32_t a = channel::max_value;

        if (_a != nullptr)
            a = _a[i];

        image_data[offset+0] = algorithm::scale_destination_value(r, 255);
        image_data[offset+1] = algorithm::scale_destination_value(g, 255);
        image_data[offset+2] = algorithm::scale_destination_value(b, 255);
        image_data[offset+3] = algorithm::scale_destination_value(a, 255);
    }

    uint32_t error = lodepng::encode(file_name, image_data, width, height);

    if (error != 0)
        throw std::runtime_error(file_name + ": " + lodepng_error_text(error));    
}

void save_png(const std::string& file_name, const data::rgb& image)
{
    save_png(file_name, image, channel());
}

}}
