#include "Card.h"
#include <iostream>
#include <fstream>

void Card::addCard(std::string c, std::string b, std::string u, std::string d) {
    Card card;
    card.CardNumber = c;
    card.Build = b;
    card.Unit = u;
    card.Door = d;
    cards.push_back(card);
}

void Card::saveFile(std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "δ�ҵ��ɴ��ļ���" << std::endl;
        return;
    }
    for (const auto& card : cards) {
        file << card.CardNumber << "," << card.Build << "," << card.Unit << "," << card.Door << std::endl;
    }
    file.close();
}

void Card::loadFile(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "δ�ҵ��ɴ��ļ���" << std::endl;
        return;
    }

    cards.clear();

    std::string line;
    while (getline(file, line)) {
        Card card;
        size_t pos = 0;
        std::string box = line;
        std::vector<std::string> vor;
        while (pos != std::string::npos) {
            pos = box.find(',');
            vor.push_back(box.substr(0, pos));
            box = box.substr(pos + 1);
        }
        auto i = vor.begin();
        card.CardNumber = *i;
        card.Build = *(i + 1);
        card.Unit = *(i + 2);
        card.Door = *(i + 3);
        cards.push_back(card);
    }
    file.close();
}

void Card::printCard() {
    for (const auto& card : cards) {
        std::cout << "���ţ�" << card.CardNumber << " " << card.Build << "��" 
            << card.Unit << "��Ԫ" << " " << "���ƺţ�" << card.Door << std::endl;
    }
}

void Card::Run() {
    std::string filename = "cards.txt";
    loadFile(filename);

    while (true) {
        std::cout << "1.����¿�    2.��ѯ���п���Ϣ    0.�������˵�" << std::endl;
        int work;
        std::cin >> work;
        if (work == 1) {
            std::string cardnumber, build, unit, door;
            std::cout << "���뿨�ţ�"; std::cin >> cardnumber;
            std::cout << "���붰�ţ�"; std::cin >> build;
            std::cout << "���뵥Ԫ�ţ�"; std::cin >> unit;
            std::cout << "�������ƺţ�"; std::cin >> door;
            addCard(cardnumber, build, unit, door);
            saveFile(filename);
        }
        else if (work == 2) {
            std::string password;
            std::cout << "�������ѯ¥�����룺";
            std::cin >> password;
            if (password == "12345678") {
                printCard();
            }
        }
        else if (work == 0)
            return;
    }
}