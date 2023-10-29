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
        std::cerr << "未找到可打开文件。" << std::endl;
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
        std::cerr << "未找到可打开文件。" << std::endl;
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
        std::cout << "卡号：" << card.CardNumber << " " << card.Build << "栋" 
            << card.Unit << "单元" << " " << "门牌号：" << card.Door << std::endl;
    }
}

void Card::Run() {
    std::string filename = "cards.txt";
    loadFile(filename);

    while (true) {
        std::cout << "1.添加新卡    2.查询所有卡信息    0.返回主菜单" << std::endl;
        int work;
        std::cin >> work;
        if (work == 1) {
            std::string cardnumber, build, unit, door;
            std::cout << "输入卡号："; std::cin >> cardnumber;
            std::cout << "输入栋号："; std::cin >> build;
            std::cout << "输入单元号："; std::cin >> unit;
            std::cout << "输入门牌号："; std::cin >> door;
            addCard(cardnumber, build, unit, door);
            saveFile(filename);
        }
        else if (work == 2) {
            std::string password;
            std::cout << "请输入查询楼盘密码：";
            std::cin >> password;
            if (password == "12345678") {
                printCard();
            }
        }
        else if (work == 0)
            return;
    }
}