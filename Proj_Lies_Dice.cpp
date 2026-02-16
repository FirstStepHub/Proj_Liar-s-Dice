#include<iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std ;

// Prototype
void startGame() ; //ตัวเริ่ม
void processTurn() ; //สลับเทิร์นเล่น
void checkChallenge() ; //จับโกหก

class Player{
    public:
    string name ;
    int diceNow ; //เต๋าที่มีในมือ
    vector<int> diceInHand ;

    Player(string inputName) {
        name = inputName ;
        diceNow = 5 ;
    }

    void rollDice() //สุ่มเต๋า

    void loseDice() //ลดเต๋าถ้าโดนจับ

    void seeHand() //กดดูเต๋าในมือตัวเอง

} ;



vector<Player> players ; //เผื่อทำหลายคน



int main(){

}



void startGame(){
    //เริ่มเกม
}

void processTurn(){
    //การBid
    //สลับเทิร์น
}

void checkChallenge(){
    //จับโกหก (เปิดหน้าเต๋า)
}





















