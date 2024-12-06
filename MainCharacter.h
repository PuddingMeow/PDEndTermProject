#include <string>
using namespace std;

class MainCharacter
{
private:
    string name; //主角名稱
    int atk; //攻擊
    int def; //防禦
    int spd; //速度
    int luk; //幸運值
    int spLimit; //精力上限
    int mny; //錢錢
    string partner; //夥伴(應該只有一位)
public:
    MainCharacter() : atk(0), def(0), spd(0), luk(0), spLimit(0), mny(0)
    {
    };

    //getters
    string getName() { return name; };
    int getATK() { return atk; };
    int getDEF() { return def; };
    int getSPD() { return spd; };
    int getLUK() { return luk; };
    int getSPLimit() { return spLimit; };
    int getMNY() { return mny; };
    string listPartner() { return partner; };

    //加or減各項數值
    void addATK(int value);
    void addDEF(int value);
    void addSPD(int value);
    void addLUK(int value);
    void addSPLimit(int value);
    void addMNY(int value);

};
