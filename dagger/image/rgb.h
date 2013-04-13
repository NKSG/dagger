#pragma once


#include <dagger/channel.h>


namespace dagger {
namespace image {


struct rgb
{
    channel r, g, b;

    rgb()
    {
    }

    rgb(int16_t height, int16_t width)
      : r(height, width)
      , g(height, width)
      , b(height, width)
    {
    }

    int16_t height() const
    {
        return r.height();
    }

    int16_t width() const
    {
        return r.width();
    }

    struct diff
    {
        channel::diff r, g, b;

        diff()
        {
        }

        diff(const rgb& i1, const rgb& i2)
          : r(i1.r, i2.r)
          , g(i1.g, i2.g)
          , b(i1.b, i2.b)
        {
        }

        void apply(rgb* d)
        {
            r.apply(&d->r);
            g.apply(&d->g);
            b.apply(&d->b);
        }
    };
};

}}
