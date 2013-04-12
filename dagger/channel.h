#pragma once


#include <dagger/types.h>


namespace dagger {


class channel
{
public:

public:
    const int max_value = 100000000;
    
public:
    channel(uint16_t height, uint16_t width)
    {
        create_channel(height, width);
    }

public:
    int16_t height() const
    {
        return m_height;
    }
    
    int16_t width() const
    {
        return m_width;
    }
    
    const data_t data() const
    {
        return m_data;
    }

    data_t data()
    {
        return m_data;
    }

public:
    channel(const channel& other)
    {
        *this = other;
    }

    channel& operator=(const channel& other)
    {
        create_channel(other.m_height, other.m_width);
        std::copy_n(other.m_data.get(), m_image_size, m_data.get());
        
        return *this;
    }

private:
    void create_channel(int16_t height, int16_t width)
    {
        assert(height > 0);
        assert(width > 0);
        
        m_height = height;
        m_width = width;
        
        m_image_size = height * width;
        
        m_data.reset(new int32_t[m_image_size]);
        std::fill_n(m_data.get(), m_image_size, 0);
    }

private:
    data_t  m_data;
    
    int16_t m_height;
    int16_t m_width;
    
    int32_t m_image_size;    
};

}
