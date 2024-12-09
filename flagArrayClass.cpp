#include "flagArrayClass.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <iomanip>

// Flag* binarySearch(const Flag* array, std::string flagName, int start_pos, int end_pos);
/*
int main(){
    FlagArray test;
    test.print();
    std::cout << test.checkFlagStatus("recruitXiaoJie_1") << std::endl;
    test.updateFlagStatus("recruitXiaoJie_1", true);
    std::cout << test.checkFlagStatus("recruitXiaoJie_1") << std::endl;
    return 0;
}*/

Flag* FlagArray::linearSearch(std::string flagName) const {
    for(int i = 0; i < this->flagCnt; ++i){
        if(this->flag[i].name == flagName){
            return (this->flag + i);
        }
    }
    return nullptr;
}

// default constructor builds flagArray with predesignated text file,
// where all flag names are listed.
// use the text file to add or remove flags.
FlagArray::FlagArray() {
    std::ifstream file("init_config/flagList.txt");

    if(file.is_open() == false){
        throw file_error("Missing file: init_config/flagList.txt");
    }

    file >> this->flagCnt;
    this->flag = new Flag[flagCnt];

    std::string flagName = "";
    for(int i = 0; i < flagCnt; ++i){
        file >> flagName;
        flag[i] = {flagName, 0};
    }

    file.close();
}

FlagArray::FlagArray(const FlagArray& fa) {
    this->flagCnt = fa.flagCnt;
    this->flag = new Flag[this->flagCnt];

    for(int i = 0; i < this->flagCnt; ++i){
        this->flag[i] = fa.flag[i];
    }
}

FlagArray::~FlagArray() {
    delete [] this->flag;
}

const FlagArray& FlagArray::operator=(const FlagArray& fa) {
    for(int i = 0; i < this->flagCnt; ++i){
        this->flag[i].status = fa.flag[i].status;
    }
    return *this;
}

Flag& FlagArray::operator[](int index) {
    if(index < 0 || index >= this->flagCnt){
        throw std::out_of_range("FlagArray: invalid index accessed");
    }
    return (this->flag[index]);
}

int FlagArray::getFlagCnt() const {
    return (this->flagCnt);
}

// returns target flag status.
bool FlagArray::checkFlagStatus(std::string flagName) const {
    Flag* targetFlag = this->linearSearch(flagName);
    if(targetFlag == nullptr){
        std::string errMsg = "Flag does not exist: " + flagName;
        throw file_error(errMsg);
    }
    return targetFlag->status;
}

// updates target flag.
void FlagArray::updateFlagStatus(std::string flagName, bool status) {
    Flag* targetFlag = this->linearSearch(flagName);
    if(targetFlag == nullptr){
        std::string errMsg = "Flag does not exist: " + flagName;
        throw file_error(errMsg);
    }
    targetFlag->status = status;
    return;
}

// print all flags.
void FlagArray::print() const {
    for(int i = 0; i < this->flagCnt; ++i){
        std::cout << std::setw(20) << this->flag[i].name << " || ";
        std::cout << this->flag[i].status << std::endl;
    }
    return;
}

/* possible optimisation.
Flag* binarySearch(const Flag* array, std::string flagName, int start_pos, int end_pos) {
    int mid_pos = (start_pos + end_pos) / 2;
    if(array[mid_pos].name == flagName){
        return (array + mid_pos);
    }else if(end_pos - start_pos == 1){

    }else{
        
    }
}*/