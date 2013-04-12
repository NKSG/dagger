#pragma once


#include <dagger/channel.h>
#include <dagger/channel_diff.h>
#include <dagger/image/base.h>


namespace dagger {
namespace image {


class rgba : public base
{
public:
    struct data
    {
        channel r;
        channel g;
        channel b;
        channel a;

        data(int16_t height, int16_t width)
          : r(height, width)
          , g(height, width)
          , b(height, width)
          , a(height, width)
        {
        }
    };

public:
    rgba()
      : m_data(nullptr)
      , m_data_diff(nullptr)
      , m_last_change(0)
      , m_last_parent_change(0)
    {
    }

public:
    uint32_t update(data* d)
    {
        if (m_parent == nullptr)
        {
            *d = *m_data;
            return 1;
        }
        
        uint32_t last_parent_change = m_parent->update(d);
        
        if (last_parent_change > m_last_parent_change)
        {
            m_last_parent_change = last_parent_change;
            
            do_operation(d);
            return m_last_change;
        }
        
        m_data_diff->apply(d);
        return m_last_change;
    }

    void do_operation(data* d)
    {
        data tmp(*d);
        //operation(d);
        
        m_last_change++;
        m_data_diff.reset(new data_diff(tmp, *d));
    }

    void connect(rgba* parent)
    {
    }

    void disconnect()
    {
    }

private:
    struct data_diff
    {
        channel_diff r;
        channel_diff g;
        channel_diff b;
        channel_diff a;

        data_diff(const data& i1, const data& i2)
          : r(i1.r, i2.r)
          , g(i1.g, i2.g)
          , b(i1.b, i2.b)
          , a(i1.a, i2.a)
        {
        }

        void apply(data* d)
        {
            r.apply(&d->r);
            g.apply(&d->g);
            b.apply(&d->b);
            a.apply(&d->a);
        }
    };

private:
    rgba* m_parent;
    
    std::unique_ptr<data>      m_data;
    std::unique_ptr<data_diff> m_data_diff;

    uint32_t m_last_change;
    uint32_t m_last_parent_change;
};

}}
