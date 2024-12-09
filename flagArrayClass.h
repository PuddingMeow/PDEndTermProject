#ifndef FLAGARRAYCLASS_H
#define FLAGARRAYCLASS_H

#include <string>
#include <stdexcept>

class file_error : public std::runtime_error {
    private:
    public:
        file_error(std::string msg) : runtime_error(msg) {};
};

struct Flag {
    std::string name;
    bool status;
};


// All FlagArrays are initialised with init_config/flagList.txt.
// Use member functions to verify/update specific flags.
class FlagArray{
    private:
        Flag* flag;
        int flagCnt;

        Flag* linearSearch(std::string flagName) const;
    public:
        FlagArray();
        FlagArray(const FlagArray&);
        ~FlagArray();

        const FlagArray& operator=(const FlagArray&);
        Flag& operator[](int index);

        int getFlagCnt() const;
        bool checkFlagStatus(std::string flagName) const;
        void updateFlagStatus(std::string flagName, bool status);
        void print() const; // debug.
};

#endif