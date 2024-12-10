
#ifndef BATTLESIMULATION_H
#define BATTLESIMULATION_H

#include <bits/stdc++.h>
#include "MainCharacter.h"
using namespace std;

const std::chrono::milliseconds TEXT_DELAY = std::chrono::milliseconds(800);
void delay_ms(std::chrono::milliseconds);

bool battleSimulation(MainCharacter& player, MainCharacter& partner, MainCharacter& opponent1, MainCharacter& opponent2);

#endif
