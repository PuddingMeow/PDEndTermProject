#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H

#include <string>
using namespace std;

class MainCharacter
{
protected:
    string name; //主角名稱
    int atk; //攻擊
    int def; //防禦
    int spd; //速度
    int luk; //幸運值
    int spLimit; //精力上限
    int skl; //技術
    int mny; //錢錢
    string partner; //夥伴(應該只有一位)
public:
    MainCharacter() : name("鸣喆"), atk(0), def(0), spd(0), luk(0), spLimit(0), skl(0), mny(0), partner("no_partner")
    {
    };
    MainCharacter(const MainCharacter& another);

    //getters
    string getName() { return name; };
    int getATK() { return atk; };
    int getDEF() { return def; };
    int getSPD() { return spd; };
    int getLUK() { return luk; };
    int getSPLimit() { return spLimit; };
    int getSKL() { return skl; };
    int getMNY() { return mny; }; 
    string listPartner() { return partner; };

    //setters
    void setName(string newName);
    void setPartner(string newPartner);

    //加or減各項數值
    void addATK(int value);
    void addDEF(int value);
    void addSPD(int value);
    void addLUK(int value);
    void addSPLimit(int value);
    void addSKL(int value);
    void addMNY(int value);

};

#endif
