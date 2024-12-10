
#ifndef BATTLESIMULATION_H
#define BATTLESIMULATION_H

#include <bits/stdc++.h>
#include "MainCharacter.h"
using namespace std;

void delay_ms(std::chrono::milliseconds);

//true player Win , false player Lose
bool battleSimulation(MainCharacter& player, MainCharacter& partner, MainCharacter& opponent1, MainCharacter& opponent2);

#endif
