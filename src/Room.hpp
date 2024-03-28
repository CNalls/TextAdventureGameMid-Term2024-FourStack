#pragma once
#include "fogpi/Math.hpp"

#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Entity.hpp"
#include "Door.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

class Player;
class Room {
public:
    void Load(std::string _path);
    void Draw();
    void Update();
    Room();
    void SetPlayer(Player* player); 
    void AddEnemy(Enemy* enemy);
    void HandleCombat(Entity* player, Entity* enemy);

    bool StillPlaying() { return true; }

    Entity& GetPlayer() { return *m_player; }
    std::vector<Entity*>& GetMonsters() { return m_monsters; }
    const std::vector<std::vector<char>>& GetMap() { return m_map; }
    char GetLocation(Vector2D _pos);
    Entity* GetEnemyAtPosition(Vector2D position);
    int GetHeight() const { return m_map.size(); }
    int GetWidth() const 
    {
        if (m_map.empty()) 
        {
            return 0; // Return 0 if the map is empty
        }
        return m_map[0].size(); // Return the width of the first row
    }
    void Combat(Entity* player, Entity* enemy);
    void RemoveEnemy(Entity* enemy) 
    {
        auto it = std::find(m_enemies.begin(), m_enemies.end(), enemy);
        if (it != m_enemies.end()) 
        {
            m_enemies.erase(it);
            delete enemy;
        }
    }
    void ClearLocation(Vector2D _pos);
    void OpenDoor(Vector2D _pos);
private:
    Entity *m_player = nullptr;
    std::vector<Entity*> m_enemies = {};
    std::vector<Entity*> m_monsters;
    std::vector<std::vector<char>> m_map;
    std::vector<Door> m_doors;
};