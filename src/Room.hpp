#pragma once
#include "fogpi/Math.hpp"

#include <string>
#include <vector>
#include <algorithm>
#include "Entity.hpp"
#include "Door.hpp"
#include <iostream>


class Room {
public:
    void Load(std::string _path);
    void Draw();
    void Update();

    bool StillPlaying() { return true; }

    Entity& GetPlayer() { return *m_player; }
    std::vector<Entity*>& GetMonsters() { return m_monsters; }
    const std::vector<std::vector<char>>& GetMap() { return m_map; }
    char GetLocation(Vector2D _pos);
    void ClearLocation(Vector2D _pos);
    void OpenDoor(Vector2D _pos);
    char GetLocationType(Vector2D _pos);
    void DecreaseEnemyCount() 
    {
        int newCount = m_enemyCount - 1;
        m_enemyCount = (newCount > 0) ? newCount : 0;
    }

private:
    Entity *m_player = nullptr;
    int m_enemyCount = 0;
    std::vector<Entity*> m_monsters;
    std::vector<std::vector<char>> m_map;
    std::vector<Door> m_doors;
};