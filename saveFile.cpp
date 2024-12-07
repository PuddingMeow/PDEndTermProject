#include "saveFile.h"
#include "flags.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

// create new save.
SaveFile::SaveFile(int id, bool tempDistinguisher) : id(id), dayCnt(1)/*, MainCharacter(player)*/
{
}

// read from save.
void SaveFile::importFrom(int id) {
    std::string path = "saves/save" + std::to_string(id) + ".txt";
    std::ifstream save(path);

    if(save.is_open() == false){
        throw std::runtime_error("failed to load save: file does not exist");
    }

    std::string str = ""; // container for formatting.
    bool status = false;

    save >> str >> this->dayCnt;

    save >> str;
    for(int i = 0; i < this->flags.getFlagCnt(); ++i){
        save >> status;
        this->flags[i].status = status;
    }
    
    save.close();
    return;
}

void SaveFile::update(int dayCnt/*, MainCharacter player*/, FlagArray flags) {
    if(dayCnt <= 0){
        throw std::invalid_argument("SaveFile::updateSave failed: invalid dayCnt");
    }
    this->dayCnt = dayCnt;
//  this->player = player;
    this->flags = flags;
    return;
}

void SaveFile::exportTo(){
    std::string path =  "saves/save" + std::to_string(id) + ".txt";
    std::ofstream save(path);
    
    // missing player data.
    save << "currentDayCnt: " << dayCnt << "\n\n";

    save << "flagStates:\n";
    save << this->flags[0].status;
    for(int i = 1; i < this->flags.getFlagCnt(); ++i){
        save << "\n" << this->flags[i].status;
    }

    save.close();
    return;
}

void SaveFile::print() const {
    std::cout << "dayCnt: " << this->dayCnt << "\n";
    std::cout << "flagStatus:\n";
    this->flags.print();
    return;
}