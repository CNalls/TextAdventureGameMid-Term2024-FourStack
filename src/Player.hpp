#pragma once

#include "Entity.hpp"

class Player : public Entity
{
public:
    void Start();
    void Update();
    void RestoreHealth();
private:
    int m_health = 40; //change player health here 
    const int m_maxHealth = 40;
    int m_keyCount = 0;
    int m_goldCount = 0;
    int m_chestCount = 0;
    int m_randomItemCount = 0;
    int m_dropItem = 0;
    int m_enemykillCount = 0;

    
    
    //could do int 1 = gold, int 2 = weapon etc instead
    //int m_enemyMeleeEnem = 0;
    //int m_enemyRangedEnem = 0;
    //these are the things that you can interact with on the map
    
};

