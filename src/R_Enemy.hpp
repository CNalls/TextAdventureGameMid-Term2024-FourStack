#pragma once
#include "Entity.hpp"


class R_Enemy : public Entity
{
public:
    void Start();
    void Update();
private:
    
    int m_goldCount = 0;
    //these are the things that you can interact with on the map
};