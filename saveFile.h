#ifndef SAVEFILE_H
#define SAVEFILE_H

#include "flags.h"
#include "MainCharacter.h"

class SaveFile {
    private:
        int id;
        int dayCnt;
        MainCharacter player;
        FlagArray flags;
    public:
        SaveFile(int id); // create fresh save.

        int getID() const;
        int getDayCnt() const;
        MainCharacter getPlayer() const;
        FlagArray getFlags() const;

        void importFrom(int id); // import from existing txt file.
        void update(int dayCnt, MainCharacter player, FlagArray flags); // update save data.
        void exportTo(); // export save to txt file.

        void print(); // debug.
};

#endif