#pragma once

#include <string>
#include "fogpi/Math.hpp"
#include "Stats.hpp"

class Room;

class Entity {
public:
    Room* room;
    Stats stats;

    void Init(unsigned int _x, unsigned int _y) { m_position = Vector2D(_x, _y); }

    virtual void Start() {}
    virtual void Update() {}

    char Draw() { return m_character; }
    Vector2D GetPosition() { return m_position; }
protected:
    Vector2D m_position;
    char m_character;
    
};
