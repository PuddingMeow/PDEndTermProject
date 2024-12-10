#include <bits/stdc++.h>
#include "teamClass.h"
#include "battleSimulationFunc.h"

using namespace std;

// 擲硬幣，決定誰先發球
void flipCoin(Team& player, Team& oppo);

// 檢查某事件是否成功（機率為 a%）
bool checkSuccess(int a);

// 發球模擬，返回比賽是否繼續
bool serve(Team& serveSide, Team& oppoSide, bool playing);

// 計算發球造成的傷害，返回比賽是否繼續
bool serveDamageCaculate(Team& serveSide, Team& oppoSide, int serveMethodNum, bool playing);

// 選擇發球方式
int chooseServeMethod();

// 選擇誰站在前排
void chooseFront(Team& t);

//模擬接球，返回這一分的比賽是否繼續
bool receive(Team& receiveSide, Team& oppoSide, bool playing);

//模擬攻擊流程，返回有沒有人得分，返回這一分的比賽是否繼續
bool attack(Team& attackSide, Team& oppoSide, bool playing);

//判斷舉球是否成功
bool setBall(Team& attackSide, Team& oppoSide, bool playing);

//選擇攻擊方式
int chooseAttackMethod();

//選擇攻擊位置
int chooseAim();

//計算攻擊傷害
bool attackDamageCaculate(Team& attackSide, Team& oppoSide, int attackMethodNum, bool playing);

//battleSimulationFunction, use in main.cpp
bool battleSimulation(MainCharacter& player, MainCharacter& partner, MainCharacter& opponent1, MainCharacter& opponent2){
    string playerTeamName = "";
    cout << "你的隊名要叫做什麼？\n>>";
    getline(cin, playerTeamName);
    if (playerTeamName.empty()) {
        cout << "隊名不能為空！請重新輸入。\n";
        getline(cin, playerTeamName);
    }
    if (cin.fail()) {
        cin.clear();  // 清除錯誤狀態
        cin.ignore(INT_MAX, '\n');  // 清空緩衝區
        cout << "輸入錯誤，請重新輸入。\n";
        getline(cin, playerTeamName);
    }
    Team opponent(opponent1, opponent2, false, "我是超強的對手啦哈哈");
    Team playerTeam(player, partner, true, playerTeamName);
    
    cout << "\n==========比賽開始！==========\n";
    cout << "由 " << playerTeam.getTeamName() << " 對上 " << opponent.getTeamName() << " ！\n";
    int endScore = 15;
    cout << "當分數到達 " << endScore << " 分時遊戲結束！\n";
    delay_ms(TEXT_DELAY);

    flipCoin(playerTeam, opponent);

    while (playerTeam.getScore() < endScore && opponent.getScore() < endScore) {
        delay_ms(TEXT_DELAY);
        cout << "========== 比賽進行中 ==========" << endl;
        cout << "現在分數\n你的隊伍：" << playerTeam.getScore() << '\n';
        cout << "對手隊伍：" << opponent.getScore() << '\n';
        delay_ms(TEXT_DELAY);
        
        bool playing = true;
        if(playerTeam.isServeTurn()){
            playing = serve(playerTeam, opponent, playing);
        }else{
            playing = serve(opponent, playerTeam, playing);
        }
        while (playing) {
            if(playerTeam.isRecieveTurn()){
                playing = receive(playerTeam, opponent, playing);
            }else if(opponent.isRecieveTurn()){
                playing = receive(opponent, playerTeam, playing);
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
    return (playerTeam.getScore() == endScore);
}

/*
int main() {
    //設定亂數種子
    srand(time(NULL));
    
    MainCharacter player, A, B, C;
    player.addDEF(1200);
    B.addDEF(30);
    string playerTeamName = "";
    cout << "你的隊名要叫做什麼？\n>>";
    getline(cin, playerTeamName);
    if (playerTeamName.empty()) {
        cout << "隊名不能為空！請重新輸入。\n";
        getline(cin, playerTeamName);
    }
    if (cin.fail()) {
        cin.clear();  // 清除錯誤狀態
        cin.ignore(INT_MAX, '\n');  // 清空緩衝區
        cout << "輸入錯誤，請重新輸入。\n";
        getline(cin, playerTeamName);
    }
    Team opponent(A, B, false, "我是超強的對手啦哈哈");
    Team playerTeam(player, C, true, playerTeamName);
    
    cout << "\n==========比賽開始！==========\n";
    cout << "由 " << playerTeam.getTeamName() << " 對上 " << opponent.getTeamName() << " ！\n";
    int endScore = 15;
    cout << "當分數到達 " << endScore << " 分時遊戲結束！\n";
    delay_ms(TEXT_DELAY);

    flipCoin(playerTeam, opponent);

    while (playerTeam.getScore() < endScore && opponent.getScore() < endScore) {
        delay_ms(TEXT_DELAY);
        cout << "========== 比賽進行中 ==========" << endl;
        cout << "現在分數\n你的隊伍：" << playerTeam.getScore() << '\n';
        cout << "對手隊伍：" << opponent.getScore() << '\n';
        delay_ms(TEXT_DELAY);
        
        bool playing = true;
        if(playerTeam.isServeTurn()){
            playing = serve(playerTeam, opponent, playing);
        }else{
            playing = serve(opponent, playerTeam, playing);
        }
        while (playing) {
            if(playerTeam.isRecieveTurn()){
                playing = receive(playerTeam, opponent, playing);
            }else if(opponent.isRecieveTurn()){
                playing = receive(opponent, playerTeam, playing);
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
*/


void delay_ms(std::chrono::milliseconds ms){
	using namespace std::chrono;

	time_point<steady_clock> start = steady_clock::now();
	while(true){
		time_point<steady_clock> now = steady_clock::now();
		milliseconds duration = duration_cast<milliseconds>(now - start);
		if(duration >= ms){
			break;
		}
	}

	return;
}

bool checkSuccess(int a) {
    int dice = rand() % 100+1;
    cout << "[DEBUG] 擲骰子點數: " << dice << " (成功機率: " << a << "%)" << endl;
    delay_ms(TEXT_DELAY);
    return dice < a;
}

void flipCoin(Team& player, Team& oppo) {
    int playerChoice = 0;
    cout << "\n========== 擲硬幣階段 ==========" << endl;
    cout << "擲硬幣決定誰先發球！\n";
    cout << "你要選正面還是反面? (1: 正面, 2: 反面)\n>>";
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
    cout << "擲硬幣結果: " << (coinResult == 1 ? "正面" : "反面") << endl;
    delay_ms(TEXT_DELAY);
    if (playerChoice == coinResult) {
        cout << "恭喜你猜中了！由你們這隊先發球！\n";
        delay_ms(TEXT_DELAY);
        player.setTurn(1);
        oppo.setTurn(2);
    } else {
        cout << "你猜錯了！由對面先發球！\n";
        delay_ms(TEXT_DELAY);
        player.setTurn(2);
        oppo.setTurn(1);
    }
}

// 發球模擬，返回比賽是否繼續
bool serve(Team& serveSide, Team& oppoSide, bool playing) {
    cout << "\n========== 發球階段 ==========" << endl;
    int serveMethodNum = 0;
    if (serveSide.getIsPlayerTeam()) {
        cout << "現在是玩家隊伍的發球回合" << endl;
        delay_ms(TEXT_DELAY);
        serveMethodNum = chooseServeMethod();
        serveSide.setAttackAim(chooseAim());
    } else {
        cout << "現在是對手隊伍的發球回合" << endl;
        delay_ms(TEXT_DELAY);
        serveMethodNum = rand() % 4 + 1;
        serveSide.setAttackAim(rand() % 2 + 1);
    }

    playing = serveDamageCaculate(serveSide, oppoSide, serveMethodNum, playing);
    return playing;
}

int chooseServeMethod() {
    int serveMethodNum = 0;
    cout << "你想要用哪種方式發球呢？\n";
    cout << "(1) 大力跳發 (2) 跳飄 (3) 高手發球 (4) 低手發球\n>>";
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
    cout << "選擇的發球方式: " << serveMethodNum << endl;
    delay_ms(TEXT_DELAY);
    return serveMethodNum;
}

void chooseFront(Team& t) {
    cout << "\n========== 防守分配階段 ==========" << endl;
    if (t.getIsPlayerTeam()) {
        int frontPlayer;
        cout << "你要讓誰站在前場防守？(1: 玩家, 2: 隊友)\n>>";
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
        cout << "玩家選擇 " << (frontPlayer == 1 ? "自己" : "隊友") << " 為前排" << endl;
        t.setFront(frontPlayer);
        delay_ms(TEXT_DELAY);
    } else {
        int randomChoice = rand() % 2 + 1;
        cout << "對手選擇 " << (randomChoice == 1 ? "玩家A" : "玩家B") << " 為前排" << endl;
        t.setFront(randomChoice);
        delay_ms(TEXT_DELAY);
    }
}

bool serveDamageCaculate(Team& serveSide, Team& oppoSide, int serveMethodNum, bool playing) {
    cout << "發球方式: " << serveMethodNum << endl;
    if (serveMethodNum == 1 && checkSuccess(30 + serveSide.backPlayer().getSKL())) {
        oppoSide.setReceiveDifficulity(40 + serveSide.backPlayer().getATK() * 1.5);
        cout << "暴力即是美學！球以飛快的速度來到對手場上！\n";
        delay_ms(TEXT_DELAY);
   } else if (serveMethodNum == 2 && checkSuccess(50 + serveSide.backPlayer().getSKL())) {
        oppoSide.setReceiveDifficulity(50 + serveSide.backPlayer().getSKL() * 1.1);
        cout << "場外爆出了一陣掌聲！球左搖右晃的往對手場上衝去！\n";
        delay_ms(TEXT_DELAY);
   } else if (serveMethodNum == 3 && checkSuccess(80 + serveSide.backPlayer().getSKL())) {
        oppoSide.setReceiveDifficulity(25 + serveSide.backPlayer().getSKL() * 0.5);
        cout << "漂亮的高手發球！\n";
        delay_ms(TEXT_DELAY);
   } else if (serveMethodNum == 4 && checkSuccess(99)) {
        oppoSide.setReceiveDifficulity(15 + serveSide.backPlayer().getSKL() * 0.3);
        cout << "不求有功，但求無過～穩穩的低手發球！\n";
        delay_ms(TEXT_DELAY);
    } else {
        if(serveSide.getIsPlayerTeam()) cout << "發球失誤！對方得分QAQ\n";
        if(!serveSide.getIsPlayerTeam()) cout << "對方發球失誤！你們得分啦～\n";
        oppoSide.addPoint();
        oppoSide.setTurn(1); //換對方發球
        serveSide.setTurn(2); //己方接球
        playing = false;
    }
    delay_ms(TEXT_DELAY);
    return playing;
}

bool receive(Team& receiveSide, Team& oppoSide, bool playing) {
    cout << "\n========== 接球階段 ==========" << endl;
    delay_ms(TEXT_DELAY);
    chooseFront(receiveSide);
    if (oppoSide.getAttackAim() == 1) {
        cout << "球飛到了前場！\n";
        delay_ms(TEXT_DELAY);
        playing = checkSuccess(receiveSide.frontPlayer().getDEF() * 1.5 + receiveSide.frontPlayer().getSPD() - receiveSide.getReceiveDifficulity());
    } else {
        cout << "球飛到了後場！\n";
        delay_ms(TEXT_DELAY);
        playing = checkSuccess(receiveSide.backPlayer().getDEF() * 1.5 + receiveSide.backPlayer().getSPD() - receiveSide.getReceiveDifficulity());
    }
    if(receiveSide.getIsPlayerTeam()){
        if (playing) {
            cout << "你成功接到球了！\n";
            receiveSide.setTurn(3); //攻擊
            oppoSide.setTurn(2);//對手接球
            delay_ms(TEXT_DELAY);
            return playing;
        } else {
            cout << "沒有接到球QAQ\n對方得分！\n";
            oppoSide.addPoint();
            receiveSide.setTurn(2); //接球
            oppoSide.setTurn(1);//對手發球
            delay_ms(TEXT_DELAY);
            return playing;
        }
    }else{
        if (playing) {
            cout << "對手成功接到球了～\n";
            receiveSide.setTurn(3); //攻擊
            oppoSide.setTurn(2); //對手接球
            delay_ms(TEXT_DELAY);
            return playing;
        } else {
            cout << "對手沒有接到球QAQ\n你成功得分！\n";
            oppoSide.addPoint();
            receiveSide.setTurn(2); //接球
            oppoSide.setTurn(1); //對手發球
            delay_ms(TEXT_DELAY);
            return playing;
        }
    }
}

bool attack(Team& attackSide, Team& oppoSide, bool playing) {
    cout << "\n========== 攻擊階段 ==========" << endl;
    int attackMethod = 0;
    if(attackSide.getIsPlayerTeam()){
        attackMethod = chooseAttackMethod();
    }else{
        attackMethod = rand() % 4 + 1;
    }
    playing = setBall(attackSide, oppoSide, playing);
    if(!playing) return playing;
    if(attackSide.getIsPlayerTeam()){
        attackSide.setAttackAim(chooseAim());
    }else{
        attackSide.setAttackAim(rand() % 2 + 1);
    }
    playing = attackDamageCaculate(attackSide, oppoSide, attackMethod, playing);
    return playing;
}

bool setBall(Team& attackSide, Team& oppoSide, bool playing){
    cout << "\n========== 舉球階段 ==========" << endl;
    playing = checkSuccess(attackSide.frontPlayer().getSPD()*0.2+attackSide.frontPlayer().getSKL()*0.8+70);
    if(attackSide.getIsPlayerTeam()){
        if(playing){
            cout << "你的舉球非常漂亮的畫了一到弧線！\n";
            delay_ms(TEXT_DELAY);
            return playing;
        }else{
            cout << "舉球時，手滑掉了？？？\n對手獲得一分！\n";
            delay_ms(TEXT_DELAY);
            oppoSide.addPoint();
            oppoSide.setTurn(1);
            attackSide.setTurn(2);
            return playing;
        }
    }else{
         if(playing){
            cout << "對方舉球成功！\n";
            delay_ms(TEXT_DELAY);
            return playing;
        }else{
            cout << "對方舉球時只顧著看你的絕世容顏\n球掉到地上，你獲得一分！\n";
            delay_ms(TEXT_DELAY);
            oppoSide.addPoint();
            oppoSide.setTurn(1);
            attackSide.setTurn(2);
            return playing;
        }
    }
}

int chooseAttackMethod(){
    int attackMethodNum = 0;
    cout << "你想要用哪種方式攻擊呢？\n";
    cout << "(1) 強力扣殺 (2) 吊球 (3) 快攻 (4) 平地回擊\n>>";
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
    cout << "選擇的攻擊方式: " << attackMethodNum << endl;
    delay_ms(TEXT_DELAY);
    return attackMethodNum;
}
int chooseAim(){
    cout << "\n========== 選擇攻擊目標階段 ==========" << endl;
    int attackAimNum = 0;
    cout << "你想要把球打到對方場上的哪個地方呢？\n";
    cout << "(1) 前場 (2) 後場\n>>";
    try {
        cin >> attackAimNum;
        if (attackAimNum < 1 || attackAimNum > 2) {
            throw out_of_range("請輸入 1～2 之間的數字！\n");
        }
    } catch (out_of_range& e) {
        cout << e.what();
        cin.clear(); //XXX:但其實我沒搞懂這在幹啥
        cin.ignore(INT_MAX, '\n');
        return chooseAim();
    }
    cout << "選擇的攻擊位置: " << attackAimNum << endl;
    delay_ms(TEXT_DELAY);
    return attackAimNum;
}

bool attackDamageCaculate(Team& attackSide, Team& oppoSide, int attackMethodNum, bool playing) {
    cout << "攻擊方式: " << attackMethodNum << endl;
    if (attackMethodNum == 1 && checkSuccess(40 + attackSide.backPlayer().getSKL())) {
        oppoSide.setReceiveDifficulity(attackSide.backPlayer().getSKL() * 0.2 + attackSide.backPlayer().getATK() * 1);
        cout << "球來就是要爆扣！用力量來壓制對手！\n";
        delay_ms(TEXT_DELAY);
   } else if (attackMethodNum == 2 && checkSuccess(50 + attackSide.backPlayer().getSKL())) {
        oppoSide.setReceiveDifficulity(20 + attackSide.backPlayer().getSKL() * 0.8);
        cout << "看準對方的空檔！用吊球來迷惑對手～\n";
        delay_ms(TEXT_DELAY);
   } else if (attackMethodNum == 3 && checkSuccess(40 + attackSide.backPlayer().getSKL())) {
        oppoSide.setReceiveDifficulity(attackSide.backPlayer().getATK() * 0.6 + attackSide.backPlayer().getSKL() * 0.4 + attackSide.backPlayer().getSPD() * 0.5);
        cout << "迅！快！猛！用出其不意的快攻來取分！\n";
        delay_ms(TEXT_DELAY);
   } else if (attackMethodNum == 4 && checkSuccess(99)) {
        oppoSide.setReceiveDifficulity(20 + attackSide.backPlayer().getSKL() * 0.1);
        cout << "穩穩地把球打過去才是王道！球往隊手場上了飛過去～\n";
        delay_ms(TEXT_DELAY);
   } else {
        delay_ms(TEXT_DELAY);
        if(attackSide.getIsPlayerTeam()) cout << "攻擊失誤！對方得分QAQ\n";
        if(!attackSide.getIsPlayerTeam()) cout << "對方攻擊失誤！你們得分啦～\n";
        delay_ms(TEXT_DELAY);
        oppoSide.addPoint();
        oppoSide.setTurn(1); //換對方發球
        attackSide.setTurn(2); //己方接球
        playing = false;
    }
    return playing;
}
