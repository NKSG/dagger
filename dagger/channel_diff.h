#pragma once


#include <dagger/channel.h>


namespace dagger {


class channel_diff
{
public:
    class different_channels_error : public std::runtime_error
    {
    public:
        different_channels_error()
          : runtime_error("channels don't have same dimensions")
        {
        }
    };
    
    class invalid_channel_error : public std::runtime_error
    {
    public:
        invalid_channel_error()
          : runtime_error("channel not compatible with the diff")
        {
        }
    };
    
public:
    channel_diff(const channel& c1, const channel& c2)
    {
        if (c1.height() != c2.height())
            throw different_channels_error();

        if (c1.width() != c2.width())
            throw different_channels_error();

        create_channel_diff(c1, c2);
    }

public:
    void apply(channel* c)
    {
        if (c->height() != m_height)
            throw invalid_channel_error();

        if (c->width() != m_width)
            throw invalid_channel_error();

        int32_t* channel_data = c->data().get();
        int32_t* diff_data = m_data.get();
        
        int32_t value_offset = 0;

        for (int32_t i = 0; i < m_image_size; i++)
        {
            if (m_bit_mask[i] == false)
                continue;
            
            channel_data[i] += diff_data[value_offset];
            value_offset++;
        }
    }

public:
    channel_diff(const channel_diff& other)
    {
        *this = other;
    }

    channel_diff& operator=(const channel_diff& other)
    {
        create_channel_diff(other.m_height, other.m_width);
        std::copy_n(m_data.get(), m_image_size, other.m_data.get());
    }

private:
    void create_channel_diff(int16_t height, int16_t width)
    {
        assert(height > 0);
        assert(width > 0);
        
        m_height = height;
        m_width = width;
        
        m_image_size = height * width;
        
        m_data.reset(new int32_t[m_image_size]);
        std::fill_n(m_data.get(), m_image_size, 0);

        m_bit_mask.resize(m_image_size);
        std::fill_n(m_bit_mask.begin(), m_image_size, false);
    }

    void create_channel_diff(const channel& c1, const channel& c2)
    {
        create_channel_diff(c1.height(), c1.width());
        
        const int32_t* c1_data = c1.data().get();
        const int32_t* c2_data = c2.data().get();
        
        int32_t* dest_data = m_data.get();
        int32_t diff_values = 0;

        for (int32_t i = 0; i < m_image_size; i++)
        {
            int32_t diff = c1_data[i] - c2_data[i];
            dest_data[i] = diff;

            if (diff == 0)
                continue;
            
            m_bit_mask[i] = true;
            diff_values++;
        }

        data_t compacted_data(new int32_t[diff_values]);

        std::copy_if(m_data.get(), m_data.get()+m_image_size, compacted_data.get(),
                     [](int32_t value) { return value != 0; });

        m_data = compacted_data;
    }

private:
    data_t     m_data;
    bit_mask_t m_bit_mask;
    
    int16_t m_height;
    int16_t m_width;
    
    int32_t m_image_size;
};

}
