#include "Card.h"
#include "Resident.h"
#include <iostream>

int main() {

    Card card;
    Resident resident;

    while (true)
    {
        std::cout << "1.Card����       2.Resident����       0.�˳�����" << std::endl;
        int choice;
        std::cin >> choice;
        if (choice == 1)
        {
            std::cout << "Card������\n";
            card.Run();
        }
        else if (choice == 2)
        {
            std::cout << "Resident������\n";
            resident.Run();
        }
        else if (choice == 0)
            break;
    }

    return 0;
}