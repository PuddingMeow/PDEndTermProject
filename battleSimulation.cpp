#include <bits/stdc++.h>
#include <cstdlib>
#include "teamClass.h"
using namespace std;

// 計算發球造成的傷害，返回比賽是否繼續
bool serveDamageCaculate(Team& serveSide, Team& oppoSide, int serveMethodNum, bool playing);

// 選擇發球方式
int chooseServeMethod();

// 選擇誰站在前排
void chooseFront(Team& t);

//判斷舉球是否成功
bool setBall(Team& attackSide, bool playing);

//選擇攻擊方式
int chooseAttackMethod();

//選擇攻擊位置
int chooseAttackAim();

//計算攻擊傷害
bool attackDamageCaculate(Team& attackSide, Team& oppoSide, int attackMethodNum, bool playing);

// 檢查某事件是否成功（機率為 a%）
bool checkSuccess(int a) {
    int dice = rand() % 100+1;
    cout << "[DEBUG] 擲骰子點數: " << dice << " (成功機率: " << a << "%)" << endl;
    return dice < a;
}

// 擲硬幣，決定誰先發球
void flipCoin(Team& player, Team& oppo) {
    int playerChoice = 0;
    cout << "========== 擲硬幣階段 ==========" << endl;
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
        return flipCoin(player, oppo);
    }

    int coinResult = rand() % 2 + 1; // 1: 正面, 2: 反面
    cout << "[DEBUG] 擲硬幣結果: " << (coinResult == 1 ? "正面" : "反面") << endl;

    if (playerChoice == coinResult) {
        cout << "恭喜你猜中了！由你們這隊先發球！\n";
        player.setTurn(1);
        oppo.setTurn(2);
    } else {
        cout << "你猜錯了！由對面先發球！\n";
        player.setTurn(2);
        oppo.setTurn(1);
    }
}

// 發球模擬，返回比賽是否繼續
bool serve(Team& serveSide, Team& oppoSide, bool playing) {
    cout << "========== 發球階段 ==========" << endl;
    int serveMethodNum = 0;
    if (serveSide.getIsPlayerTeam()) {
        cout << "[DEBUG] 現在是玩家隊伍的發球回合" << endl;
        serveMethodNum = chooseServeMethod();   
    } else {
        cout << "[DEBUG] 現在是對手隊伍的發球回合" << endl;
        serveMethodNum = rand() % 4 + 1;
    }
    playing = serveDamageCaculate(serveSide, oppoSide, serveMethodNum, playing);
    return playing;
}

int chooseServeMethod() {
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
        return chooseServeMethod();
    }
    cout << "[DEBUG] 選擇的發球方式: " << serveMethodNum << endl;
    return serveMethodNum;
}

void chooseFront(Team& t) {
    cout << "========== 前後場選擇階段 ==========" << endl;
    if (t.getIsPlayerTeam()) {
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
            return chooseFront(t);
        }
        cout << "[DEBUG] 玩家選擇 " << (frontPlayer == 1 ? "自己" : "隊友") << " 為前排" << endl;
        t.setFront(frontPlayer);
    } else {
        int randomChoice = rand() % 2 + 1;
        cout << "[DEBUG] 對手選擇 " << (randomChoice == 1 ? "玩家A" : "玩家B") << " 為前排" << endl;
        t.setFront(randomChoice);
    }
}

bool serveDamageCaculate(Team& serveSide, Team& oppoSide, int serveMethodNum, bool playing) {
    cout << "[DEBUG] 發球方式: " << serveMethodNum << endl;
    if (serveMethodNum == 1 && checkSuccess(30 + serveSide.backPlayer().getSKL())) {
        oppoSide.setReceiveDifficulity(40 + serveSide.backPlayer().getATK() * 1.5);
    } else if (serveMethodNum == 2 && checkSuccess(50 + serveSide.backPlayer().getSKL())) {
        oppoSide.setReceiveDifficulity(50 + serveSide.backPlayer().getSKL() * 1.1);
    } else if (serveMethodNum == 3 && checkSuccess(80 + serveSide.backPlayer().getSKL())) {
        oppoSide.setReceiveDifficulity(25 + serveSide.backPlayer().getSKL() * 0.5);
    } else if (serveMethodNum == 4 && checkSuccess(99)) {
        oppoSide.setReceiveDifficulity(15 + serveSide.backPlayer().getSKL() * 0.3);
    } else {
        cout << "發球失誤！對方得分～\n";
        oppoSide.addPoint();
        oppoSide.setTurn(1); //換對方發球
        serveSide.setTurn(2); //己方接球
        playing = false;
    }
    return playing;
}

bool receive(Team& receiveSide, Team& oppoSide, bool playing, int aim) {
    cout << "========== 接球階段 ==========" << endl;
    chooseFront(receiveSide);
    if (aim == 1) {
        playing = checkSuccess(receiveSide.frontPlayer().getDEF() * 1.5 + receiveSide.frontPlayer().getSPD() - receiveSide.getReceiveDifficulity());
    } else {
        playing = checkSuccess(receiveSide.backPlayer().getDEF() * 1.5 + receiveSide.backPlayer().getSPD() - receiveSide.getReceiveDifficulity());
    }
    if(receiveSide.getIsPlayerTeam()){
        if (playing) {
            cout << "[DEBUG] 你成功接到球了！\n";
            receiveSide.setTurn(3); //攻擊
            oppoSide.setTurn(2);//對手接球
            return playing;
        } else {
            cout << "沒有接到球QAQ\n對方得分！\n";
            oppoSide.addPoint();
            receiveSide.setTurn(2); //接球
            oppoSide.setTurn(1);//對手發球
            return playing;
        }
    }else{
        if (playing) {
            cout << "[DEBUG] 對手成功接到球了！\n";
            receiveSide.setTurn(3); //攻擊
            oppoSide.setTurn(2); //對手接球
            return playing;
        } else {
            cout << "對手沒有接到球QAQ\n你成功得分！\n";
            oppoSide.addPoint();
            receiveSide.setTurn(2); //接球
            oppoSide.setTurn(1); //對手發球
            return playing;
        }
        
    }
    
}

bool attack(Team& attackSide, Team& oppoSide, bool playing) {
    cout << "========== 攻擊階段 ==========" << endl;
    int attackMethod = 0;
//    int attackAim = 0; //1 前場 2後場 0初始 
    if(attackSide.getIsPlayerTeam()){
        attackMethod = chooseAttackMethod();
    }else{
        attackMethod = rand() % 4 + 1;
    }
    playing = setBall(attackSide, playing);
    if(!playing) return playing;
    if(attackSide.getIsPlayerTeam()){
//        attackAim = chooseAttackAim();
    }else{
//        attackAim = rand() % 2 + 1;
    }
    playing = attackDamageCaculate(attackSide, oppoSide, attackMethod, playing);
    return playing;
}

bool setBall(Team& attackSide, bool playing){
    playing = checkSuccess(attackSide.frontPlayer().getSPD()*0.2+attackSide.frontPlayer().getSKL()*0.8+70);
    if(attackSide.getIsPlayerTeam()){
        if(playing){
            cout << "舉球成功！";
            return playing;
        }else{
            cout << "舉球時，手滑掉了？？？\n對手獲得一分！";
            return playing;
        }
    }else{
         if(playing){
            cout << "對方舉球成功！";
            return playing;
        }else{
            cout << "對方舉球時只顧著看你的絕世容顏\n球掉到地上，你獲得一分！";
            return playing;
        }
    }
}

int chooseAttackMethod(){
    int attackMethodNum = 0;
    cout << "你想要用哪種方式攻擊呢？\n";
    cout << "(1) 強力扣殺 (2) 吊球 (3) 快攻 (4) 平地回擊\n";
    try {
        cin >> attackMethodNum;
        if (attackMethodNum < 1 || attackMethodNum > 4) {
            throw out_of_range("請輸入 1～4 之間的數字！\n");
        }
    } catch (out_of_range& e) {
        cout << e.what();
        cin.clear(); //XXX:但其實我沒搞懂這在幹啥
        cin.ignore(INT_MAX, '\n');
        return chooseAttackMethod();
    }
    cout << "[DEBUG] 選擇的攻擊方式: " << attackMethodNum << endl;
    return attackMethodNum;
}
int chooseAttackAim(){
    int attackAimNum = 0;
    cout << "你想要把球打到對方場上的哪個地方呢？\n";
    cout << "(1) 前場 (2) 後場\n";
    try {
        cin >> attackAimNum;
        if (attackAimNum < 1 || attackAimNum > 2) {
            throw out_of_range("請輸入 1～2 之間的數字！\n");
        }
    } catch (out_of_range& e) {
        cout << e.what();
        cin.clear(); //XXX:但其實我沒搞懂這在幹啥
        cin.ignore(INT_MAX, '\n');
        return chooseAttackAim();
    }
    cout << "[DEBUG] 選擇的攻擊位置: " << attackAimNum << endl;
    return attackAimNum;
}
bool attackDamageCaculate(Team& attackSide, Team& oppoSide, int attackMethodNum, bool playing) {
    cout << "[DEBUG] 攻擊方式: " << attackMethodNum << endl;
    if (attackMethodNum == 1 && checkSuccess(40 + attackSide.backPlayer().getSKL())) {
        oppoSide.setReceiveDifficulity(attackSide.backPlayer().getSKL() * 0.2 + attackSide.backPlayer().getATK() * 1);
    } else if (attackMethodNum == 2 && checkSuccess(50 + attackSide.backPlayer().getSKL())) {
        oppoSide.setReceiveDifficulity(20 + attackSide.backPlayer().getSKL() * 0.8);
    } else if (attackMethodNum == 3 && checkSuccess(40 + attackSide.backPlayer().getSKL())) {
        oppoSide.setReceiveDifficulity(attackSide.backPlayer().getATK() * 0.6 + attackSide.backPlayer().getSKL() * 0.4 + attackSide.backPlayer().getSPD() * 0.5);
    } else if (attackMethodNum == 4 && checkSuccess(99)) {
        oppoSide.setReceiveDifficulity(20 + attackSide.backPlayer().getSKL() * 0.1);
    } else {
        cout << "攻擊失誤！對方得分～\n";
        oppoSide.addPoint();
        oppoSide.setTurn(1); //換對方發球
        attackSide.setTurn(2); //己方接球
        playing = false;
    }
    return playing;
}
int main() {
    srand(time(NULL));

    MainCharacter player, A, B, C;
    player.addDEF(1200);
    Team opponent(A, B, false);
    Team playerTeam(player, C, true);

    flipCoin(playerTeam, opponent);
    int endScore = 15;

    while (playerTeam.getScore() < endScore && opponent.getScore() < endScore) {
        cout << "========== 比賽進行中 ==========" << endl;
        cout << "現在分數\n你的隊伍：" << playerTeam.getScore() << '\n';
        cout << "對手隊伍：" << opponent.getScore() << '\n';
        bool playing = true;
        if(playerTeam.isServeTurn()){
            playing = serve(playerTeam, opponent, playing);
        }else{
            playing = serve(opponent, playerTeam, playing);
        }
        while (playing) {
            if(playerTeam.isRecieveTurn()){
                playing = receive(playerTeam, opponent, playing, 1);
            }else if(opponent.isRecieveTurn()){
                playing = receive(opponent, playerTeam, playing, 1);
            }
            if(playing){
                if(playerTeam.isAttackTurn()){
                    playing = attack(playerTeam, opponent, playing);
                }else if (opponent.isAttackTurn()){
                    playing = attack(opponent, playerTeam, playing);
                }
            }
        }
    }

    cout << (playerTeam.getScore() == endScore ? "恭喜你贏了！\n" : "你輸了！\n");
    return 0;
}

