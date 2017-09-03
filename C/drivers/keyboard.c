#include "keyboard.h"

char getScancode()
{
    char c = 0;
    
    do 
    {
        if(portInB(0x60) != c)
        {
            c = portInB(0x60);
            if(c > 0)
                return c;
        }
    }
    while(1);
}
