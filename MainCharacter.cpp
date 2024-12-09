#include "MainCharacter.h"

MainCharacter::MainCharacter(const MainCharacter& another){
    this->name = another.name;
    this->atk = another.atk;
    this->def = another.def;
    this->spd = another.spd;
    this->luk = another.luk;
    this->spLimit = another.spLimit;
    this->skl = another.skl;
    this->mny = another.mny;
    this->partner = another.partner;
}

MainCharacter& MainCharacter::operator=(const MainCharacter& another){
    if (this == &another){
        return *this; // 防止自我賦值
    }   
    this->name = another.name;
    this->atk = another.atk;
    this->def = another.def;
    this->spd = another.spd;
    this->luk = another.luk;
    this->spLimit = another.spLimit;
    this->skl = another.skl;
    this->mny = another.mny;
    this->partner = another.partner;
    return *this;
}

void MainCharacter::setName(string newName){
    name = newName;
}

void MainCharacter::setPartner(string newPartner){
    partner = newPartner;
}

void MainCharacter::addATK(int value){
    atk += value;
}

void MainCharacter::addDEF(int value){
    def += value;
}

void MainCharacter::addSPD(int value){
    spd += value;
}

void MainCharacter::addLUK(int value){
    luk += value;
}

void MainCharacter::addSPLimit(int value){
    spLimit += value;
}

void MainCharacter::addSKL(int value){
    skl += value;
}

void MainCharacter::addMNY(int value){
    mny += value;
}

