#define _CRT_SECURE_NO_WARNINGS

#include "Resident.h"
#include <iostream>
#include <fstream>

void Resident::addResident(std::string n, std::string p, std::string c, std::string b, std::string u, std::string d, std::string pp) {
    Resident resident;
    resident.CardNumber = c;
    resident.Build = b;
    resident.Unit = u;
    resident.Door = d;
    resident.Name = n;
    resident.phoneNumber = p;
    resident.password = pp;
    passwordTocard[pp] = c;
    cardTodoor.insert(make_pair(c, b));
    cardTodoor.insert(make_pair(c, u));
    cardTodoor.insert(make_pair(c, d));
    cardTodoor.insert(make_pair(c, n));
    residents.push_back(resident);
}

bool Resident::deleteResident(std::string n, std::string p) {
    for (auto i = residents.begin(); i != residents.end(); i++) {
        if (i->Name == n && i->phoneNumber == p) {
            residents.erase(i);
            return true;
        }
    }
    return false;
}

bool Resident::editResident(std::string n, std::string p) {
    std::cout << "��������µĵ绰���룺";
    std::string newp;
    std::cin >> newp;
    for (auto& resident : residents) {
        if (resident.Name == n && resident.phoneNumber == p) {
            resident.phoneNumber = newp;
            return true;
        }
    }
    return false;
}

std::vector<Resident> Resident::searchResident(std::string name) {
    std::vector<Resident> result;
    for (auto& resident : residents) {
        if (resident.Name.find(name) != std::string::npos) {
            result.push_back(resident);
        }
    }
    return result;
}

bool Resident::openDoor(std::string pp) {
    auto it = passwordTocard.find(pp);
    if (it != passwordTocard.end()) {
        std::string cardNumber = it->second;
        auto doorIt = cardTodoor.find(cardNumber);
        auto count = cardTodoor.count(cardNumber);
        if (doorIt != cardTodoor.end())
        {
            for (auto flag = 0; flag < count; flag++, doorIt++)
            {
                if (flag == 2)
                {
                    std::cout << doorIt->second << "���Ѵ򿪡�" << std::endl;
                    auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                    char time[100];
                    std::strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTime));
                    std::ofstream logfile("times.txt", std::ios::app);
                    if (logfile.is_open())
                    {
                        logfile << cardNumber << "<->" << time << std::endl;
                    }
                    logfile.close();
                }                    
            }
            return true;
        }
        else
            std::cout << "��Ч����" << std::endl;
    }
    else {
        std::cout << "������������ԡ�" << std::endl;
    }
    return false;
}

void Resident::logDoorOpen(std::string cardNumber)      //��ӡ����ʱ��
{
    std::ifstream logfile("times.txt");
    if (!logfile.is_open())
    {
        std::cerr << "δ�ҵ��ɴ��ļ���" << std::endl;
        return;
    }
    std::map<std::string, std::string>Time;
    std::string _cardNumber, _time;
    std::string line;
    while (getline(logfile, line))
    {
        size_t commaPos = line.find("<->");
        if (commaPos != std::string::npos)
        {
            _cardNumber = line.substr(0, commaPos);
            _time = line.substr(commaPos + 3);
            Time[_cardNumber] = _time;
        }
    }
    logfile.close();
    auto it = Time.find(_cardNumber);
    if (it != Time.end())
    {
        if (it->first == cardNumber)
            std::cout << it->first << "��" << it->second << "���š�" << std::endl;
    }
}

void Resident::saveFile(std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "δ�ҵ��ɴ��ļ���" << std::endl;
        return;
    }
    for (const auto& resident : residents) {
        file << resident.CardNumber << "," << resident.Build << "," << resident.Unit << "," << resident.Door << ","
            << resident.Name << "," << resident.phoneNumber << "," << resident.password << std::endl;
    }
    file.close();
}

void Resident::mapFile(std::string filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "δ�ҵ��ɴ��ļ���" << std::endl;
        return;
    }
    for (const auto& pair : passwordTocard)
    {
        file << "passwordTocard:" << pair.first << "->" << pair.second << std::endl;
    }
    for (const auto& pair : cardTodoor)
    {
        file << "cardTodoor:" << pair.first << "->" << pair.second << std::endl;
    }
    file.close();
}

void Resident::loadFile(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "δ�ҵ��ɴ��ļ���" << std::endl;
        return;
    }

    residents.clear();

    std::string line;
    while (getline(file, line)) {
        Resident resident;
        size_t pos = 0;
        std::string box = line;
        std::vector<std::string> vor;
        while (pos != std::string::npos) {
            pos = box.find(',');
            vor.push_back(box.substr(0, pos));
            box = box.substr(pos + 1);
        }
        auto i = vor.begin();
        resident.CardNumber = *i;
        resident.Build = *(i + 1);
        resident.Unit = *(i + 2);
        resident.Door = *(i + 3);
        resident.Name = *(i + 4);
        resident.phoneNumber = *(i + 5);
        resident.password = *(i + 6);
        residents.push_back(resident);
    }
    file.close();
}

void Resident::LmapFile(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "δ�ҵ��ɴ��ļ���" << std::endl;
        return;
    }

    passwordTocard.clear();
    cardTodoor.clear();

    std::string key, value;
    std::string line;
    while (getline(file, line))
    {
        if (line.find("passwordTocard:") != std::string::npos)
        {
            line = line.substr(line.find(":") + 1);
            {
                size_t commaPos = line.find("->");
                if (commaPos != std::string::npos)
                {
                    key = line.substr(0, commaPos);
                    value = line.substr(commaPos + 2);
                    passwordTocard[key] = value;
                }
            }
        }
        else if (line.find("cardTodoor:") != std::string::npos)
        {
            line = line.substr(line.find(":") + 1);
            {
                size_t commaPos = line.find("->");
                if (commaPos != std::string::npos)
                {
                    key = line.substr(0, commaPos);
                    value = line.substr(commaPos + 2);
                    cardTodoor.insert(make_pair(key, value));
                }
            }
        }
    }
    file.close();
}

void Resident::printResident() {
    for (const auto& resident : residents) {
        std::cout << "���ţ�" << resident.CardNumber << " " << resident.Build << "��"
            << resident.Unit << "��Ԫ" << " " << "���ƺţ�" << resident.Door << " " << "������"
            << resident.Name << " " << "�绰���룺" << resident.phoneNumber << std::endl;
    }
}

void Resident::Run() {
    std::string filename = "residents.txt";
    std::string Filename = "relations.txt";
    loadFile(filename);
    LmapFile(Filename);

    while (true) {
        std::cout << "1.��Ӿ�����Ϣ     2.��ѯ������Ϣ" << std::endl;
        std::cout << "3.���¾�����Ϣ     4.ɾ��������Ϣ" << std::endl;
        std::cout << "5.���о�����Ϣ     6.���������Ϣ" << std::endl;
        std::cout << "7.����            8.��ʾ������ʱ��" << std::endl;
        std::cout << "        0.�������˵�            " << std::endl;
        int work;
        std::cin >> work;
        if (work == 1) {
            std::string cardnumber, build, unit, door, name, phonenumber, password;
            std::cout << "���뿨�ţ�"; std::cin >> cardnumber;
            std::cout << "���붰�ţ�"; std::cin >> build;
            std::cout << "���뵥Ԫ�ţ�"; std::cin >> unit;
            std::cout << "�������ƺţ�"; std::cin >> door;
            std::cout << "����������"; std::cin >> name;
            std::cout << "����绰���룺"; std::cin >> phonenumber;
            std::cout << "���ÿ������룺"; std::cin >> password;
            addResident(name, phonenumber, cardnumber, build, unit, door, password);
        }
        else if (work == 2) {
            std::string name;
            std::cout << "�������������"; std::cin >> name;
            std::vector<Resident> result = searchResident(name);
            if (!result.empty()) {
                std::cout << "��ѯ�����" << std::endl;
                for (const auto& resident : result) {
                    std::cout << "���ţ�" << resident.CardNumber << " " << resident.Build << "��"
                        << resident.Unit << "��Ԫ" << " " << "���ƺţ�" << resident.Door << " " << "������"
                        << resident.Name << " " << "�绰���룺" << resident.phoneNumber << std::endl;
                }
            }
            else {
                std::cout << "δ�������þ�����Ϣ��" << std::endl;
            }
        }
        else if (work == 3) {
            std::string name, phonenumber;
            std::cout << "�������������"; std::cin >> name;
            std::cout << "�������绰���룺"; std::cin >> phonenumber;
            if (editResident(name, phonenumber)) {
                saveFile(filename);
                std::cout << "������Ϣ�Ѹ��¡�" << std::endl;
            }
            else {
                std::cout << "����ʧ�ܡ�" << std::endl;
            }
        }
        else if (work == 4) {
            std::string name, phonenumber;
            std::cout << "�������������"; std::cin >> name;
            std::cout << "�������绰���룺"; std::cin >> phonenumber;
            if (deleteResident(name, phonenumber)) {
                saveFile(filename);
                std::cout << "������Ϣ��ɾ����" << std::endl;
            }
            else {
                std::cout << "ɾ��ʧ�ܡ�" << std::endl;
            }
        }
        else if (work == 5) {
            std::string password;
            std::cout << "�������ѯ������Ϣ���룺";
            std::cin >> password;
            if (password == "12345678") {
                printResident();
            }
        }
        else if (work == 6) {
            saveFile(filename);
            mapFile(Filename);
        }
        else if (work == 7) {
            std::cout << "�����뿪�����룺";
            std::string password;
            std::cin >> password;
            openDoor(password);
        }
        else if (work == 8) {
            std::cout << "������Ҫ��ѯ�Ŀ��ţ�";
            std::string cardnumber;
            std::cin >> cardnumber;
            logDoorOpen(cardnumber);
            std::cout << "�Ƿ���ʾ������Ϣ��Yes or No..." << std::endl;
            std::string OR;
            std::cin >> OR;
            if (OR == "Yes")
            {
                auto doorIt = cardTodoor.find(cardnumber);
                auto count = cardTodoor.count(cardnumber);
                if (doorIt != cardTodoor.end())
                {
                    for (auto flag = 0; flag < count; flag++, doorIt++)
                    {
                        if (flag == 0) std::cout << doorIt->second << "��" << " ";
                        else if (flag == 1) std::cout << doorIt->second << "��Ԫ" << " ";
                        else if (flag == 2) std::cout << "���ƺţ�" << doorIt->second << " ";
                        else if (flag == 3) std::cout << "������" << doorIt->second;
                    }
                }
            }
            std::cout << std::endl;
        }
        else if (work == 0)
            return;
    }
}