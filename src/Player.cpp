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
    std::string instruction = "wasd and Enter to move";
    char directionInput = 'r';
    Vector2D direction(0.0f, 0.0f);

    while(directionInput != 'w' &&
          directionInput != 'a' &&
          directionInput != 's' &&
          directionInput != 'd')
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
        printf("You Have Used a Key to Open this Door: %i \n" ,m_keyCount);
        room->OpenDoor(m_position + direction);
        //future lock that says (the key doesnt fit)  and is like a boss room key
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
        //we gonna have to builda  shop level for this one
        room->ClearLocation(m_position + direction);
    }

    //check for chest
    if (room->GetLocation(m_position + direction) == 'C')
    {
        if (m_keyCount <= 0)
        {
            printf("You Lack The Required Item for this: %i \n" ,m_keyCount );
            return;
        }
            
    
        //check how do we know we have keys and try to add this to the 
        m_keyCount --;
        printf("You Have Used a Key to Open the Chest: %i \n" ,m_keyCount );
        printf("You Have Received a: %i \n" ,m_randomItemCount );
        printf("Key Count: %i \n" ,m_keyCount );

        room->ClearLocation(m_position + direction);
    }

    //Check for gold after death
    // need to change this to however death screen looks
    if (room->GetLocation(m_position + direction) == ' ')
    {
        m_goldCount++;
        printf("You Picked Up Gold: %i \n" ,m_goldCount );
        room->ClearLocation(m_position + direction);
    }

    // try to move
    if (room->GetLocation(m_position + direction) == ' ')
        m_position += direction;


    //Make merchant area, backup code, make a demo enemy area and see if I can get stats to print out on enemy, see if i can make a while loop that makes a combat for an enemy that occurs after walking over the enemy (if possible add ai where it moves a random spot every time you input WASD) )
}