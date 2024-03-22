#pragma once

#include "Entity.hpp"

class Player : public Entity
{
public:
    void Start();
    void Update();
private:
    int m_keyCount = 0;
    int m_goldCount = 0;
    int m_chestCount = 0;
    int m_randomItemCount = 0;
    //int m_enemyMeleeEnem = 0;
    //int m_enemyRangedEnem = 0;
    //these are the things that you can interact with on the map

};