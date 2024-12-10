#ifndef EVENTFUNCTION_H
#define EVENTFUNCTION_H

#include <string>
#include <chrono>
#include "flagArrayClass.h"
#include "MainCharacter.h"

const std::chrono::milliseconds TEXT_DELAY = std::chrono::milliseconds(500);
void delay_ms(std::chrono::milliseconds);

bool triggerEvent(std::string fileName, MainCharacter& player, FlagArray& flags);

#endif