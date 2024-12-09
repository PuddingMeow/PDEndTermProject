#ifndef EVENTCLASS_H
#define EVENTCLASS_H

#include <string>
#include "flagArrayClass.h"
#include "MainCharacter.h"

class Event {
    private:
        std::string fileName;

    public:
        Event(std::string fileName);

        
};

bool triggerEvent(std::string eventFileName, MainCharacter& player, FlagArray& flags);

#endif
