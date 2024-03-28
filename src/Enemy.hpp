#pragma once
#include "Entity.hpp" // Ensure this path correctly points to your Entity class definition
#include <iostream>
class Enemy : public Entity {
public:
    Enemy(char character = 'E', int health = 10); // Default character 'E' and health 10
    void TakeDamage(int damage);
    bool IsAlive() const;
    /*Vector2D GetPosition() 
    { 
        std::cout << "Enemy position: " << m_position.x << ", " << m_position.y << std::endl;
        return m_position; 
    }*/


private:
    int m_health;
    char m_character; 
};

