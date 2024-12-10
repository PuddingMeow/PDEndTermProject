#include <bits/stdc++.h>
#include "MainCharacter.h"
#include "flagArrayClass.h"
#include "saveFileClass.h"
using namespace std;
/* what we should have
主要事項：
1. character/player object
2. main function(interface & daily progression)
3. event system
4. training system(可與event一起做？)
5. teammate recruiting(與event一起……？也跟flags有關)
6. match system

次要事項：
1. save system
2. items & inventory(?)
*/


/*所以我現在是這樣設計的
a file of character design (of course you can split it into many files)
some files about event designs (最後統整為一個檔案方便匯入)
some files about daily progression (同上)
a file about teammate recruiting(not now)
some files about match system.(not now)*/


//每天開始的固定處理與輸出
void dayStart(int dayCnt){ 
    cout << "第" << dayCnt << "天\n";
}

//每天結束的固定處理與輸出
void dayEnd(int& dayCnt, MainCharacter player){
    cout << "第" << dayCnt << "天\n";
    cout << "現在的各項數值\n";
    cout << "攻擊力：" << player.getATK() << '\n';
    cout << "防禦力：" << player.getDEF() << '\n';
    cout << "敏捷度：" << player.getSPD() << '\n';
    cout << "幸運值：" << player.getLUK() << '\n'; //感覺加了比較好玩
    cout << "精力值上限：" << player.getSPLimit() << '\n';
    cout << "錢包餘額：" << player.getMNY() << '\n';
    cout << "你的隊友：" << player.listPartner() << '\n';
    dayCnt ++;
}

void mainMenu(MainCharacter& player, FlagArray& flags);
bool createNewSave(MainCharacter& player, FlagArray& flags);
bool loadSave(MainCharacter& player, FlagArray& flags);
void printSaveList();

// output delay function
const std::chrono::milliseconds TEXT_DELAY = std::chrono::milliseconds(500);
void delay_ms(std::chrono::milliseconds);

int main(){
    int dayCnt = 1; //現在的天數
    int battleDay = 8; //數值隨便寫的，要比賽的日子
    int finalDay = 8; //數值我歲便寫的2，最後一天

    while(true){
        MainCharacter player;
        FlagArray flags;

        mainMenu(player, flags);

        /*while(dayCnt <= finalDay){
            if(dayCnt in battleDay){
                battleSimulation();//希望我們寫的到
            }else{
                daySimulation(); //包含event和dailyProgression //還有選項輸出等等
            }
            dayEnd(dayCnt, player);//執行結束處理
        }*/
    }

    return 0;
}

void mainMenu(MainCharacter& player, FlagArray& flags) {
    int player_choice = 0;
    while(true){
        std::cout << "\n\n===== 排球青年 =====\n\n";
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
            action_success = createNewSave(player, flags);
            break;
        case 2:
            action_success = loadSave(player, flags);
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

    // if action failed, return to main menu.
    if(action_success == false){
        mainMenu(player, flags);
    }

    return;
}

bool createNewSave(MainCharacter& player, FlagArray& flags){
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
            raw_input = player.getName();
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
    player = player_save.getPlayer();
    flags = player_save.getFlags();

    player.setName(playerName);

    player_save.update(1, player, flags);
    player_save.exportTo();

    std::cout << "＞＞存檔建立完成！" << std::endl;
    delay_ms(TEXT_DELAY);

    return true;
}

bool loadSave(MainCharacter& player, FlagArray& flags) {
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
    player = player_save.getPlayer();
    flags = player_save.getFlags();

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

void delay_ms(std::chrono::milliseconds ms){
	using namespace std::chrono;

	time_point<steady_clock> start = steady_clock::now();
	while(true){
		time_point<steady_clock> now = steady_clock::now();
		milliseconds duration = duration_cast<milliseconds>(now - start);
		if(duration >= ms){
			break;
		}
	}

	return;
}