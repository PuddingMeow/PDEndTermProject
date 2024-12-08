#include "MainCharacter.h"

class NpcCharacter : public MainCharacter
{
private:

public:
    NpcCharacter() : MainCharacter()
    {
    }
    NpcCharacter(const NpcCharacter& another) : MainCharacter(another)
    {
    }
};
