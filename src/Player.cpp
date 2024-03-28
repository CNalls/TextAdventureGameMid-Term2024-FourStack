#include "Player.hpp"
#include "Enemy.hpp" 
#include "Room.hpp"
#include "fogpi/Math.hpp"
#include <iostream>
#include <cstdlib> 
#include <ctime>   

Player::Player() {
    
}


void Player::Start() {
    m_character = 'P';
    m_health = 20; 
}

void Player::Update() {
    std::string instruction = "Use WASD to move and press Enter.";
    char directionInput = 'r';
    Vector2D direction(0.0f, 0.0f);
    getchar();
    std::cout << instruction << std::endl;
    
    printf("%c\n", directionInput);

    
    if (directionInput == 'w') direction = Vector2D(0.0f, -1.0f);
    else if (directionInput == 'a') direction = Vector2D(-1.0f, 0.0f);
    else if (directionInput == 's') direction = Vector2D(0.0f, 1.0f);
    else if (directionInput == 'd') direction = Vector2D(1.0f, 0.0f);

    Vector2D newPosition = m_position + direction;

    printf("room pointer: %p", room);
    Entity* enemy = room->GetEnemyAtPosition(newPosition);
    if (enemy) {
        std::cout << "You encountered an enemy! Press 'r' to roll the dice for combat: ";
        char roll;
        std::cin >> roll;

        if (roll == 'r') {
            int playerDamage = rand() % 6 + 1; // Calculate player's damage

            // Apply damage to the enemy and show the results
            dynamic_cast<Enemy*>(enemy)->TakeDamage(playerDamage);
            if (!dynamic_cast<Enemy*>(enemy)->IsAlive()) {
                std::cout << "Enemy defeated!" << std::endl;
                room->RemoveEnemy(enemy); // Remove the enemy if defeated
            }
        }
    } else if (room->GetLocation(newPosition) == ' ') {
        m_position = newPosition; // Move the player if the new position is free
    }

   
}

void Player::TakeDamage(int damage) {
    m_health -= damage;
    std::cout << "Player took " << damage << " damage and now has " << m_health << " health left." << std::endl;

    if (m_health <= 0) {
        std::cout << "Player is dead!" << std::endl;
        // Implement game-over logic here
    }
}

