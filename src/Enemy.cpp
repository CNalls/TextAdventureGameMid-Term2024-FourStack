#pragma once
#include "Enemy.hpp"

Enemy::Enemy(char character, int health) : m_character(character), m_health(health) {
}
void Enemy::TakeDamage(int damage) {
    m_health -= damage;
   
}

bool Enemy::IsAlive() const {
    return m_health > 0;
}