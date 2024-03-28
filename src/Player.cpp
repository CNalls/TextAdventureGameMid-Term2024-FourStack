#include "Player.hpp"
#include "fogpi/fogpi.hpp"
#include "fogpi/Math.hpp"
#include "Room.hpp"
#include <string>
#include <random>
#include <ctime>

int rollDice() 
{
    static std::mt19937 rng(static_cast<unsigned int>(time(0))); // Seed with time
    std::uniform_int_distribution<int> distribution(1, 6); // 1 to 6
    return distribution(rng);
}

void Player::Start()
{
    m_character = 'P';

    Stats playerStats
    {
        .strength = 5.0f,
        .dexterity = 6.0f,
        .constitution = 8.0f
    };
}

void Player::Update()
{
    // direction
    std::string instruction = "wasd and Enter to move, press h for help";
    char directionInput = 'r';
    Vector2D direction(0.0f, 0.0f);

    while(directionInput != 'w' &&
          directionInput != 'a' &&
          directionInput != 's' &&
          directionInput != 'd' && 
          directionInput != 'h')
    {
        directionInput = request_char(instruction.c_str());
    }

    if (directionInput == 'w')
        direction = Vector2D(0.0f, -1.0f);
    if (directionInput == 'a')
        direction = Vector2D(-1.0f, 0.0f);
    if (directionInput == 's')
        direction = Vector2D(0.0f, 1.0f);
    if (directionInput == 'd')
        direction = Vector2D(1.0f, 0.0f);
    // HELP MENU
    if (directionInput == 'h')
    {
        std::cout << "P   the player" << std::endl;
        std::cout << "L   these are doors, they are all locked" << std::endl;
        std::cout << "K   these are keys, you need these to open doors" << std::endl;
        std::cout << "G   this is gold" << std::endl;
        std::cout << "-   these are ranged enemies" << std::endl;
        std::cout << "+   these are melee enemies" << std::endl;
        std::cout << std::endl;
    
    Vector2D newPosition = m_position + direction;

// Check for an enemy encounter
    if (room->GetLocation(newPosition) == 'E') { // Assuming 'E' is a placeholder for actual enemy symbols
        char enemyType = room->GetLocationType(newPosition); // Make sure you've implemented this method in the Room class
        int enemyHealth = (enemyType == 'M' ? 5 : 10); // Mimic or ranged enemy health
    
        std::cout << "You encountered a " << (enemyType == 'M' ? "Mimic!" : "Archer!") << "! Press 'r' to roll the dice." << std::endl;
    
        while (m_health > 0 && enemyHealth > 0) {
            std::cout << "Press 'r' to roll: ";
            char input;
            std::cin >> input; // Assuming input validation is done elsewhere
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
            if (input == 'r') {
                int playerRoll = rollDice();
                int enemyRoll = rollDice();
                std::cout << "You rolled: " << playerRoll << ", Enemy rolled: " << enemyRoll << std::endl;
            
                // Damage calculation based on the rolls
                m_health -= enemyRoll; // Player takes damage equal to the enemy's roll
                enemyHealth -= playerRoll; // Enemy takes damage equal to the player's roll
            
                std::cout << "You took " << enemyRoll << " damage! Your health: " << m_health << std::endl;
                std::cout << "Enemy took " << playerRoll << " damage! Enemy health: " << enemyHealth << std::endl;
            }
        
            if (m_health <= 0) {
                std::cout << "You were defeated by the enemy! Game Over." << std::endl;
                // Handle player defeat (e.g., end game)
                exit(0);
                break;
            } else if (enemyHealth <= 0) {
                std::cout << "You defeated the enemy!" << std::endl;
                room->ClearLocation(newPosition); // Remove the enemy from the map
                break;
            }
        }
    
        return; // Skip moving into the enemy's space if combat initiated
    }


    // check for key
    if (room->GetLocation(m_position + direction) == 'K')
    {
        m_keyCount++;
        printf("You Picked Up A Key: %i \n" ,m_keyCount ); 
        room->ClearLocation(m_position + direction);
    }

    // check for lock
    if (room->GetLocation(m_position + direction) == 'L')
    {
        if (m_keyCount <= 0)
            return;
        //check how do we know we have keys and try to add this to the 
        m_keyCount --;
        room->OpenDoor(m_position + direction);
    }

    // check for door
    if (room->GetLocation(m_position + direction) == 'D')
    {
        room->OpenDoor(m_position + direction);
    }

    //check for gold
    if (room->GetLocation(m_position + direction) == 'G')
    {
        m_goldCount++;
        printf("You Picked Up Gold: %i \n" ,m_goldCount );
        //printf("%i \n" ,m_goldCount);
        room->ClearLocation(m_position + direction);
    }

    //check for item purchase
    //For example, sword, bow, buckler, shield, potion, Machine for gambling machine
    //a weapon that costs 999 gold but one shots everything with a 100% crit chance and accuracy rate
    if (room->GetLocation(m_position + direction) == 'G')
    {
        if (m_goldCount <= 0)
            return;
        m_goldCount--;
        room->ClearLocation(m_position + direction);
    }

    //check for chest
    if (room->GetLocation(m_position + direction) == 'C')
    {
        if (m_keyCount <= 0)
            return;
        //check how do we know we have keys and try to add this to the 
        m_chestCount --;
        room->OpenDoor(m_position + direction);
    }

    // try to move
    if (room->GetLocation(m_position + direction) == ' ')
        m_position += direction;
}


