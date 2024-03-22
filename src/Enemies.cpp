#include "Enemies.hpp"
#include "fogpi/fogpi.hpp"
#include "fogpi/Math.hpp"
#include "Room.hpp"
#include <string>
/*
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

if (room->GetLocation(m_position + direction) == 'M')
    {
        printf("You have Entered A Combat Scenario with: %i \n" ,m_enemyMeleeEnemRand ); //maybe make a randomizer for all melee enemies and from that it has its own special stats
        room->ClearLocation(m_position + direction);
    }

if (room->GetLocation(m_position + direction) == 'R')
    {
        printf("You have Entered A Combat Scenario with: %i \n" ,m_enemyRangedEnemRand ); 
        room->ClearLocation(m_position + direction);
    }

}
*/