#pragma once

#include "Entity.hpp"
#include <iostream>

class Player : public Entity
{
public:
    void Start();
    void Update();
    Vector2D GetPosition() 
    { 
    std::cout << "Player position: " << m_position.x << ", " << m_position.y << std::endl;
    return m_position; 
    }
private:
    int m_keyCount = 0;
    int m_goldCount = 0;
    int m_chestCount = 0;
    //these are the things that you can interact with on the map

};