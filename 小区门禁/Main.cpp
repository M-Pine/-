#include "Card.h"
#include "Resident.h"
#include <iostream>

int main() {

    Card card;
    Resident resident;

    while (true)
    {
        std::cout << "1.Card操作       2.Resident操作       0.退出程序" << std::endl;
        int choice;
        std::cin >> choice;
        if (choice == 1)
        {
            std::cout << "Card操作：\n";
            card.Run();
        }
        else if (choice == 2)
        {
            std::cout << "Resident操作：\n";
            resident.Run();
        }
        else if (choice == 0)
            break;
    }

    return 0;
}