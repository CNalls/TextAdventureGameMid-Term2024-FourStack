#include "R_Enemy.hpp"
#include "fogpi/fogpi.hpp"
#include "fogpi/Math.hpp"
#include "Room.hpp"
#include <string>
//#include "Stats.hpp"
void R_Enemy::Start()
{
    m_character = '-';

    Stats rEnemyStats
    {
        .strength = 3.0f,
        .dexterity = 8.0f,
        .constitution = 4.0f
    };
    
}

void R_Enemy::Update()
{
     
}