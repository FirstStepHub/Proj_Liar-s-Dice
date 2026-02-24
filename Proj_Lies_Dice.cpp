#include<iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std ;


// Global Vari //
class Player ;
vector<Player> players ; 
int currentBidAmount = 0 ; // จำนวนลูกเต๋าที่เดิมพันปัจจุบัน
int currentBidFace = 0 ; // หน้าลูกเต๋าที่เดิมพันปัจจุบัน
int currentPlayerTurn = 0 ; // อินเด็กซ์ของผู้เล่นปัจจุบัน

// Prototype
void startGame() ; //ตัวเริ่ม
void processTurn() ; //สลับเทิร์นเล่น
void checkChallenge() ; //จับโกหก
void resetRound() ; //รีเซ็ต

class Player{
public:
    string name ;
    int diceNow ; //เต๋าที่มีในมือ
    vector<int> diceInHand ;
    Player(string inputName) {
        name = inputName ;
        diceNow = 5 ;
    }

     //สุ่มเต๋า
    void rollDice(){
        diceInHand.clear() ; // ล้างหน้าเต๋าเก่าออกก่อน
        if (diceNow > 0) {
            for (int i = 0 ; i < diceNow ; i++) {
                int roll = (rand() % 6) + 1 ; // สุ่ม 1-6
                diceInHand.push_back(roll) ;
            }
        }
    }

     //ลดเต๋าถ้าโดนจับ
    void loseDice(){
        if (diceNow > 0) {
            diceNow-- ;
            cout << "Player :" << name << " lost a die! Remaining: " << diceNow << endl ;
        }
    }

    //กดดูเต๋าในมือตัวเอง
    void seeHand(){
        cout << "[" << name << "'s Hand]: " ;
        for (int d : diceInHand) {
            cout << d << " " ;
        }
        cout << endl;
    }

};



int main(){
    srand(time(0)) ;
    startGame() ;

}


//เริ่มเกม
void startGame(){
    int numPlayers ;
    cout << "Enter number of players: " ;
    cin >> numPlayers ;

    for (int i = 1; i <= numPlayers; i++) {
        string n ;
        cout << "Enter name for Player " << i << ": " ;
        cin >> n ;
        players.push_back(Player(n)) ;
    }
}

void resetRound() {
    currentBidAmount = 0 ;
    currentBidFace = 0 ;
}

void processTurn(){
    int amount, face ;
        while (true) {
            cout << "Place your bid : (face) (amount)" ;
            cin >> face >> amount ;

        bool valid = false;
        if (amount > currentBidAmount) valid = true ;
        else if (amount == currentBidAmount && face > currentBidFace) valid = true ;

        if (valid && face >= 1 && face <= 6) {
            currentBidAmount = amount ;
            currentBidFace = face ;
            break ;
        } else {
            cout << "Invalid bid! You must raise the amount or the face value." << endl ;
        }
    }
}

void checkChallenge(){
    //จับโกหก (เปิดหน้าเต๋า)
}




















