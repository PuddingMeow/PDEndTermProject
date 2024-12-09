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

        bool trigger(MainCharacter& player, FlagArray& flags);
};

<<<<<<< HEAD
#endif
=======
bool triggerEvent(std::string eventFileName, MainCharacter& player, FlagArray& flags);

#endif
>>>>>>> a517355067180e969342a96a1bf94bfd255cc5a1
