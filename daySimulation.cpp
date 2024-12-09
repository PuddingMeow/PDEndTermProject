#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "eventFunction.h"
#include "flagArrayClass.h"
#include "saveFileClass.h"
#include "MainCharacter.h"

class MenuOption {
    protected:
        int type; // 1: EventOption; 2: BackOption
        std::string displayText;

    public:
        MenuOption(int type, std::string displayText);

        int getType() const {return this->type;};

        virtual void printDisplayText() const;
        virtual void printConfirmation() const = 0;
        virtual bool processConfirmation(MainCharacter& player, FlagArray& flags) = 0;
};

class EventOption : public MenuOption {
    protected:
        std::string description;
        std::string eventFileName;
    public:
        EventOption(std::string displayText, std::string description, std::string eventFileName);

        void printDisplayText() const;
        void printConfirmation() const;
        bool processConfirmation(MainCharacter& player, FlagArray& flags);
};

class Menu {
    private:
        int optionCnt;
        int maxOptionCnt;
        MenuOption** options;

        Menu(const Menu&) {/*blocked*/};
        const Menu& operator=(const Menu&) {/*blocked*/ return *this;};

        void printOptionList() const;
        void promptAndProcessUserInput(MainCharacter& player, FlagArray& flags);
    public:
        Menu(int optionCnt);
        ~Menu();

        void addEventOption(std::string displayText, std::string description, std::string eventFileName);
        void triggerMenu(MainCharacter& player, FlagArray& flags);
};


/*class GameState {
    private:
        int totalTurns;
        int remainingTurns;
    public:
};*/

//void daySimulation(int dayCnt, FlagArray flags);

int main() {
    SaveFile save(1);
    MainCharacter player(save.getPlayer());
    FlagArray flags(save.getFlags());

    /*player.addLUK(1987);

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
    newSave.print();*/

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
}

// class: MenuOption
MenuOption::MenuOption(int type, std::string displayText) : type(type), displayText(displayText)
{
}

void MenuOption::printDisplayText() const {
    std::cout << "type(" << this->type << ") ";
    std::cout << "displayText: " << this->displayText << "\n";
    return;
}

// class: EventOption
EventOption::EventOption(std::string displayText, std::string description, std::string eventFileName) 
 : MenuOption(1, displayText), description(description), eventFileName(eventFileName)
{
}

void EventOption::printDisplayText() const {
    MenuOption::printDisplayText();
    return;
}

void EventOption::printConfirmation() const {
    std::cout << this->description << "\n";
    std::cout << "＞＞確認你的選擇？（Ｙ／Ｎ）：";
    return;
}

bool EventOption::processConfirmation(MainCharacter& player, FlagArray& flags) {
    std::string raw_input = "";
    std::getline(std::cin, raw_input);

    if(raw_input == "Y"){
        triggerEvent(this->eventFileName, player, flags);
        return true;
    }else{
        std::cout << "＞＞取消選擇，返回母選單。\n";
        return false;
    }
}



// class: Menu: public
Menu::Menu(int maxOptionCnt) : optionCnt(0), maxOptionCnt(maxOptionCnt) {
    this->options = new MenuOption*[this->maxOptionCnt];
}

Menu::~Menu() {
    for(int i = 0; i < this->optionCnt; ++i){
        delete options[i];
    }
    delete [] options;
}

void Menu::addEventOption(std::string displayText, std::string description, std::string eventFileName) {
    if(this->optionCnt == this->maxOptionCnt) {
        throw std::logic_error("maxOptionCnt of Menu exceeded");
    }

    this->options[optionCnt] = new EventOption(displayText, description, eventFileName);
    ++this->optionCnt;
    return;
}

void Menu::triggerMenu(MainCharacter& player, FlagArray& flags) {
    this->printOptionList();
    this->promptAndProcessUserInput(player, flags);
    return;
}

// class: Menu: private
void Menu::printOptionList() const {
    for(int i = 0; i < this->optionCnt; ++i){
        switch(this->options[i]->getType()){
            case 1: // EventOption
                std::cout << "(" << i + 1 << ")";
                options[i]->printDisplayText();
                break;
            default:
                throw std::logic_error("MenuOption: invalid option type");
        }
    }
}

void Menu::promptAndProcessUserInput(MainCharacter& player, FlagArray& flags) {
    int player_choice = 0;

    // input processing.
    while(true){
        std::cout << "＞＞你的選擇：";

        std::string raw_input = "";
        std::getline(std::cin, raw_input);

        try{
            player_choice = stoi(raw_input);
            if(player_choice <= 0 || player_choice > this->optionCnt){
                throw std::out_of_range("player_choice out of range");
            }
            break;
        }
        catch(std::invalid_argument& e){
            std::cout << "＞＞請輸入有效數字！數字就好，括號不用～\n";
        }
        catch(std::out_of_range& e){
            std::cout << "＞＞請輸入有效數字！選擇：（";
			std::cout << "1";
			for(int i = 1; i < this->optionCnt; ++i){
				std::cout << "," << i + 1;
			}
			std::cout << "）\n";
        }
    }

    --player_choice; // adjust player_choice to match index.

    // trigger option.
    switch(this->options[player_choice]->getType()){
        case 1: // EventOption
            {
                options[player_choice]->printConfirmation();
                bool confirmation = options[player_choice]->processConfirmation(player, flags);

                if(confirmation == false){
                    this->triggerMenu(player, flags);
                }

                break;
            }
        default:
            throw std::logic_error("MenuOption: invalid option type");
    }

    return;
}