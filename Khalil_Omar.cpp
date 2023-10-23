// Khalil_Omar.zip
// This is my final project for c++, the game: Durak - Family Edition
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>  // for std::setw

struct CARD {
    int num;
    std::string shape;
}; // struct for card

void shuffle(std::vector<CARD> & allCards); 
void deal(std::vector<CARD> & allCards, std::vector<CARD> & deal1, std::vector<CARD> & deal2, std::vector<CARD> & deal3, std::vector<CARD> & deal4);
void reveal(std::vector<CARD> & allCards, std::vector<CARD> & deal);
int attack(std::vector<CARD> & allCards, std::vector<CARD> & deal, std::vector<CARD> & tables);
int defend(std::vector<CARD> & allCards, std::vector<CARD> & deal, std::vector<CARD> & tables);
int attackvalidation(std::vector<CARD> & allCards, std::vector<CARD> & deal, std::vector<CARD> & tables, int & numplayed);
int defendvalidation(std::vector<CARD> & allCards, std::vector<CARD> & deal, std::vector<CARD> & tables, int & numdefended);

int main(int argc, char const *argv[])
{
    std::vector<CARD> deck; // all cards
    CARD vecstruct; // vector that holds card name and shape
    std::string player[4]; // save each player's name
    std::vector<CARD> hand1, hand2, hand3, hand4; // vector for each hand
    std::vector<CARD> table; // vector for cards played on table
    const char * dares[16] = { // dares to be selected randomly
        "Do 10 push ups.",
        "Show the most embaressing photo on your phone.",
        "Do an impression of a celebrity … and keep going with it until the group guess who you are!",
        "Crawl a lap around the room.",
        "Confess something you never told your friends before.",
        "Drink water without using your hand.",
        "Hold a handstand for as long as you can.",
        "Do the worm for 30 seconds.",
        "Talk in a british accent for the next round.",
        "Talk to the wall as if it was someone starting a fight with you. Argue back at it.",
        "Make every person in the group smile… and keep going until every single person has cracked a smile!",
        "Spin around 20 times then try to walk straight.",
        "Stand up and tell everyone your BEST joke. They can then rate it on a scale of 1-10.",
        "Call a friend and pick a fight with them about something ridiculous.",
        "Allow your friends to write something embarrassing somewhere on your body (that can be hidden with clothing) with a permanent marker.",
        "Attempt to moonwalk."    
    };
    
    //instructions
    std::cout << "\nWelcome to Durak - Family Edition!" << "\nGather a group of 4 people and the first " 
    << "person to rid of their hand gets to watch the rest perform a dare!\n" << std::endl
    << "RULES:\nEach player gets 6 cards (Highest to lowest - 10, 9, 8, 7, 6, 5).\nA card can be defended by either playing a higher card of the " <<
    "same shape, or by playing any Spade (The Strong Suit) card.\nA player can keep attacking any number that is on the table.\n" <<
    "If a player successfully defended an attack, they get to attack the next player. If they cannot, they pick up all cards on the table, " <<
    "their turn gets skipped, and the next player attacks.\n" << std::endl << "That is enough of me explaining. Let's see who is the DURAK!\n" << std::endl;

    for(int i = 0; i < 4; i++){ // get players names
        std::cout << "Enter Player " << i + 1 << "'s Name: ";
        getline(std::cin, player[i]);
    }

    //create deck of cards
    for(int i = 0; i < 24; i++){
        if(i < 6){
            vecstruct.num = i + 5;
            vecstruct.shape = "Spade";
        }
        else if(i > 5 && i < 12){
            vecstruct.num = i - 1;
            vecstruct.shape = "Club";
        }
        else if(i > 11 && i < 18){
            vecstruct.num = i - 7;
            vecstruct.shape = "Diamond";
        }
        else if(i > 17 && i < 24){
            vecstruct.num = i - 13;
            vecstruct.shape = "Heart";
        }
        deck.push_back(vecstruct);
        //std::cout << deck[i].num << " " << deck[i].shape << "\n\n"; // for testing
    }


    shuffle(deck); // call shuffle function
    deal(deck, hand1, hand2, hand3, hand4); // call deal function

    srand(time(NULL)); 
    int i = rand() % 4; // randomizing which player starts first
    int tempnum1 = 1; 
    int tempnum2 = 1; // as long as they are 1, attack and defend keeps going

    while(hand1.size() != 0 || hand2.size() != 0 || hand3.size() != 0 || hand4.size() != 0){ // playing stops once a player gets rid of their hand
        if(i == 0){ // player 0 attacking 1
            
                std::cout << "\n\nPress enter to reveal " << player[i] << "'s cards.";
                reveal(deck, hand1);
                std::cout << "\n" << player[i] << ", please attack " << player[i + 1] << " (1-6 or 0 to stop attacking): ";
                tempnum1 = attack(deck, hand1, table);
                if(hand1.size() == 0){
                    break;
                }
                if(tempnum1 == 0){
                }
                else {
                    std::cout << "\n\nPress enter to reveal " << player[i + 1] << "'s cards.";
                    reveal(deck, hand2);
                    std::cout << "\n\n" << player[i + 1] << ", please defend " << player[i] << "'s attack (1-6 or or 0 to stop defending): ";
                    tempnum2 = defend(deck, hand2, table);
                    if(hand2.size() == 0){
                        break;
                    }
                    if(tempnum2 == 0){
                    }
                }
        }   
        else if(i == 1){ // player 1 attacking 2
            
                std::cout << "\n\nPress enter to reveal " << player[i] << "'s cards.";
                reveal(deck, hand2);
                std::cout << "\n" << player[i] << ", please attack " << player[i + 1] << " (1-6 or 0 to stop attacking): ";
                tempnum1 = attack(deck, hand2, table);
                if(hand2.size() == 0){
                        break;
                }
                if(tempnum1 == 0){
                }
                else {
                    std::cout << "\n\nPress enter to reveal " << player[i + 1] << "'s cards.";
                    reveal(deck, hand3);
                    std::cout << "\n\n" << player[i + 1] << ", please defend " << player[i] << "'s attack (1-6 or or 0 to stop defending): ";
                    tempnum2 = defend(deck, hand3, table);
                    if(hand3.size() == 0){
                        break;
                    }
                    if(tempnum2 == 0){
                    }
                }
        }
        else if(i == 2){ // player 2 attacking 3
            
                std::cout << "\n\nPress enter to reveal " << player[i] << "'s cards.";
                reveal(deck, hand3);
                std::cout << "\n" << player[i] << ", please attack " << player[i + 1] << " (1-6 or 0 to stop attacking): ";
                tempnum1 = attack(deck, hand3, table);
                if(hand3.size() == 0){
                        break;
                }
                if(tempnum1 == 0){
                }
                else {
                    std::cout << "\n\nPress enter to reveal " << player[i + 1] << "'s cards.";
                    reveal(deck, hand4);
                    std::cout << "\n" << player[i + 1] << ", please defend " << player[i] << "'s attack (1-6 or or 0 to stop defending): ";
                    tempnum2 = defend(deck, hand4, table);
                    if(hand4.size() == 0){
                        break;
                    }
                    if(tempnum2 == 0){
                    }
                }
        }
        else if(i == 3){ // player 3 attacking 0
            
                std::cout << "\n\nPress enter to reveal " << player[i] << "'s cards.";
                reveal(deck, hand4);
                std::cout << "\n\n" << player[i] << ", please attack " << player[i - 3] << " (1-6 or 0 to stop attacking): ";
                tempnum1 = attack(deck, hand4, table);
                if(hand4.size() == 0){
                        break;
                }
                if(tempnum1 == 0){
                }
                else {
                    std::cout << "\n\nPress enter to reveal " << player[i - 3] << "'s cards.";
                    reveal(deck, hand1);
                    std::cout << "\n\n" << player[i - 3] << ", please defend " << player[i] << "'s attack (1-6 or or 0 to stop defending): ";
                    tempnum2 = defend(deck, hand1, table);
                    if(hand1.size() == 0){
                        break;
                    }
                }
        }
        else { // if i >= 4, break from the if statements
            break;
        }
        
        if(tempnum1 == 0){ // if a player defends, they attack next
            i += 1;
        }
        
        if(tempnum2 == 0){ // if a player doesnt defend, their turn is skipped
            i += 2;
        }
        
        if(i >= 4){ // circling back when > 3
            i = i - 4;
        }

    }
    
    srand(unsigned(time(NULL)));
    int random1 = rand() % 16;
    int random2 = rand() % 16;
    int random3 = rand() % 16;
    if(hand1.size() == 0){
        std::cout << "\n\nCongrats " << player[0] << "! Now it's time for " << player[1] << ", " << player[2] << ", and " << player[3] << " to perform a dare\n" << std::endl;
        std::cout << "The dare for " << player[1] << " is: " << dares[random1] << std::endl;
        std::cout << "The dare for " << player[2] << " is: " << dares[random2] << std::endl;
        std::cout << "The dare for " << player[3] << " is: " << dares[random3] << std::endl;
    }
    else if(hand2.size() == 0){
        std::cout << "\n\nCongrats " << player[1] << "! Now it's time for " << player[0] << ", " << player[2] << ", and " << player[3] << " to perform a dare!\n" << std::endl;
        std::cout << "The dare for " << player[0] << " is: " << dares[random1] << std::endl;
        std::cout << "The dare for " << player[2] << " is: " << dares[random2] << std::endl;
        std::cout << "The dare for " << player[3] << " is: " << dares[random3] << std::endl;
    }
    else if(hand3.size() == 0){
        std::cout << "\n\nCongrats " << player[2] << "! Now it's time for " << player[0] << ", " << player[1] << ", and " << player[3] << " to perform a dare!\n" << std::endl;
        std::cout << "The dare for " << player[0] << " is: " << dares[random1] << std::endl;
        std::cout << "The dare for " << player[1] << " is: " << dares[random2] << std::endl;
        std::cout << "The dare for " << player[3] << " is: " << dares[random3] << std::endl;
    }
    else if(hand4.size() == 0){
        std::cout << "\n\nCongrats " << player[3] << "! Now it's time for " << player[0] << ", " << player[1] << ", and " << player[2] << " to perform a dare!\n" << std::endl;
        std::cout << "The dare for " << player[0] << " is: " << dares[random1] << std::endl;
        std::cout << "The dare for " << player[1] << " is: " << dares[random2] << std::endl;
        std::cout << "The dare for " << player[2] << " is: " << dares[random3] << std::endl;
    }

    std::cout << "\nThanks for playing Durak - Family Edition!\nI hope you enjoyed.\n" << std::endl;

    return 0;
}

void shuffle(std::vector<CARD> & allCards){ // function for shuffling all cards
    srand(time(0));
    for(int i = 0; i < 24; i++){
        int r = i + (rand() % (24 - i));
        std::swap(allCards[i].num, allCards[r].num);
        std::swap(allCards[i].shape, allCards[r].shape);
        //std::cout << allCards[i].num << allCards[i].shape << std::endl; // for testing
    }
}


void deal(std::vector<CARD> & allCards, std::vector<CARD> & deal1, std::vector<CARD> & deal2, std::vector<CARD> & deal3, std::vector<CARD> & deal4){
     for(int i = 0; i < 24; i++){ // functions deals 6 cards to each player after shuffled
         if(i < 6)
             deal1.push_back(allCards[i]);
         else if(i > 5 && i < 12)
             deal2.push_back(allCards[i]);
         else if(i > 11 && i < 18)
             deal3.push_back(allCards[i]);
         else if(i > 17 && i < 24)
             deal4.push_back(allCards[i]);
     }
}

void reveal(std::vector<CARD> & allCards, std::vector<CARD> & deal){ // allows other players to look away while a player plays their turn
    
    while((std::cin.get()) != '\n'); // to allow the player to reveal hand
    for(int i = 0; i < deal.size(); i++){
        std::cout << i + 1 << std::setw(3) << "|" << deal[i].num << " " << deal[i].shape << std::endl; // print cards with equal indentation
    }
}

int attack(std::vector<CARD> & allCards, std::vector<CARD> & deal, std::vector<CARD> & tables){ // function for a player attacking another
    
    int tempnum1;

        while(attackvalidation(allCards, deal, tables, tempnum1) == 0){ // player asked to pick a card to attack with it, input validation for 0-6 inclusive
            std::cout << "The card played is not allowed. Pick another card: ";
            std::cin.clear(); //clearing the failbit
            //while((std::cin.get()) != '\n'); // clear input buffer
        }

        if(tempnum1 == 0){ // for stopping the attack
            system("clear");
            std::cout << "\nAttack Successfully Defended!";
            for(int i = tables.size(); i > 0; i--){
                tables.erase(tables.begin() + i - 1); // when attack is stopped, table is cleared 
            }
        }
        else {
            tables.push_back(deal[tempnum1 - 1]); // the card player added to table
            system("clear");
            std::cout << "Attacking Card: " << deal[tempnum1 - 1].num << " " << deal[tempnum1 - 1].shape << std::endl; //print card picked
            std::cout << "Cards on table: ";
            for(int i = 0; i < tables.size(); i++){ // print current table
                std::cout << tables[i].num << " " << tables[i].shape << ", ";
            }
            deal.erase(deal.begin() + tempnum1 - 1); // remove card played from hand
        }

        return tempnum1; // if tempnum1 = 0, then attack stopped
}

int defend(std::vector<CARD> & allCards, std::vector<CARD> & deal, std::vector<CARD> & tables){ // function for defending the attack
    
    int tempnum2;

    while(defendvalidation(allCards, deal, tables, tempnum2) == 0){ // validation for card selected
        std::cout << "The card played is not allowed. Pick another card: ";
        std::cin.clear(); //clearing the failbit
        //while((std::cin.get()) != '\n'); // clear input buffer
    }
    
    if(tempnum2 == 0){
        system("clear");
        std::cout << "\nAttack Not Defended!";
        for(int i = tables.size(); i > 0; i--){ // if not able to defend, all table elements are picked up to hand
            deal.push_back(tables[i]);
            tables.erase(tables.begin() + i - 1);
        }
    }
    else {
        tables.push_back(deal[tempnum2 - 1]); // if defended, card selected added to table
        system("clear"); // avoid other players peeking at your cards
        // only cards printed defending card selected and table
        std::cout << "Defending Card: " << deal[tempnum2 - 1].num << " " << deal[tempnum2 - 1].shape << std::endl;
        std::cout << "Cards on table: ";
        for(int i = 0; i < tables.size(); i++){
            std::cout << tables[i].num << " " << tables[i].shape << ", ";
        }
        deal.erase(deal.begin() + tempnum2 - 1);
    }

    return tempnum2; // if tempnum2 = 0, then defend stopped
}

int attackvalidation(std::vector<CARD> & allCards, std::vector<CARD> & deal, std::vector<CARD> & tables, int & numplayed){

    int matchnum;
    while(!(std::cin >> numplayed) || numplayed < 0 || numplayed > deal.size()){
        std::cout << "Wrong Input! Please enter number from 1-6 (or 0 to stop attacking): ";
        std::cin.clear(); //clearing the failbit
        while((std::cin.get()) != '\n'); // clear input buffer
    }
    while((std::cin.get()) != '\n'); // clear input buffer    

    if(tables.size() == 0){
        return 1;
    }
    else {
        matchnum = 0;
        if(numplayed != 0){
            for(int i = 0; i < tables.size(); i++){
                if(deal[numplayed - 1].num == tables[i].num){
                matchnum = 1;
                }
            }
        }
        else {
            return 1;
        }
        
        if(matchnum == 1){
            return 1;
        }
        else
            return 0;        
    }
}

int defendvalidation(std::vector<CARD> & allCards, std::vector<CARD> & deal, std::vector<CARD> & tables, int & numdefended){

    
    while(!(std::cin >> numdefended) || numdefended < 0 || numdefended > deal.size()){
        std::cout << "Wrong Input! Please enter number from 1-6 (or 0 to stop defending): ";
        std::cin.clear(); //clearing the failbit
        while((std::cin.get()) != '\n'); // clear input buffer
    }
    while((std::cin.get()) != '\n'); // clear input buffer

    if(!(numdefended == 0)){
        if(tables[tables.size() - 1].shape == "Spade"){
            if(deal[numdefended - 1].num > tables[tables.size() - 1].num){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if(tables[tables.size() - 1].shape == "Club"){
            if(deal[numdefended - 1].num > tables[tables.size() - 1].num && deal[numdefended - 1].shape == "Club"){
                return 1;
            }
            else if(deal[numdefended - 1].shape == "Spade"){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if(tables[tables.size() - 1].shape == "Diamond"){
            if(deal[numdefended - 1].num > tables[tables.size() - 1].num && deal[numdefended - 1].shape == "Diamond"){
                return 1;
            }
            else if(deal[numdefended - 1].shape == "Spade"){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if(tables[tables.size() - 1].shape == "Heart"){
            if(deal[numdefended - 1].num > tables[tables.size() - 1].num && deal[numdefended - 1].shape == "Heart"){
                return 1;
            }
            else if(deal[numdefended - 1].shape == "Spade"){
                return 1;
            }
            else {
                return 0;
            }
        }
        else {
            return 0;
        }

    }
    else {
        return 1;
    }
}