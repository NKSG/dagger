#pragma once


#include <dagger/channel.h>


namespace dagger {
namespace algorithm {


channel apply_alpha(const channel& c1, const channel& c2, const channel& alpha)
{
    if (c1.height() != c2.height())
        throw channel::invalid_channel_error();

    if (c1.width() != c2.width())
        throw channel::invalid_channel_error();

    if (alpha.empty() == true)
    {
        channel d(c1);
        return std::move(d);
    }

    channel d(c1.height(), c1.width());
    int32_t image_size = c1.height() * c1.width();

    const int32_t* _c1 = c1.data().get();
    const int32_t* _c2 = c2.data().get();
    const int32_t* _a = alpha.data().get();

    int32_t* _d = d.data().get();
        
    for (int32_t i = 0; i < image_size; i++)
    {
        int64_t v1 = _c1[i];
        int64_t v2 = _c2[i];
        int64_t a = _a[i];

        assert(v1 > 0);
        assert(v2 > 0);
        assert(a > 0);

        _d[i] = (v1 * a + v2 * (channel::max_value - a)) / channel::max_value;
    }

    return std::move(d);
}

}}
