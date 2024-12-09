#ifndef EVENTFUNCTION_H
#define EVENTFUNCTION_H

#include <string>
#include "flagArrayClass.h"
#include "MainCharacter.h"

bool triggerEvent(std::string fileName, MainCharacter& player, FlagArray& flags);

#endif