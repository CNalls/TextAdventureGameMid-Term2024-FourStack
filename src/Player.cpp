#include "Player.hpp"
#include "fogpi/fogpi.hpp"
#include "fogpi/Math.hpp"
#include "Room.hpp"
#include <string>

void Player::Start()
{
    m_character = 'P';
}

void Player::Update()
{
    // direction
    std::string instruction = "wasd and Enter to move, press h for help";
    char directionInput = 'r';
    Vector2D direction(0.0f, 0.0f);

    while(directionInput != 'w' &&
          directionInput != 'a' &&
          directionInput != 's' &&
          directionInput != 'd' && directionInput != 'h')
    {
        directionInput = request_char(instruction.c_str());
    }

    if (directionInput == 'w')
        direction = Vector2D(0.0f, -1.0f);
    if (directionInput == 'a')
        direction = Vector2D(-1.0f, 0.0f);
    if (directionInput == 's')
        direction = Vector2D(0.0f, 1.0f);
    if (directionInput == 'd')
        direction = Vector2D(1.0f, 0.0f);
    // HELP MENU
    if (directionInput == 'h')
        std::cout << "P   the player" << std::endl;
        std::cout << "D   these are doors, they are all locked" << std::endl;
        std::cout << "K   these are keys, you need these to open doors" << std::endl;
        std::cout << "G   this is gold" << std::endl;
        std::cout << "-   these are ranged enemies" << std::endl;
        std::cout << "+   these are melee enemies" << std::endl;
        std::cout << std::endl;
    
    // check for key
    if (room->GetLocation(m_position + direction) == 'K')
    {
        m_keyCount++;
        printf("You Picked Up A Key: %i \n" ,m_keyCount ); 
        room->ClearLocation(m_position + direction);
    }

    // check for lock
    if (room->GetLocation(m_position + direction) == 'L')
    {
        if (m_keyCount <= 0)
            return;
        //check how do we know we have keys and try to add this to the 
        m_keyCount --;
        room->OpenDoor(m_position + direction);
    }

    // check for door
    if (room->GetLocation(m_position + direction) == 'D')
    {
        room->OpenDoor(m_position + direction);
    }

    //check for gold
    if (room->GetLocation(m_position + direction) == 'G')
    {
        m_goldCount++;
        printf("You Picked Up Gold: %i \n" ,m_goldCount );
        //printf("%i \n" ,m_goldCount);
        room->ClearLocation(m_position + direction);
    }

    //check for item purchase
    //For example, sword, bow, buckler, shield, potion, Machine for gambling machine
    //a weapon that costs 999 gold but one shots everything with a 100% crit chance and accuracy rate
    if (room->GetLocation(m_position + direction) == 'G')
    {
        if (m_goldCount <= 0)
            return;
        m_goldCount--;
        room->ClearLocation(m_position + direction);
    }

    //check for chest
    if (room->GetLocation(m_position + direction) == 'C')
    {
        if (m_keyCount <= 0)
            return;
        //check how do we know we have keys and try to add this to the 
        m_chestCount --;
        room->OpenDoor(m_position + direction);
    }

    // try to move
    if (room->GetLocation(m_position + direction) == ' ')
        m_position += direction;
}