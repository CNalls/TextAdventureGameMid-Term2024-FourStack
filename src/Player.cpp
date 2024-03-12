#include "Player.hpp"
#include "fogpi/fogpi.hpp"
#include "fogpi/Math.hpp"
#include "Room.hpp"
#include <string>
#include <iostream>

void Player::Start()
{
    m_character = 'P';
}

void Player::Update() {
    // direction
    std::string instruction = "wasd and Enter to move";
    char directionInput = 'r';
    Vector2D direction(0.0f, 0.0f);

    // Get user input for movement
    while (directionInput != 'w' && directionInput != 'a' && directionInput != 's' && directionInput != 'd') {
        directionInput = request_char(instruction.c_str());
    }

    // Determine movement direction
    if (directionInput == 'w')
        direction = Vector2D(0.0f, -1.0f);
    else if (directionInput == 'a')
        direction = Vector2D(-1.0f, 0.0f);
    else if (directionInput == 's')
        direction = Vector2D(0.0f, 1.0f);
    else if (directionInput == 'd')
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
        room->OpenDoor(m_position + direction);
    }

    // Engage in combat if an enemy is at the new position
    Entity* enemy = room->GetEnemyAtPosition(m_position);
    if (enemy) {
        // Engage in combat with the enemy
        std::cout << "You encountered an enemy! Press 'r' to roll the dice: ";
        char roll;
        std::cin >> roll;
        if (roll == 'r') {
            // Roll a 6-sided dice for player and enemy
            int playerRoll = rand() % 6 + 1;
            int enemyRoll = rand() % 6 + 1;

            std::cout << "Player rolled: " << playerRoll << std::endl;
            std::cout << "Enemy rolled: " << enemyRoll << std::endl;

            // Determine the winner based on the dice rolls
            if (playerRoll >= enemyRoll) {
                std::cout << "You defeated the enemy!" << std::endl;
                room->RemoveEnemy(enemy);
            } else {
                std::cout << "You were defeated by the enemy!" << std::endl;
                // Handle player defeat (e.g., game over)
            }
        }
    }
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