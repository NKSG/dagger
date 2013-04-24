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
namespace kernel {


class matrix;
channel calculate(const channel&, const matrix&, bool);


class matrix
{
public:
    typedef std::vector<double> values_t;
    
public:
    matrix(int16_t width, int16_t height)
    {
        create_matrix(width, height);
        
        m_values.resize(width * height);
        std::fill(m_values.begin(), m_values.end(), 0);
    }

    matrix(int16_t width, int16_t height, const values_t& values)
    {
        assert(values.size() == width * height);
        
        create_matrix(width, height);
        
        m_values.resize(width * height);
        std::copy(values.begin(), values.end(), m_values.begin());
    }

public:
    int16_t width() const
    {
        return m_width;
    }

    int16_t height() const
    {
        return m_height;
    }

    int32_t size() const
    {
        return m_values.size();
    }

    values_t values() const
    {
        return m_values;
    }

    void set_value(int16_t x, int16_t y, double value)
    {
        assert(x >= 0 && x < m_width);
        assert(y >= 0 && y < m_height);

        m_values[y * m_width + x] = value;
    }

public:
    matrix(const matrix& other)
    {
        *this = other;
    }

    matrix& operator=(const matrix& other)
    {
        create_matrix(other.m_width, other.m_height);
        m_values = other.m_values;

        return *this;
    }

    matrix(matrix&& other)
    {
        *this = std::move(other);
    }

    matrix& operator=(matrix&& other)
    {
        m_width = other.m_width;
        m_height = other.m_height;
        
        m_values = std::move(other.m_values);
    }

private:
    void create_matrix(int16_t width, int16_t height)
    {
        assert(width % 2 != 0);
        assert(height % 2 != 0);
        
        assert(width > 0 && width <= 8192);
        assert(height > 0 && height <= 8192);

        m_width = width;
        m_height = height;
    }

    std::vector<int64_t> int_values() const
    {
        std::vector<int64_t> int_values;
        int_values.resize(m_values.size());
        
        std::transform(m_values.begin(), m_values.end(), int_values.begin(),
                       [](const double& v) {return static_cast<int64_t>(v * 1000);});

        return int_values;
    }

private:
    int16_t m_width;
    int16_t m_height;

    values_t m_values;

private:
    friend channel calculate(const channel& c, const matrix& k, bool normalize);
};

channel calculate(const channel& c, const matrix& k, bool normalize)
{
    assert(c.empty() == false);
    
    assert(k.width() <= 8192);
    assert(k.height() <= 8129);
    
    channel d(c.width(), c.height());
    channel v(k.width(), k.height());

    std::vector<int64_t> kernel = k.int_values();
    
    int16_t width = c.width();
    int16_t height = c.height();

    int16_t x_offset = k.width() / 2;
    int16_t y_offset = k.height() / 2;

    const int32_t* data = v.data().get();
    int32_t size = kernel.size();

    for (int16_t y = 0; y < height; y++)
    {
        for (int16_t x = 0; x < width; x++)
        {
            v.view(c, x-x_offset, y-y_offset);

            int64_t value = std::inner_product(data, data+size, kernel.begin(), static_cast<int64_t>(0));
            
            value /= 1000;
            
            if (normalize == true)
                value /= size;
            
            value = std::min(value, static_cast<int64_t>(channel::max_value));
            value = std::max(value, static_cast<int64_t>(0));

            d.set_value(x, y, value);
        }
    }

    return d;
}

}}}
