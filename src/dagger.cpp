#include "channel_diff.h"


int main()
{
    dagger::channel c1(1024*4, 1024*6);
    dagger::channel c2(1024*4, 1024*6);

    c1.data().get()[0] = 1;
    c2.data().get()[1] = 2;

    dagger::channel_diff d(c1, c2);

    d.apply(&c1);
    
    return 0;
}
