#ifdef _WIN32
#include <windows.h>
#endif

#include "fogpi/fogpi.hpp"
#include "fogpi/Math.hpp"

#include "Room.hpp"
#include "Entity.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    Room room;
    room.Load("assets/level_1.map");

    while(true)
    {
        room.Update();
    }

    return 0;

    
}