#ifndef EVENTCLASS_H
#define EVENTCLASS_H

#include <string>
#include "FlagArrayClass.h"
#include "MainCharacter.h"

class Event {
    private:
        std::string fileName;

    public:
        Event(std::string fileName);

        bool trigger(MainCharacter& player, FlagArray& flags);
};

#endif