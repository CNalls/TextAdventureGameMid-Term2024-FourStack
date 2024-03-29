#pragma once
#include <iostream>

struct Stats
{
    float maxHealth = 10.0f;
    float strength = 10.0f;
    float dexterity = 10.0f;
    float constitution = 10.0f;
};

static int StatMenu()
{
    // Create instances of Stats for the Melee and Ranged Enemies
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
    //these will print if the enemy unit is walked over
    
    //printf("Melee Enemy Stats: %i \n" ,physEnemyStats.maxHealth );



    //std::cout << "Melee Enemy Stats:" << std::endl;
    //std::cout << "Max Health: " << physEnemyStats.maxHealth << std::endl;
    //std::cout << "Strength: " << physEnemyStats.strength << std::endl;
    //std::cout << "Dexterity: " << physEnemyStats.dexterity << std::endl;
    //std::cout << "Constitution: " << physEnemyStats.constitution << std::endl;

    //std::cout << "\nRanged Enemy Stats:" << std::endl;
    //std::cout << "Max Health: " << rangeEnemyStats.maxHealth << std::endl;
    //std::cout << "Strength: " << rangeEnemyStats.strength << std::endl;
    //std::cout << "Dexterity: " << rangeEnemyStats.dexterity << std::endl;
    //std::cout << "Constitution: " << rangeEnemyStats.constitution << std::endl;

    return 0;
}


