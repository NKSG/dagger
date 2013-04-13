#include <dagger/rgb.h>


struct autolevels : public dagger::operation<dagger::image::rgb>::function
{
    dagger::image::rgb operator()(const dagger::image::rgb& source)
    {
        dagger::image::rgb dest(source);
        return std::move(dest);
    }
};


int main()
{
    autolevels a;
    
    dagger::operation<dagger::image::rgb> op1(nullptr, &a);

    dagger::image::rgb d;
    op1.render(&d);

    /*
    dagger::file::png::load("bla1.png", &i1);
    dagger::operation::auto_levels i2(&i1);
    
    dagger::operation::grayscale i3(&i2);
    
    i3.update();
    
    dagger::operation::threshold i4(&i3, 100);
    
    i4.set_treshold(101);
    i4.update();

    dagger::file::png::save(&i4, "bla2.png");
    */
    
    return 0;
}
