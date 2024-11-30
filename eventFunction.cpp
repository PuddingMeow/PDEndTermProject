#include "eventFunction.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <windows.h> 

// Should take MainCharacter as argument as well.
// It should update relevant variables through get/increment functions.
// I'll add it in once its ready.
bool triggerEvent(std::string eventFileName);

int main() {
	try{
		triggerEvent("event1.txt");
		triggerEvent("event2.txt");
		triggerEvent("event3.txt");
	}
	catch(std::invalid_argument e){
		std::cout << e.what();
	}
	return 0;
}

bool triggerEvent(std::string eventFileName){
	std::string path = "events/";
	path += eventFileName;
	
	std::ifstream event(path);
	
	if(!event.is_open()){
		throw std::invalid_argument("File name does not exist.");
	}
	
	std::string title = "";
	std::getline(event, title);
	std::cout << title << "\n";
	Sleep(500);
	
	while(event.eof() == false){
		std::string name = "";
		std::string text = "";
		std::getline(event, name);
		std::getline(event, text);
		
		if(name == "mc"){
			std::cout << "你："; 
		}else if(name != "n"){
			std::cout << name << "：";
		}
		std::cout << text << "\n";
		Sleep(1000);
	}
	
	event.close();
	return true;
}
