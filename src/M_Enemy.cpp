#include "M_Enemy.hpp"
#include "fogpi/fogpi.hpp"
#include "fogpi/Math.hpp"
#include "Room.hpp"
#include <string>
//#include "Stats.hpp"
void M_Enemy::Start()
{
    m_character = '+';

    Stats mEnemyStats
    {
        .strength = 7.0f,
        .dexterity = 5.0f,
        .constitution = 7.0f
    };
    
}

void M_Enemy::Update()
{
     
}