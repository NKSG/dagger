#pragma once


#include <dagger/algorithm/apply_alpha.h>
#include <dagger/image/rgb.h>


namespace dagger {
namespace algorithm {


image::rgb apply_alpha(const image::rgb& i1, const image::rgb& i2, const channel& alpha)
{
    image::rgb d;
    
    d.r = apply_alpha(i1.r, i2.r, alpha);
    d.g = apply_alpha(i1.g, i2.g, alpha);
    d.b = apply_alpha(i1.b, i2.b, alpha);

    return std::move(d);
}

}}
