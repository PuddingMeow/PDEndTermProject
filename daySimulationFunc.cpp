#include "daySimulationFunc.h"
#include "eventFunction.h"
#include "flagArrayClass.h"
#include "saveFileClass.h"
#include "MainCharacter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

class TriggerCondition {
    protected:
        std::string attribute;
    public:
        TriggerCondition(std::string attribute);

        virtual bool verify(MainCharacter& player, FlagArray& flags) = 0;
        virtual void print() const = 0;
};

class StatGate : public TriggerCondition{
    protected:
        std::string lockType; // comparison operators for stat check, +/- for toll fee 
        int value;
    public:
        StatGate(std::string statType, std::string lockType, int value);
        
        bool verify(MainCharacter& player, FlagArray& flags);
        void print() const;
};

class FlagGate : public TriggerCondition{
    protected:
        std::string flagName;
        bool status;
    public:
        FlagGate(std::string flagname, bool status);

        bool verify(MainCharacter& player, FlagArray& flags);
        void print() const;
};

class MenuOption {
    private:
        std::string eventFileName;
        std::string label;
        std::string description;
        std::vector<TriggerCondition*> triggerConditions;

        MenuOption(const MenuOption&) {/*blocked*/};
        void operator=(const MenuOption&) {/*blocked*/};
    public:
        MenuOption(std::string eventFileName, std::string label, std::string description);
        ~MenuOption();

        int addTriggerCondition(std::string statType, std::string lockType, int value);
        int addTriggerCondition(std::string flagName, bool status);
        void printLabel() const;
        void printDescription() const;
        bool trigger(MainCharacter& player, FlagArray& flags);

        void print() const;

};

class Menu {
    private:
        std::vector<MenuOption*> options;

        Menu(const Menu&) {/*blocked*/};
        void operator=(const Menu&) {/*blocked*/};
    public:
        Menu() {};
        ~Menu();

        int getOptionCnt() const {return this->options.size();};

        int addOption(std::string eventFileName, std::string label, std::string description);
        int addTriggerCondition(int index, std::string statType, std::string lockType, int value);
        int addTriggerCondition(int index, std::string flagName, bool status);

        void printOptions() const;
        void trigger(MainCharacter& player, FlagArray& flags);

        void print() const;
};

/*int main() {
    SaveFile save(1);
    MainCharacter player(save.getPlayer());
    FlagArray flags(save.getFlags());

    player.addLUK(1987);

    flags[0].status = true;

    Event event_1("event1.txt");
    Event event_2("event3.txt");
    Event event_3("event4.txt");
    
    event_1.trigger(player, flags);
    event_2.trigger(player, flags);
    event_3.trigger(player, flags);

    save.update(1, player, flags);

    save.exportTo();

    SaveFile newSave(1);
    newSave.importFrom(1);
    newSave.print();

    player.addMNY(2000);

    daySimulation(1, player, flags);

    /*Menu menu;
    menu.addOption("event1.txt", "Go Outside", "Touch grass lol");
    menu.addOption("event3.txt", "Do Whatever", "idkman");

    menu.addTriggerCondition(1, "test_flag", true);
    menu.addTriggerCondition(1, "MNY", "-", 200);

    menu.trigger(player, flags);

    Menu menu(2);
    menu.addEventOption("Training Area", "Hone your skills!", "training_atk.txt");
    menu.addEventOption("Outside", "Leave the dorms!", "event1.txt");

    menu.triggerMenu(player, flags);

    save.update(1, player, flags);

    save.exportTo();

    SaveFile newSave(1);
    newSave.importFrom(1);
    newSave.print();

    return 0;
}*/

// class: TriggerCondition
TriggerCondition::TriggerCondition(std::string attribute)
 : attribute(attribute)
{}

// class: StatGate
StatGate::StatGate(std::string statType, std::string lockType, int value)
 : TriggerCondition(statType), lockType(lockType), value(value)
{}

void StatGate::print() const {
    std::cout << "StatGate: type " << this->attribute << " " << this->lockType << this->value;
}

bool StatGate::verify(MainCharacter& player, FlagArray& flags) {
    int player_stat_value = 0;
    if(this->attribute == "MNY"){
        player_stat_value = player.getMNY();
    }else{
        std::string msg = "StatGate: invalid attribute (" + this->attribute + ")";
        throw std::logic_error(msg);
    }

    if(this->lockType == "-"){
        if(player_stat_value >= this->value){
            return true;
        }else{
            return false;
        }
    }else{
        std::string msg = "StatGate: invalid lockType (" + this->lockType + ")";
        throw std::logic_error(msg);        
    }
}

// class: FlagGate
FlagGate::FlagGate(std::string flagName, bool status)
 : TriggerCondition("FLAG"), flagName(flagName), status(status)
{}

void FlagGate::print() const {
    std::cout << "FlagGate: " << this->flagName << " " << this->status;
}

bool FlagGate::verify(MainCharacter& player, FlagArray& flags) {
    bool player_flag_status = flags.checkFlagStatus(this->flagName);
    if(player_flag_status == this->status){
        return true;
    }else{
        return false;
    }
}

// class: MenuOption
MenuOption::MenuOption(std::string eventFileName, std::string label, std::string description)
 : eventFileName(eventFileName), label(label), description(description)
{}

MenuOption::~MenuOption() {
    for(int i = 0; i < this->triggerConditions.size(); ++i){
        delete triggerConditions[i];
    }
}

int MenuOption::addTriggerCondition(std::string statType, std::string lockType, int value) {
    StatGate* cond = new StatGate(statType, lockType, value);
    this->triggerConditions.push_back(cond);
    return triggerConditions.size();
}

int MenuOption::addTriggerCondition(std::string flagName, bool status) {
    FlagGate* cond = new FlagGate(flagName, status);
    this->triggerConditions.push_back(cond);
    return triggerConditions.size();    
}

void MenuOption::printLabel() const {
    std::cout << this->label;
    return;
}
void MenuOption::printDescription() const {
    std::cout << this->description;
    return;
}

bool MenuOption::trigger(MainCharacter& player, FlagArray& flags) {
    // check conditions.
    for(int i = 0; i < this->triggerConditions.size(); ++i){
        if(this->triggerConditions[i]->verify(player, flags) == false){
            return false;
        }
    }
    
    // trigger event.
    triggerEvent(this->eventFileName, player, flags);

    return true;
}

void MenuOption::print() const {
    std::cout << "MenuOption: " << this->eventFileName << "\n";
    std::cout << "label: " << this->label << "\n";
    std::cout << "descr: " << this->description << "\n";
    for(int i = 0; i < this->triggerConditions.size(); ++i){
        this->triggerConditions[i]->print();
        std::cout << "\n";
    }
    return;
}

// class: Menu
Menu::~Menu() {
    for(int i = 0; i < this->options.size(); ++i){
        delete this->options[i];
    }
}

int Menu::addOption(std::string eventFileName, std::string label, std::string description) {
    MenuOption* option = new MenuOption(eventFileName, label, description);
    this->options.push_back(option);
    return this->options.size();
}

int Menu::addTriggerCondition(int index, std::string statType, std::string lockType, int value) {
    if(index < 0 || index >= this->options.size()){
        throw std::out_of_range("Menu: failed to add TriggerCondition");
    }
    return this->options[index]->addTriggerCondition(statType, lockType, value);
}

int Menu::addTriggerCondition(int index, std::string flagName, bool status) {
    if(index < 0 || index >= this->options.size()){
        throw std::out_of_range("Menu: failed to add TriggerCondition");
    }
    return this->options[index]->addTriggerCondition(flagName, status);
}

void Menu::printOptions() const {
    std::cout << "(1) ";
    this->options[0]->printLabel();
    for(int i = 1; i < this->options.size(); ++i){
        std::cout << '\n';
        std::cout << "(" << i + 1 << ") ";
        this->options[i]->printLabel();
    }
    std::cout << '\n';
    return;
}

void Menu::trigger(MainCharacter& player, FlagArray& flags) {
    int player_choice = 0;
    while(true){
        this->printOptions();

        // prompt and get player input.
        std::cout << "＞＞你的選擇：";
        std::string raw_input = "";
        std::getline(std::cin, raw_input);

        // verify input.
        try{
            player_choice = stoi(raw_input);
            if(player_choice <= 0 || player_choice > this->options.size()){
                throw std::out_of_range("player_choice out of range");
            }
        }catch(std::invalid_argument& e){
            std::cout << "＞＞請輸入有效數字！數字就好，括號不用～\n";
        }catch(std::out_of_range& e){
            std::cout << "＞＞請輸入有效數字！選擇：（";
			std::cout << "1";
			for(int i = 1; i < 3; ++i){
				std::cout << "," << i + 1;
			}
			std::cout << "）\n";
        }

        --player_choice;

        // confirmation.
        std::cout << "＞＞";
        this->options[player_choice]->printDescription();
        std::cout << std::endl;
        std::cout << "＞＞確認選擇（Ｙ／Ｎ）：";
        std::getline(std::cin, raw_input);
        
        if(raw_input != "Y"){
            std::cout << "＞＞取消選擇。" << '\n';
            delay_ms(TEXT_DELAY);
            continue;
        }

        // trigger event. checks if all conditions are met.
        if(this->options[player_choice]->trigger(player, flags) == false){
            std::cout << "＞＞未符合條件！請重新選擇。" << std::endl;
            continue;
        }

        break;
    }
    return;
}

void daySimulation(int dayCnt, SaveFile& save) {
    // extract save data.
    MainCharacter player = save.getPlayer();
    FlagArray flags = save.getFlags();

    // import schedule file.
    std::string path = "day_schedule\\day_schedule_" + to_string(dayCnt) + ".txt";
    std::ifstream file(path);
    if(file.is_open() == false){
        std::string msg = path + " does not exist.";
        throw logic_error(msg);
    }

    // parse file.
    while(true){
        std::string command = "";
        std::getline(file, command);

        std::string input = "";
        if(command == "event"){
            std::getline(file, input);
            triggerEvent(input, player, flags);
        }else if(command == "gatedEvent"){
            std::string eventFileName = "";
            std::vector<TriggerCondition*> conditions;
            while(true){
                std::getline(file, input);
                if(input == "stat"){
                    std::string statType;
                    std::string lockType;
                    int value;

                    std::getline(file, statType);
                    std::getline(file, lockType);
                    std::getline(file, input);
                    value = std::stoi(input);

                    StatGate* cond = new StatGate(statType, lockType, value);
                    conditions.push_back(cond);

                }else if(input == "flag"){
                    std::string flagName;
                    bool status;

                    std::getline(file, flagName);
                    std::getline(file, input);
                    status = std::stoi(input);

                    FlagGate* cond = new FlagGate(flagName, status);
                    conditions.push_back(cond);

                }else if(input == "event"){
                    std::getline(file, eventFileName);
                    break;
                }else{
                    std::string msg = "Invalid file formatting: " + path;
                    throw std::logic_error(msg);
                }
            }

            bool checksPassed = true;
            for(int i = 0; i < conditions.size(); ++i){
                if(conditions[i]->verify(player, flags) == false){
                    checksPassed = false;
                    break;
                }
            }

            if(checksPassed){
                triggerEvent(eventFileName, player, flags);
            }

            for(int i = 0; i < conditions.size(); ++i){
                delete conditions[i];
            }
        }else if(command == "action"){
            Menu menu;
            while(true){
                std::getline(file, input);
                if(input == "option"){
                    std::string eventFileName = "";
                    std::string label = "";
                    std::string description = "";

                    std::getline(file, eventFileName);
                    std::getline(file, label);
                    std::getline(file, description);

                    menu.addOption(eventFileName, label, description);
                }else if(input == "stat"){
                    std::string statType;
                    std::string lockType;
                    int value;

                    std::getline(file, statType);
                    std::getline(file, lockType);
                    std::getline(file, input);
                    value = std::stoi(input);

                    menu.addTriggerCondition(menu.getOptionCnt() - 1, statType, lockType, value);                 
                }else if(input == "flag"){
                    std::string flagName;
                    bool status;

                    std::getline(file, flagName);
                    std::getline(file, input);
                    status = std::stoi(input);

                    menu.addTriggerCondition(menu.getOptionCnt() - 1, flagName, status);
                }else if(input == "endAction"){
                    break;
                }else{
                    std::string msg = "Invalid file formatting: " + path;
                    throw std::logic_error(msg);
                }
            }
            menu.print();
            menu.trigger(player, flags);
        }else if(command == "endDay"){
            break;
        }else{
            std::string msg = "Invalid file formatting: " + path;
            throw std::logic_error(msg);
        }

        std::getline(file, input); // skip empty line.
    }

    // update save data.
    save.update(dayCnt, player, flags);
    std::cout << "＞＞存檔已更新。";

    file.close();
    return;
}

void Menu::print() const {
    for(int i = 0; i < this->options.size(); ++i){
        this->options[i]->print();
    }
    return;
}
