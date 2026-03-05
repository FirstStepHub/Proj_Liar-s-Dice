#include<iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cctype>
using namespace std ;

class Player{
public:
    string name ;
    int diceNow ;
    vector<int> diceInHand ;
    bool Bot;
    Player(string inputName , bool botStatus = false) {
        name = inputName ;
        diceNow = 5 ;
        Bot = botStatus ;
    }

    void rollDice(){
        diceInHand.clear() ;
        if (diceNow > 0) {
            for (int i = 0 ; i < diceNow ; i++) {
                int roll = (rand() % 6) + 1 ;
                diceInHand.push_back(roll) ;
            }
        }
    }

    void loseDice(){
        if (diceNow > 0) {
            diceNow-- ;
            cout << "Player :" << name << " lost a dice! Remaining: " << diceNow << endl ;
        }
    }

    void seeHand(){
        cout << "[" << name << "'s Hand]: " ;
        for (int d : diceInHand) {
            cout << d << " " ;
        }
        cout << endl ;
    }

};

vector<Player> players ; 
int currentBidAmount = 0 ;
int currentBidFace = 0 ;
int currentPlayerTurn = 0 ;
int totalDiceInGame = 0 ;

void startGame() ;
void playGame() ;
void processTurn() ;
void checkChallenge() ;
void resetRound() ;
int countActivePlayers() ;



int main(){
    srand(time(0)) ;
    startGame() ;
    playGame() ;
    return 0 ;
}


void startGame(){
    string name ;
    cout << "Enter your name: " ;
    cin >> name ;
    players.push_back(Player(name, false)) ;

    int numBots ;
    cout << "Enter number of Bots to play against: " ;
    cin >> numBots ;

    for (int i = 1; i <= numBots; i++) {
        players.push_back(Player("Bot_" + to_string(i), true)) ;
    }
}

void resetRound() {
    currentBidAmount = 0 ;
    currentBidFace = 0 ;
    totalDiceInGame = 0 ;
    
    for (Player& p : players) {
        if (p.diceNow > 0) {
            p.rollDice() ;
            totalDiceInGame += p.diceNow ;
        }
    }
    cout << "\n===================================" << endl ;
    cout << "   NEW ROUND STARTED! Total Dice: " << totalDiceInGame << endl ;
    cout << "===================================" << endl ;
}

void processTurn(){
if (players[currentPlayerTurn].diceNow == 0) return ;

    cout << "\n--- " << players[currentPlayerTurn].name << "'s Turn ---" << endl ;

    if (!players[currentPlayerTurn].Bot) {
        players[currentPlayerTurn].seeHand() ;
    }

    if (currentBidAmount == 0) {
        cout << "No current bid." << endl ;
    } else {
        cout << "Current Bid: " << currentBidAmount << " of Face [" << currentBidFace << "]" << endl ;
    }

    if (players[currentPlayerTurn].Bot) {
        int amount, face ;

        if (currentBidAmount == 0) {
            face = (rand() % 6) + 1 ;
            amount = 1 ;
            cout << players[currentPlayerTurn].name << " bids: Face " << face << ", Amount " << amount << endl ;
            currentBidAmount = amount ;
            currentBidFace = face ;
        } else {
            int challengeThreshold = (totalDiceInGame / 2) + (rand() % 2) ; 
            
            if (currentBidAmount >= challengeThreshold) {
                cout << players[currentPlayerTurn].name << " says: CHALLENGE! (0 0)" << endl ;
                checkChallenge() ;
                resetRound() ;
                return ;
            } else {
                amount = currentBidAmount ;
                face = currentBidFace ;

                if (face < 6 && rand() % 2 == 0) {
                    face++ ;
                } else {
                    amount++ ;
                }

                cout << players[currentPlayerTurn].name << " bids: Face " << face << ", Amount " << amount << endl ;
                currentBidAmount = amount ;
                currentBidFace = face ;
            }
        }
    } else {
        if (currentBidAmount == 0) {
            cout << "You are the first bidder. You must place a bid." << endl ;
        } else {
            cout << "Enter '0 0' to CHALLENGE, or place a higher bid." << endl ;
        }

        int amount, face;
        while (true) {
            cout << "Place your bid (face amount) OR type 'Exit' to quit: ";
            string inputStr ;
            cin >> inputStr ;

for (char &c : inputStr) {
                c = toupper(c);
            }

            if (inputStr == "EXIT") {
                cout << "\n👋 You have exited the game. See you next time!" << endl;
                exit(0);
            }

            face = atoi(inputStr.c_str());
            cin >> amount;

            if (face == 0 && amount == 0) {
                if (currentBidAmount == 0) {
                    cout << "You cannot challenge on the first turn!" << endl;
                    continue;
                }
                checkChallenge();
                resetRound();
                return;
            }

            bool valid = false;
            if (amount > currentBidAmount) valid = true;
            else if (amount == currentBidAmount && face > currentBidFace) valid = true;

            if (valid && face >= 1 && face <= 6) {
                currentBidAmount = amount;
                currentBidFace = face;
                break;
            } else {
                cout << "Invalid bid! You must raise the amount or the face value (1-6)." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }
    do {
        currentPlayerTurn = (currentPlayerTurn + 1) % players.size();
    } while (players[currentPlayerTurn].diceNow == 0);
}

void checkChallenge(){
cout << "\n!!! CHALLENGE CALLED !!!" << endl;
    
    int actualCount = 0;
    for (Player& p : players) {
        if (p.diceNow > 0) {
            p.seeHand();
            for (int d : p.diceInHand) {
                if (d == currentBidFace) {
                    actualCount++;
                }
            }
        }
    }

    cout << "\nTotal amount of Face [" << currentBidFace << "] on the table is: " << actualCount << endl;

    int previousPlayer = currentPlayerTurn - 1;
    if (previousPlayer < 0) previousPlayer = players.size() - 1;
    while (players[previousPlayer].diceNow == 0) {
        previousPlayer--;
        if (previousPlayer < 0) previousPlayer = players.size() - 1;
    }

    if (actualCount >= currentBidAmount) {
        cout << "=> " << players[previousPlayer].name << " told the TRUTH! (There are " << actualCount << " >= " << currentBidAmount << ")" << endl;
        cout << "=> " << players[currentPlayerTurn].name << " (Challenger) loses the challenge!" << endl;
        players[currentPlayerTurn].loseDice();
    } else {
        cout << "=> " << players[previousPlayer].name << " BLUFFED! (There are only " << actualCount << " < " << currentBidAmount << ")" << endl;
        cout << "=> " << players[previousPlayer].name << " (Bidder) gets caught!" << endl;
        players[previousPlayer].loseDice();
        currentPlayerTurn = previousPlayer;
    }
    while (players[currentPlayerTurn].diceNow == 0) {
        currentPlayerTurn = (currentPlayerTurn + 1) % players.size();
    }
}

int countActivePlayers() {
    int count = 0;
    for (Player& p : players) {
        if (p.diceNow > 0) count++;
    }
    return count;
}

void playGame() {
    resetRound();

    while (countActivePlayers() > 1) {
        processTurn();
    }

    for (Player& p : players) {
        if (p.diceNow > 0) {
            cout << "\n🎉 WINNER IS: " << p.name << " 🎉" << endl;
            break;
        }
    }
}

