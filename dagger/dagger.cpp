#include <dagger/rgb.h>


using namespace dagger;


struct autolevels : public operation<image::rgb>::function
{
    image::rgb operator()(const image::rgb& source)
    {
        image::rgb dest(source);
        return std::move(dest);
    }
};


int main()
{
    autolevels a;
    
    operation<image::rgb> op1(nullptr, &a);

    image::rgb d;
    op1.render(&d);
    
    return 0;
}
