#include <fstream>
#include <string>

class SaveFile {
    private:
        int id;
        int dayCnt;
//      MainCharacter player;
//      FlagArray flags;
    public:
        SaveFile(int id/*, MainCharacter player*/);
        SaveFile(std::string fileName);

        void updateSave(int dayCnt/*, MainCharacter player, FlagArray flags*/);
        void exportSave();
};

SaveFile::SaveFile(int id) : id(id), dayCnt(1)/*, MainCharacter(player)*/
{
}

SaveFile::SaveFile(std::string fileName){
    std::string path = "saves/" + fileName;
    std::ifstream save(path);
    /*import save*/
    save.close();
}

void SaveFile::updateSave(int dayCnt/*, MainCharacter player, FlagArray flags*/){
    this->dayCnt = dayCnt;
//  this->player = player;
//  this->flags = flags;
    return;
}

void SaveFile::exportSave(){
    std::string path =  "saves/save" + std::to_string(id);
    std::ofstream save(path);
    /*export save*/
    save.close();
    return;
}