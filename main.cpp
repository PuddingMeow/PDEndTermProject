#include <bits/stdc++.h>
#include "MainCharacter.h"
#include "flagArrayClass.h"
#include "saveFileClass.h"
#include "eventFunction.h"
#include "battleSimulationFunc.h"
#include "daySimulationFunc.h"
using namespace std;

void mainMenu(SaveFile& save);
bool createNewSave(SaveFile& save);
bool loadSave(SaveFile& save);
void printSaveList();

void dayStart(int dayCnt);
void dayEnd(int& dayCnt, MainCharacter player);

void choosePartner(SaveFile& save);

int main(){
    int dayCnt = 1; //現在的天數
    int nextBattleDay = 6;
    int finalDay = 6; //數值我歲便寫的2，最後一天

    while(true){
        SaveFile save(1);

        mainMenu(save);

        while(dayCnt <= finalDay){
            dayStart(dayCnt);

            if(dayCnt == nextBattleDay){
                choosePartner(save);

                MainCharacter player = save.getPlayer();
                //bool winState = battleSimulation(player, , , );
                nextBattleDay += 6;
            }else{
                daySimulation(dayCnt, save);
            }
            ++dayCnt;

            dayEnd(dayCnt, save.getPlayer());

            std::string raw_input = "";
            std::cout << "＞＞要繼續游戲嗎？（Ｙ／Ｎ）：" << '\n';
            std::getline(std::cin, raw_input);
            if(raw_input != "Y"){
                std::cout << "＞＞返回游戲主頁。" << '\n';
                break;
            }
        }
    }

    return 0;
}

void mainMenu(SaveFile& save) {
    MainCharacter player;
    FlagArray flags;
    int player_choice = 0;
    while(true){
        std::cout << "\n\n===== 排球訓練日記 =====\n\n";
        std::cout << "(1) 開始新游戲\n";
        std::cout << "(2) 讀取存檔\n";
        std::cout << "(3) 結束游戲\n";
        std::cout << "\n ~by times-1 && mcchiang && changi~ \n\n";

        std::cout << "＞＞你的選擇：";
        std::string raw_input = "";
        std::getline(std::cin, raw_input);

        try{
            player_choice = stoi(raw_input);
            if(player_choice <= 0 || player_choice > 3){
                throw std::out_of_range("player_choice out of range");
            }
            break;
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
    }

    bool action_success = false;
    switch(player_choice){
        case 1:
            action_success = createNewSave(save);
            break;
        case 2:
            action_success = loadSave(save);
            break;
        case 3:
            std::cout << "謝謝游玩~~";
            delay_ms(TEXT_DELAY);
            delay_ms(TEXT_DELAY);
            exit(0);
            break;
        default:
            throw logic_error("invalid player_choice");
    }

    // if action failed, return to main menu. else, update save.
    if(action_success == false){
        mainMenu(save);
    }else{

    }

    return;
}

bool createNewSave(SaveFile& save){
    printSaveList();

    std::string raw_input = "";
    int player_choice = 0;
    while(true){
        // prompt and get player input.
        std::cout << "＞＞輸入存檔編號：";
        std::getline(std::cin, raw_input);

        // processing and validation.
        try{
            player_choice = stoi(raw_input);
            if(player_choice <= 0 || player_choice > 3){
                throw std::out_of_range("player_choice out of range");
            }
            break;
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
    }
    
    // confirmation.
    std::cout << "＞＞注意：將覆蓋既有存檔。確認選擇（Ｙ／Ｎ）：";
    std::getline(std::cin, raw_input);
    
    if(raw_input != "Y"){
        std::cout << "＞＞取消選擇，返回選單。";
        delay_ms(TEXT_DELAY);
        return false;
    }

    std::string playerName = "";
    while(true){
        // prompt and get player name.
        std::cout << "＞＞爲你自己命名吧！" << std::endl;
        std::cout << "＞＞請輸入名稱：";
        std::getline(std::cin, raw_input);
        playerName = raw_input;

        // confirmation.
        if(raw_input == ""){
            raw_input = save.getPlayer().getName();
            std::cout << "【" << raw_input << "】（默認名稱）" << std::endl;
        }else{
            std::cout << "【" << raw_input << "】" << std::endl;
        }
        std::cout << "確定要取這個名字嗎？（Ｙ／Ｎ）：";
        std::getline(std::cin, raw_input);

        if(raw_input == "Y"){
            break;
        }
    }

    // create new save and export.
    SaveFile player_save(player_choice);
    save = player_save;

    MainCharacter player = save.getPlayer();
    FlagArray flags = save.getFlags();

    player.setName(playerName);

    save.update(1, player, flags);
    save.exportTo();

    std::cout << "＞＞存檔建立完成！" << std::endl;
    delay_ms(TEXT_DELAY);

    return true;
}

bool loadSave(SaveFile& save) {
    printSaveList();

    std::string raw_input = "";
    int player_choice = 0;
    while(true){
        // prompt and get player input.
        std::cout << "＞＞輸入存檔編號：";
        std::getline(std::cin, raw_input);

        // processing and validation.
        try{
            player_choice = stoi(raw_input);
            if(player_choice <= 0 || player_choice > 3){
                throw std::out_of_range("player_choice out of range");
            }
            break;
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
    }

    // import save.
    SaveFile player_save(player_choice);
    try{
        player_save.importFrom(player_choice);
    }catch(std::runtime_error& e){
        // if no save is found, return to main menu.
        std::cout << "＞＞該欄目無既有存檔！請通過「開始新游戲」選項建立新檔。" << std::endl;
        std::cout << "＞＞返回主選單。" << std::endl;
        delay_ms(TEXT_DELAY);
        return false;
    }

    // read save data.
    save = player_save;

    std::cout << "＞＞存檔讀取完成！" << std::endl;
    delay_ms(TEXT_DELAY);
    
    return true;
}

void printSaveList() {
    for(int i = 1; i <= 3; ++i){
        std::cout << "【存檔 " << i << " 】";

        // try to import save.
        SaveFile temp_save(i);
        try{
            temp_save.importFrom(i);
        }catch(std::runtime_error& e){
            std::cout << "無存檔記錄" << '\n'; // save not found..
            continue;
        }

        // save found.
        std::cout << temp_save.getPlayer().getName() << " 第" << temp_save.getDayCnt() << "天" << '\n';
    }
    return;
}

//每天開始的固定處理與輸出
void dayStart(int dayCnt){ 
    cout << "\n=====     第   " << dayCnt << "   天     =====\n\n";
}

//每天結束的固定處理與輸出
void dayEnd(int& dayCnt, MainCharacter player){
    cout << "\n=====     第   " << dayCnt << "   天     =====\n\n";
    cout << "\n=====     結 算 畫 面     =====\n\n";
    cout << "現在的各項數值\n";
    cout << "攻擊力：" << player.getATK() << '\n';
    cout << "防禦力：" << player.getDEF() << '\n';
    cout << "敏捷度：" << player.getSPD() << '\n';
    cout << "技巧值：" << player.getSKL() << '\n';
    cout << "幸運值：" << player.getLUK() << '\n';
    cout << "精力值上限：" << player.getSPLimit() << '\n';
    cout << "錢包餘額：" << player.getMNY() << '\n';
    cout << "你的隊友：" << player.listPartner() << '\n';
    dayCnt ++;
}

void choosePartner(SaveFile& save) {
    MainCharacter player = save.getPlayer();
    FlagArray flags = save.getFlags();

    std::vector<MainCharacter> partnerList;
    
    // perform checks for partner A
    bool partner1_recruited = true;

    if(partner1_recruited){
        partnerList.push_back(/*partner A*/);
    }

    // perform checks for partner B
    bool partner2_recruited = true;

    if(partner2_recruited){
        partnerList.push_back(/*partner B*/);
    }


    if(partnerList.size() == 0){
        return;
    }

    int player_choice = 0;
    while(true){
        std::cout << "＞＞請選擇你的隊友！\n";
        for(int i = 0; i < partnerList.size(); ++i){
            std::cout << "(" << i + 1 << ")" << partnerList[i].getName() << "\n";
        }

        // prompt and get player input.
        std::cout << "＞＞你的選擇：";
        std::string raw_input = "";
        std::getline(std::cin, raw_input);

        // verify input.
        try{
            player_choice = stoi(raw_input);
            if(player_choice <= 0 || player_choice > partnerList.size()){
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

        player.setPartner(partnerList[player_choice].getName());
        std::cout << "＞＞你選擇的隊友是" << player.listPartner() << "！請在比賽中一起好好加油吧～！\n";
    }

    // update save.
    save.update(save.getDayCnt(), player, flags);

    return;
}