#include "Player.hpp"
#include "Chest.hpp"
#include "fogpi/fogpi.hpp"
#include "fogpi/Math.hpp"
#include "Room.hpp"
#include <string>

// Define the possible drops
enum Drop {
    Gold,
    Potion,
    Key,
    Wand,
    Staff,
    Spear,
    Dirk,
    Dagger,
    Bow,
    Flintlock,
    LeatherArmor,
    Chainmail,
    HeavyCuirras
};

// Function to simulate dropping one of the items randomly
int dropItem() {
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Define the distribution of drops
    std::vector<Drop> possibleDrops = {Drop::Gold, Drop::Potion, Drop::Key, Drop::Wand, Drop::Staff, Drop::Spear, Drop::Dirk, Drop::Dagger, Drop::Bow, Drop::Flintlock, Drop::LeatherArmor, Drop::Chainmail, Drop::HeavyCuirras};
    std::uniform_int_distribution<> dis(0, possibleDrops.size() - 1);
    
    // Generate a random index
    int index = dis(gen);
    
    // Return the corresponding drop
    
    return (Drop)(rand()%13);
}

int ChestRand() {
    // Simulate dropping items from the chest
    std::cout << "You Have Opened a Chest, and Inside you Find: ";
    switch(dropItem()) {
        case Drop::Gold:
            std::cout << "Gold... That's it...";
            break;
        case Drop::Potion:
            std::cout << "A Potion, or Alchohol...";
            break;
        case Drop::Key:
            std::cout << "A Key! I Wonder what This Opens...";
            break;
        case Drop::Wand:
            std::cout << "A Magic Wand! It Still Lingers With Energy...";
            break;
        case Drop::Staff:
            std::cout << "A Magic Staff! Or a Stick,  Same Stuff Really...";
            break;
        case Drop::Spear:
            std::cout << "A Very Pointy Stick! Spear Aquired...";
            break;
        case Drop::Dirk:
            std::cout << "Isn't this just a Dagger? Dirk Aquired...";
            break;
        case Drop::Dagger:
            std::cout << "The Rogues Favorite Tool, LOOK! It still had blood on it! Dagger Aquired...";
            break;
        case Drop::Bow:
            std::cout << "LOOK OUT THEY'RE IN THE TREES! Bow Aquired...";
            break;
        case Drop::Flintlock:
            std::cout << "Wait a Minute, This isn't Supposed to be here... Flintlock Aquired...";
            break;
        case Drop::LeatherArmor:
            std::cout << "Literally Rags, Basically a Potato Sack. Try Not to Get Hit. Leather Armor Aquired...";
            break;
        case Drop::Chainmail:
            std::cout << "Ah Yes, True Chainlinked Armor, Watch Out For Blunt Trauma! Chainmail Aquired...";
            break;
        case Drop::HeavyCuirras:
            std::cout << "It Will Be Hard To Get Through This Hunk of Metal! Heavy Armor Aquired...";
            break;
            //case Drop::BootsOfPerpetualMovement:
            //std::cout << "a Key";
            //break;
           // case Drop::SwordOfChance:
            //std::cout << "a Key";
           // break;
    }
    std::cout << std::endl;

    

    return 0;
}

void Player::Start()
{
    m_character = 'P';
}

void Player::Update()
{
    // direction
    std::string instruction = "wasd and Enter to move";
    char directionInput = 'r';
    Vector2D direction(0.0f, 0.0f);

    while(directionInput != 'w' &&
          directionInput != 'a' &&
          directionInput != 's' &&
          directionInput != 'd')
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
        printf("You Have Used a Key to Open this Door: %i \n" ,m_keyCount);
        room->OpenDoor(m_position + direction);
        //future lock that says (the key doesnt fit)  and is like a boss room key
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
        //we gonna have to builda  shop level for this one
        room->ClearLocation(m_position + direction);
    }

    //check for chest
    if (room->GetLocation(m_position + direction) == 'C')
    {
        if (m_keyCount <= 0)
        {
            printf("You Lack The Required Item for this: %i \n" ,m_keyCount );
            return;
        }
    }      

    if (room->GetLocation(m_position + direction) == 'L')
    {
        if (m_keyCount <= 0)
        {
            printf("You Lack The Required Item for this, AKA YOU SHALL NOT PASS!: %i \n" ,m_keyCount );
            return;
        }
    }        
///////////////////////
        //check how do we know we have keys and try to add this to the 
        if (room->GetLocation(m_position + direction) == 'C')
    {
        m_keyCount --;
        printf("You Have Used a Key to Open the Chest. Keys Left: %i \n" ,m_keyCount );
        printf(" %i " , ChestRand());
        printf("Key Count: %i \n" ,m_keyCount );
        m_goldCount++;
        printf("Gold Count: %i \n" ,m_goldCount );

        room->ClearLocation(m_position + direction);
    }

    //Check for gold after death
    // need to change this to however death screen looks
    if (room->GetLocation(m_position + direction) == 'M')
    {
        m_goldCount--;
        printf("You Have Been Looted For a Random Amount of Gold: %i \n" ,m_goldCount );
        room->ClearLocation(m_position + direction);
    }
/////////////////////
    // try to move
    if (room->GetLocation(m_position + direction) == ' ')
        m_position += direction;

    //make a gamble random machine 
    //Make merchant area, backup code, make a demo enemy area and see if I can get stats to print out on enemy, see if i can make a while loop that makes a combat for an enemy that occurs after walking over the enemy (if possible add ai where it moves a random spot every time you input WASD) )
}