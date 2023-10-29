#pragma once
#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

class Card {
public:
    std::string CardNumber;
    std::string Build;
    std::string Unit;
    std::string Door;

    /// <summary>
    /// ´æ·Åcards
    /// </summary>
    std::vector<Card>cards;

    Card() = default;
    void addCard(std::string c, std::string b, std::string u, std::string d);
    void saveFile(std::string filename);
    void loadFile(std::string filename);
    void printCard();
    void Run();
};

#endif