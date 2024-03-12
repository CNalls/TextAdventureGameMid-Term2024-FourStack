#pragma once

#include "Entity.hpp"

class Enemy : public Entity {
public:
    Enemy() {
        m_character = 'E'; // Set character representation for enemy
    }
Vector2D GetPosition() 
{ 
    std::cout << "Enemy position: " << m_position.x << ", " << m_position.y << std::endl;
    return m_position; 
}
};
