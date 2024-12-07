#ifndef SAVEFILE_H
#define SAVEFILE_H

#include "flags.h"

class SaveFile {
    private:
        int id;
        int dayCnt;
//      MainCharacter player;
        FlagArray flags;
    public:
        SaveFile(int id, bool tempDistinguisher/*, MainCharacter player*/); // create fresh save.

        void importFrom(int id); // import from existing txt file.
        void update(int dayCnt/*, MainCharacter player*/, FlagArray flags); // update save data.
        void exportTo(); // export save to txt file.

        void print() const; // debug.
};

#endif