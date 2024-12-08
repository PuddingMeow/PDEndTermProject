#include <bits/stdc++.h>
#include "teamClass.h"
using namespace std;

// 計算發球造成的傷害，返回比賽是否繼續
bool serveDamageCaculate(Team& serveSide, Team& opposide, int serveMethodNum, bool playing);

// 選擇發球方式
int chooseServeMethod(Team& playerTeam, Team& opponent);

// 選擇誰站在前排
void chooseFront(Team& t);

// 檢查某事件是否成功（機率為 a%）
bool checkSuccess(int a) {
    int dice = rand() % 100;
    return dice < a;
}

// 擲硬幣，決定誰先發球
void flipCoin(Team& player, Team& oppo) {
    int playerChoice = 0;
    cout << "你要選正面還是反面? (1: 正面, 2: 反面)\n";
    try {
        cin >> playerChoice;
        if (playerChoice != 1 && playerChoice != 2) {
            throw out_of_range("請輸入 1 或 2\n");
        }
    } catch (out_of_range& e) {
        cout << e.what();
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return flipCoin(player, oppo); // 重新進行擲硬幣
    }

    int coinResult = rand() % 2 + 1; // 1: 正面, 2: 反面
    if (playerChoice == coinResult) {
        cout << (coinResult == 1 ? "硬幣是正面！\n" : "硬幣是反面！\n");
        cout << "恭喜你猜中了！由你們這隊先發球！\n";
        player.setTurn(1);
        oppo.setTurn(2);
    } else {
        cout << (coinResult == 1 ? "硬幣是正面！\n" : "硬幣是反面！\n");
        cout << "你猜錯了！由對面先發球！\n";
        player.setTurn(2);
        oppo.setTurn(1);
    }
}

// 發球模擬，返回比賽是否繼續
bool serve(Team& playerTeam, Team& opponent, bool playing) {
    int serveMethodNum = 0;
    if (playerTeam.isServeTurn()) {
        serveMethodNum = chooseServeMethod(playerTeam, opponent);
        chooseFront(opponent);
        playing = serveDamageCaculate(playerTeam, opponent, serveMethodNum, playing);
    } else {
        serveMethodNum = rand() % 4 + 1; // 隨機選擇發球方式
        chooseFront(playerTeam);
        playing = serveDamageCaculate(opponent, playerTeam, serveMethodNum, playing);
    }
    return playing;
}

int chooseServeMethod(Team& playerTeam, Team& opponent) {
    int serveMethodNum = 0;
    cout << "你想要用哪種方式發球呢？\n";
    cout << "(1) 大力跳發 (2) 跳飄 (3) 高手發球 (4) 低手發球\n";
    try {
        cin >> serveMethodNum;
        if (serveMethodNum < 1 || serveMethodNum > 4) {
            throw out_of_range("請輸入 1～4 之間的數字！\n");
        }
    } catch (out_of_range& e) {
        cout << e.what();
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return chooseServeMethod(playerTeam, opponent); // 重新選擇
    }
    return serveMethodNum;
}

void chooseFront(Team& t) {
    if (t.isPlayerTeamFunc()) {
        int frontPlayer;
        cout << "你要讓誰站在前場？(1: 玩家, 2: 隊友)\n";
        try {
            cin >> frontPlayer;
            if (frontPlayer != 1 && frontPlayer != 2) {
                throw out_of_range("請輸入 1 或 2\n");
            }
        } catch (out_of_range& e) {
            cout << e.what();
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            return chooseFront(t); // 重新選擇
        }
        t.setFront(frontPlayer);
    } else {
        t.setFront(rand() % 2 + 1); // 隨機選擇
    }
}

bool serveDamageCaculate(Team& serveSide, Team& opposide, int serveMethodNum, bool playing) {
    if (serveMethodNum == 1 && checkSuccess(30 + serveSide.backPlayer().getSKL())) {
        opposide.setReceiveDifficulity(40 + serveSide.backPlayer().getATK() * 1.5);
    } else if (serveMethodNum == 2 && checkSuccess(50 + serveSide.backPlayer().getSKL())) {
        opposide.setReceiveDifficulity(50 + serveSide.backPlayer().getSKL() * 1.1);
    } else if (serveMethodNum == 3 && checkSuccess(80 + serveSide.backPlayer().getSKL())) {
        opposide.setReceiveDifficulity(25 + serveSide.backPlayer().getSKL() * 0.5);
    } else if (serveMethodNum == 4 && checkSuccess(99)) {
        opposide.setReceiveDifficulity(15 + serveSide.backPlayer().getSKL() * 0.3);
    } else {
        cout << "發球失誤！對方得分～\n";
        opposide.addPoint();
        playing = false;
    }
    return playing;
}

void receive() {
    // TODO: 實作接球邏輯
    cout << "接球邏輯尚未實作！\n";
}

void attack() {
    // TODO: 實作攻擊邏輯
    cout << "攻擊邏輯尚未實作！\n";
}

int main() {
    srand(time(NULL));

    MainCharacter player, A, B, C;
    Team opponent(A, B, false);
    Team playerTeam(player, C, true);

    flipCoin(playerTeam, opponent);
    int endScore = 15;

    while (playerTeam.getScore() < endScore && opponent.getScore() < endScore) {
        bool playing = true;
        playing = serve(playerTeam, opponent, playing);
        while (playing) {
            receive();
            attack();
        }
    }

    cout << (playerTeam.getScore() == endScore ? "恭喜你贏了！\n" : "你輸了！\n");
    return 0;
}
/*
#include <bits/stdc++.h>
#include "teamClass.h"
using namespace std;

//caculate the damage cause to opposide team. depend on serveSide's atk, skill, serveMethod
bool serveDamageCaculate(Team serveSide, Team& opposide, int serveMethodNum, bool playing);
//choose how to serve
int chooseServeMethod(Team playerTeam, Team opponent); 
//choose who stand forntside in team t;
void chooseFront(Team t); 
//check if a a% event will happened
bool checkSuccess(int a){     
    int dice = 0;
    dice = rand()%(100);
    if(dice <= a){
        return true;
    }else{
        return false;
    }
}

//flipcoin, decide who serve first when battle start;
void flipCoin(Team& player, Team& oppo){
    int playerChoice = 0;
    cout << "你要選正面還是反面?\n";
    try{
        cin >> playerChoice;
        if(playerChoice != 1 && playerChoice != 2){
            throw out_of_range("請輸入1或是2\n");
        }
    }
    catch(out_of_range &e){
        cout << e.what();
    }
    catch(invalid_argument &e){
        cout << "請輸入1或是2\n";
    }
    if(playerChoice == (rand()%2)){
        if(playerChoice == 0){
            cout << "硬幣是．．．正面！\n";
        }else{
            cout << "硬幣是．．．反面！\n";
        }
        cout << "恭喜你猜中了！\n";
        cout << "由你們這隊先發球！\n";
        player.setTurn(1); // team player serve first
        oppo.setTurn(2);  // team opponent receive
    }else{
        if(playerChoice == 0){
            cout << "硬幣是．．．反面！\n";
        }else{
            cout << "硬幣是．．．正面！\n";
        }
        cout << "你猜錯了！\n";
        cout << "由對面先發球！\n";
        player.setTurn(2); //team player receive
        oppo.setTurn(1); //team opponent serve first
    }
}

//serve simulation, 
bool serve(Team playerTeam, Team opponent, bool playing){
    int serveMethodNum = 0;
    if(playerTeam.isServeTurn()){
        serveMethodNum = chooseServeMethod(playerTeam, opponent); //choose which method you want to serve
        chooseFront(opponent);
        playing = serveDamageCaculate(playerTeam, opponent, serveMethodNum, playing);
    }else{
        serveMethodNum = rand()%4+1;
        chooseFront(playerTeam);
        playing = serveDamageCaculate(opponent, playerTeam, serveMethodNum, playing);
    }
    return playing;
}

int chooseServeMethod(Team playerTeam, Team opponent){
    cout << "你想要用哪種方式發球呢？\n";
    int serveMethodNum = 0;
    cout << "(1) 大力跳發\n (2) 跳飄\n (3)高手發球\n (4)低手發球\n";
    try{
        cin >> serveMethodNum;
        if(serveMethodNum > 4 ||serveMethodNum < 1){
            throw out_of_range("請輸入1～4之間的數字！\n");
        }
    }
    catch(out_of_range &e){
        cout << e.what();
    }
    catch(invalid_argument &e){
        cout << "請輸入1～4之間的數字！\n";
    }
    return serveMethodNum;
}

void chooseFront(Team t){
    if(t.isPlayerTeamFunc()){
        int frontPlayer;
        cout << "你要讓誰防守前場？\n";
        cout << "(1) 玩家\n (2) 隊友\n";
        try{
            cin >> frontPlayer;
            if (frontPlayer!=1 && frontPlayer !=2){
                throw out_of_range("請輸入1或2\n");
            }
        }
        catch(out_of_range &e){
            cout << e.what();
        }
        catch(invalid_argument &e){
            cout << "please enter 1 or 2.\n";
        }
        t.setFront(frontPlayer);
    }else{
        t.setFront(rand()%2+1);
    }
}

bool serveDamageCaculate(Team serveSide, Team& opposide, int serveMethodNum, bool playing){
    if(serveMethodNum==1){
        if(checkSuccess(30+serveSide.backPlayer().getSKL())){
            opposide.setReceiveDifficulity(40+serveSide.backPlayer().getATK()*1.5);
        }else{
            cout << "發球失誤！對方得分～\n";
            opposide.point(); //opposide get one point
            playing = false; 
        }
    }
    if(serveMethodNum==2){
        if(checkSuccess(50+serveSide.backPlayer().getSKL())){
            opposide.setReceiveDifficulity(50+serveSide.backPlayer().getSKL()*1.1);
        }else{
            cout << "發球失誤！對方得分～\n";
            opposide.point();
            playing = false;
        }
    }
    if(serveMethodNum==3){
        if(checkSuccess(80+serveSide.backPlayer().getSKL())){
            opposide.setReceiveDifficulity(25+serveSide.backPlayer().getSKL()*0.5);
        }else{
            cout << "發球失誤！對方得分～\n";
            opposide.point();
            playing = false;
        }
    }
    if(serveMethodNum==4){
        if(checkSuccess(99)){
            opposide.setReceiveDifficulity(15+serveSide.backPlayer().getSKL()*0.3);
        }else{
            cout << "發球失誤！對方得分～\n";
            opposide.point();
            playing = false;
        }
    }
    return playing;
}
int main(){
    srand(time(NULL));

    MainCharacter player;
    MainCharacter A;
    MainCharacter B;
    MainCharacter C;
    Team opponent(A, B, false);
    Team playerTeam(player, C, true);
    flipCoin(playerTeam, opponent);
    int endScore = 15;
    while(playerTeam.getScore() != endScore && opponent.getScore() != endScore){
        bool playing = true;
        serve();
        while(playing){
            receive();
            attack();
        }
    }
}
*/
