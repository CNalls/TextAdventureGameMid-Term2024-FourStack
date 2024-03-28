#pragma once
#include <iostream>
#include "Entity.hpp" // Ensure this path is correct for your project structure
#include "Room.hpp" // Forward declaration

class Player : public Entity {
public:
    Player();
    Player(Room* room);
    void Start();
    void Update();
    void TakeDamage(int damage);
    bool IsAlive() const;
    void Reset();

private:
    Room* room;
    int m_health;
    int m_keyCount;
};

