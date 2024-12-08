#include "saveFile.h"
#include "flags.h"
#include "MainCharacter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

// create new save.
SaveFile::SaveFile(int id) : id(id), dayCnt(1)
{
}

int SaveFile::getID() const {
    return this->id;
}

int SaveFile::getDayCnt() const {
    return this->dayCnt;
}

MainCharacter SaveFile::getPlayer() const {
    return this->player;
}

FlagArray SaveFile::getFlags() const {
    return this->flags;
}

// read from save.
void SaveFile::importFrom(int id) {
    std::string path = "saves/save" + std::to_string(id) + ".txt";
    std::ifstream save(path);

    if(save.is_open() == false){
        throw std::runtime_error("failed to load save: file does not exist");
    }

    std::string str = ""; // container for formatting.
    int value = 0;
    bool status = false;

    save >> str >> this->dayCnt;

    save >> str;
    save >> str >> str;
    player.setName(str);
    save >> str >> value;
    player.addATK(value);
    save >> str >> value;
    player.addDEF(value);
    save >> str >> value;
    player.addSPD(value);
    save >> str >> value;
    player.addLUK(value);
    save >> str >> value;
    player.addSPLimit(value);
    save >> str >> value;
    player.addSKL(value);
    save >> str >> value;
    player.addMNY(value);
    save >> str >> str;
    player.setPartner(str);

    save >> str;
    for(int i = 0; i < this->flags.getFlagCnt(); ++i){
        save >> status;
        this->flags[i].status = status;
    }
    
    save.close();
    return;
}

void SaveFile::update(int dayCnt, MainCharacter player, FlagArray flags) {
    if(dayCnt <= 0){
        throw std::invalid_argument("SaveFile::updateSave failed: invalid dayCnt");
    }
    this->dayCnt = dayCnt;
    this->player = player;
    this->flags = flags;
    return;
}

void SaveFile::exportTo(){
    std::string path =  "saves/save" + std::to_string(id) + ".txt";
    std::ofstream save(path);
    
    save << "currentDayCnt: " << dayCnt << "\n\n";

    save << "playerStatus:\n";
    save << "name: " << player.getName() << "\n";
    save << "ATK: " << player.getATK() << "\n";
    save << "DEF: " << player.getDEF() << "\n";
    save << "SPD: " << player.getSPD() << "\n";
    save << "LUK: " << player.getLUK() << "\n";
    save << "SPLimit: " << player.getSPLimit() << "\n";
    save << "SKL: " << player.getSKL() << "\n";
    save << "MNY: " << player.getMNY() << "\n";
    save << "partner: " << player.listPartner() << "\n\n";

    save << "flagStates:\n";
    save << this->flags[0].status;
    for(int i = 1; i < this->flags.getFlagCnt(); ++i){
        save << "\n" << this->flags[i].status;
    }

    save.close();
    return;
}

void SaveFile::print() {
    std::cout << "dayCnt: " << this->dayCnt << "\n";
    
    std::cout << "playerName: " << this->player.getName() << "\n";
    std::cout << "atk: " << this->player.getATK() << "\n";
    std::cout << "def: " << this->player.getDEF() << "\n";
    std::cout << "spd: " << this->player.getSPD() << "\n";
    std::cout << "luk: " << this->player.getLUK() << "\n";
    std::cout << "splimit: " << this->player.getSPLimit() << "\n";
    std::cout << "skl: " << this->player.getSKL() << "\n";
    std::cout << "mny: " << this->player.getMNY() << "\n";
    std::cout << "partner: " << this->player.listPartner() << "\n";

    std::cout << "flagStatus:\n";
    this->flags.print();
    return;
}