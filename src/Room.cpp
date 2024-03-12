#include "Room.hpp"

#include "Player.hpp"
#include "Enemy.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>


void Room::Load(std::string _path) {
    m_map.clear();
    m_enemies.clear(); // Clear previous enemies when loading a new room
    m_doors.clear(); // Clear previous doors when loading a new room

    std::ifstream file;
    file.open(_path);

    if (!file.is_open()) {
        printf("file not found at: %s \n", _path.c_str());
        exit(1);
    }

    std::string word;
    int number;

    while (file >> word) {
        if (word == "level") {
            if (file >> number) {
                printf("open level: %i\n", number);
            }
        }

        if (word == "next_level") {
            if (file >> word) {
                m_doors.push_back(Door());
                m_doors[m_doors.size() - 1].path = word;
            }
        }

        if (word == "map") {
            m_map.push_back(std::vector<char>());
            while(file >> word) {
                if (word == "-2") {
                    break;
                }

                if (word == "-1") {
                    m_map.push_back(std::vector<char>());
                    continue;
                }

                if (word == "0")
                    m_map[m_map.size() - 1].push_back(' ');
                else
                    m_map[m_map.size() - 1].push_back(word[0]);
            }
        }
    }

    // Spawn enemies from the map data
    for (int y = 0; y < m_map.size(); y++) {
        for (int x = 0; x < m_map[y].size(); x++) {
            if (m_map[y][x] == 'E') {
                // Create an enemy object and add it to the room
                Enemy* enemy = new Enemy();
                enemy->Init(x, y);
                m_enemies.push_back(enemy);

                // Replace 'E' with a space character in the map
                m_map[y][x] = 'E';
            }

            // Spawn player if 'S' character is found in the map
            if (m_map[y][x] == 'S') {
                if (m_player == nullptr)
                    m_player = new Player();
                m_player->Init(x, y);
                m_player->Start();
                m_map[y][x] = ' '; // Clear player spawn position in the map
            }
        }
    }
}




void Room::Update() {
    Draw();

    // Update player position
    if (m_player != nullptr) {
        m_player->room = this;
        m_player->Update();
    }

    // Check for collision with enemies
    for (Entity* enemy : m_enemies) {
        if (m_player->GetPosition() == enemy->GetPosition()) {
            std::cout << "Player position: " << m_player->GetPosition().x << ", " << m_player->GetPosition().y << std::endl;
            std::cout << "Enemy position: " << enemy->GetPosition().x << ", " << enemy->GetPosition().y << std::endl;

            // Engage in combat
            HandleCombat(m_player, enemy);
            return; // Combat ends after one round
        }
    }
}






void Room::Draw()
{
    for (int y = 0; y < m_map.size(); y++)
    {
        for (int x = 0; x < m_map[y].size(); x++)
        {
            printf("%c ", GetLocation(Vector2D(x, y)));
        }
        printf("\n");
    }
}


Entity* Room::GetEnemyAtPosition(Vector2D position) {
    for (Entity* enemy : m_enemies) {
        if (enemy->GetPosition() == position) {
            return enemy;
        }
    }
    return nullptr; 
}

char Room::GetLocation(Vector2D _pos)
{
    if (_pos.y >= m_map.size())
        return ' ';
    
    if (_pos.x >= m_map[_pos.y].size())
        return ' ';

    if (m_player != nullptr)
        if (m_player->GetPosition() == _pos)
            return m_player->Draw();
    
    return m_map[_pos.y][_pos.x];
}

void Room::ClearLocation(Vector2D _pos)
{
    if (_pos.y >= m_map.size())
        return;
    
    if (_pos.x >= m_map[_pos.y].size())
        return;
    
    m_map[_pos.y][_pos.x] = ' ';
}

void Room::OpenDoor(Vector2D _pos)
{
    for(int i = 0; i < m_doors.size(); i++)
    {
        if (m_doors[i].pos == _pos)
        {
            Load(m_doors[i].path);
        }
    }
}


// Constructor for Room class
Room::Room() {
    // Seed the random number generator with current time
    srand(static_cast<unsigned int>(time(nullptr)));
}

void Room::HandleCombat(Entity* player, Entity* enemy) 
{
    // Prompt the user to roll the dice
    std::cout << "Press 'r' to roll the dice: ";
    char roll;
    std::cin >> roll;
    
    // Check if the user rolled the dice
    if (roll == 'r') {
        // Roll a 6-sided dice for player and enemy
        int playerRoll = rand() % 6 + 1;
        int enemyRoll = rand() % 6 + 1;

        // Output rolls for debugging
        std::cout << "Player rolled: " << playerRoll << std::endl;
        std::cout << "Enemy rolled: " << enemyRoll << std::endl;

        // Determine the winner based on the dice rolls
        if (playerRoll >= enemyRoll) {
            std::cout << "Player defeats the enemy!" << std::endl;
            // Remove the defeated enemy from the room
            auto it = std::find(m_enemies.begin(), m_enemies.end(), enemy);
            if (it != m_enemies.end()) {
                m_enemies.erase(it);
                delete enemy;
            }
        } else {
            std::cout << "Enemy defeats the player!" << std::endl;
            // Handle player defeat (e.g., game over)
        }
    }
}
