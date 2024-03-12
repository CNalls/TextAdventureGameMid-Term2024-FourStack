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

    // Calculate the new position
    Vector2D newPosition = m_position + direction;

    // Check if the new position is within the bounds of the room
    if (newPosition.x >= 0 && newPosition.x < room->GetWidth() && newPosition.y >= 0 && newPosition.y < room->GetHeight()) {
        // check for key
        if (room->GetLocation(newPosition) == 'K') {
            m_keyCount++;
            room->ClearLocation(newPosition);
        }

        // check for lock
        if (room->GetLocation(newPosition) == 'L') {
            if (m_keyCount > 0) {
                m_keyCount--;
                room->OpenDoor(newPosition);
            }
        }

        // check for door
        if (room->GetLocation(newPosition) == 'D') {
            room->OpenDoor(newPosition);
        }

        // try to move
        if (room->GetLocation(newPosition) == ' ') {
            m_position = newPosition;
        }
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
