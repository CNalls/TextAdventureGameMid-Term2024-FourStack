#pragma once
#include <iostream>

struct Stats
{
    float maxHealth = 10.0f;
    float strength = 10.0f;
    float dexterity = 10.0f;
    float constitution = 10.0f;
};

int main()
{
        // Create instances of Stats for Enemy 1 and Enemy 2
    Stats physEnemyStats;
    Stats rangeEnemyStats;

    // Modify the stats for each enemy as needed
    physEnemyStats.maxHealth = 15.0f;
    physEnemyStats.strength = 12.0f;
    physEnemyStats.dexterity = 8.0f;

    rangeEnemyStats.maxHealth = 12.0f;
    rangeEnemyStats.strength = 10.0f;
    rangeEnemyStats.constitution = 11.0f;

    // Display the stats for each enemy
    std::cout << "Enemy 1 Stats:" << std::endl;
    std::cout << "Max Health: " << physEnemyStats.maxHealth << std::endl;
    std::cout << "Strength: " << physEnemyStats.strength << std::endl;
    std::cout << "Dexterity: " << physEnemyStats.dexterity << std::endl;
    std::cout << "Constitution: " << physEnemyStats.constitution << std::endl;

    std::cout << "\nEnemy 2 Stats:" << std::endl;
    std::cout << "Max Health: " << rangeEnemyStats.maxHealth << std::endl;
    std::cout << "Strength: " << rangeEnemyStats.strength << std::endl;
    std::cout << "Dexterity: " << rangeEnemyStats.dexterity << std::endl;
    std::cout << "Constitution: " << rangeEnemyStats.constitution << std::endl;

    return 0;
}


