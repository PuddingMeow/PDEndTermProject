#ifndef EVENTFUNCTION_H
#define EVENTFUNCTION_H

#include <string>
#include "flags.h"
#include "MainCharacter.h"

bool triggerEvent(std::string eventFileName, MainCharacter& player, FlagArray& flags);

#endif
