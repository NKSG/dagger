#include <dagger/image/rgba.h>


int main()
{
    dagger::image::rgba i1;

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
