#include <bits/stdc++.h>// 用於測試和輸出
#include "MainCharacter.h" // 假設 MainCharacter 定義在此檔案中
using namespace std;

class Team {
private:
    int score;                // 團隊的分數
    bool isPlayerTeam;        // 是否是玩家的隊伍
    MainCharacter A;          // 玩家 A
    MainCharacter B;          // 玩家 B
    bool front;               // 誰在前面 (0 是 A，1 是 B)
    int turn;                 // 回合狀態 (0: 初始化, 1: 發球, 2: 接球, 3: 攻擊)
    int receiveDifficulity;   // 接球的難度值

public:
    // 建構子：初始化隊伍
    Team(MainCharacter& playerA, MainCharacter& playerB, bool isPlayer)
        : A(playerA), B(playerB), isPlayerTeam(isPlayer), score(0), front(true), turn(0), receiveDifficulity(0) {}

    // 複製建構子
    Team(const Team& t)
        : score(t.score), isPlayerTeam(t.isPlayerTeam), A(t.A), B(t.B),
          front(t.front), turn(t.turn), receiveDifficulity(t.receiveDifficulity) {}

    // 賦值運算子
    Team& operator=(const Team& t) {
        if (this == &t) return *this; // 防止自我賦值
        score = t.score;
        isPlayerTeam = t.isPlayerTeam;
        A = t.A;
        B = t.B;
        front = t.front;
        turn = t.turn;
        receiveDifficulity = t.receiveDifficulity;
        return *this;
    }

    // 取得分數
    int getScore() const {
        return score;
    }

    // 增加分數
    void addPoint() {
        score++;
    }

    // 設定前排球員 (1: A, 2: B)
    void setFront(int frontNum) {
        front = (frontNum == 2);
    }

    // 獲取前排的球員
    MainCharacter& frontPlayer() {
        return front ? B : A;
    }

    // 獲取後排的球員
    MainCharacter& backPlayer() {
        return front ? A : B;
    }

    // 設定回合狀態
    void setTurn(int turnNum) {
        turn = turnNum;
    }

    // 確認是否是發球回合
    bool isServeTurn() const {
        return turn == 1;
    }

    // 確認是否是接球回合
    bool isRecieveTurn() const {
        return turn == 2;
    }

    // 確認是否是攻擊回合
    bool isAttackTurn() const {
        return turn == 3;
    }

    // 設定接球難度
    void setReceiveDifficulity(int rd) {
        if (rd >= 0) {
            receiveDifficulity = rd;
        } else {
            cout << "接球難度不能為負數！" << endl;
        }
    }

    // 確認是否是玩家的隊伍
    bool isPlayerTeamFunc() const {
        return isPlayerTeam;
    }
};
