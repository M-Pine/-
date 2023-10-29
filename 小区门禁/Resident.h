#ifndef RESIDENT_H
#define RESIDENT_H

#include "Card.h"
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <map>

class Resident {
private:
    std::string CardNumber;
    std::string Build;
    std::string Unit;
    std::string Door;
    std::string Name;
    std::string password;
    std::string phoneNumber;
    std::map<std::string, std::string>passwordTocard;
    std::multimap<std::string, std::string>cardTodoor;

public:
    Resident() = default;
    std::vector<Resident>residents;
    void addResident(std::string n, std::string p, std::string c, std::string b, std::string u, std::string d, std::string pp);
    bool deleteResident(std::string n, std::string p);
    bool editResident(std::string n, std::string p);
    bool openDoor(std::string pp);
    std::vector<Resident> searchResident(std::string name);
    void saveFile(std::string filename);
    void mapFile(std::string filename);
    void loadFile(std::string filename);
    void LmapFile(std::string filename);
    void printResident();
    void Run();
    static void logDoorOpen(std::string cardNumber);
};
#endif