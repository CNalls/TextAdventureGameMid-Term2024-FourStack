#include <iostream>
#include <random>
#include <vector>
#include "Chest.hpp"
#include "fogpi/fogpi.hpp"
#include "fogpi/Math.hpp"
#include "Room.hpp"
#include <string>

// Define the possible drops
enum class Drop {
    Gold,
    Weapon,
    Armor,
    Potion
};

// Function to simulate dropping one of the items randomly
Drop dropItem() {
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Define the distribution of drops
    std::vector<Drop> possibleDrops = {Drop::Gold, Drop::Weapon, Drop::Armor, Drop::Potion};
    std::uniform_int_distribution<> dis(0, possibleDrops.size() - 1);
    
    // Generate a random index
    int index = dis(gen);
    
    // Return the corresponding drop
    return possibleDrops[index];
}

int ChestRand() {
    // Simulate dropping items from the chest
    std::cout << "You opened the chest and found: ";
    switch(dropItem()) {
        case Drop::Gold:
            std::cout << "Gold";
            break;
        case Drop::Weapon:
            std::cout << "a Weapon";
            break;
        case Drop::Armor:
            std::cout << "Armor";
            break;
        case Drop::Potion:
            std::cout << "a Potion";
            break;
    }
    std::cout << std::endl;

    return 0;
}