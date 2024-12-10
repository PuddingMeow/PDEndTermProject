#include <bits/stdc++.h>
#include "./MainCharacter.h"
using namespace std;
/* what we should have
主要事項：
1. character/player object
2. main function(interface & daily progression)
3. event system
4. training system(可與event一起做？)
5. teammate recruiting(與event一起……？也跟flags有關)
6. match system

次要事項：
1. save system
2. items & inventory(?)
*/

/*
所以我現在是這樣設計的
a file of character design (of course you can split it into many files)
some files about event designs (最後統整為一個檔案方便匯入)
some files about daily progression (同上)
a file about teammate recruiting(not now)
some files about match system.(not now)
*/

//每天開始的固定處理與輸出
void dayStart(int dayCnt){ 
    cout << "第" << dayCnt << "天\n";
}

//每天結束的固定處理與輸出
void dayEnd(int& dayCnt, MainCharacter player){
    cout << "第" << dayCnt << "天\n";
    cout << "現在的各項數值\n";
    cout << "攻擊力：" << player.getATK() << '\n';
    cout << "防禦力：" << player.getDEF() << '\n';
    cout << "敏捷度：" << player.getSPD() << '\n';
    cout << "幸運值：" << player.getLUK() << '\n'; //感覺加了比較好玩
    cout << "精力值上限：" << player.getSPLimit() << '\n';
    cout << "錢包餘額：" << player.getMNY() << '\n';
    cout << "你的隊友：" << player.listPartner() << '\n';
    dayCnt ++;
}

int main(){
    MainCharacter player; //主角
    int dayCnt = 1; //現在的天數
    int battleDay = {7, finalDay}; //數值隨便寫的，要比賽的日子
    int finalDay = 14; //數值我歲便寫的2，最後一天
    while(dayCnt <= finalDay){
        if(dayCnt in battleDay){
            battleSimulation();//希望我們寫的到
        }else{
            daySimulation(); //包含event和dailyProgression //還有選項輸出等等
        }
        dayEnd(dayCnt, player);//執行結束處理
    }
    gameEnd();//遊戲結束處理
}

