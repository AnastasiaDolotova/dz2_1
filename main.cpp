#include <conio.h>
#include "telephone.h"
#include "search_utils.h"

/* База данных коммерческого магазина содержит сведения о товарах (телефонах):
 * наименование и марка телефона, дата поступления, количество штук, установленная цена,
 * страна - производитель. Программа должна формировать бинарный файл типа «структура»,
 * добавлять и удалять данные, а также воспринимать каждый из перечисленных запросов и давать на него ответ.
 1. Определить, есть ли в магазине указанный товар производства данной страны.
 2. Определить, можно ли приобрести за данную сумму и, если да, то, сколько телефонных аппаратов каждой марки
 (выбрать все варианты по схеме "наименование и марка - максимально возможное количество").
 3. Определить на какую общую сумму поступили товары, начиная с указанной даты.
 Для обработки файла и выбора типа обработки использовать консольное меню.
*/

void printMenu() {
    std::cout << "Choose action: " << std::endl;
    std::cout << "1 - open/create file" << std::endl;
    std::cout << "2 - print file" << std::endl;
    std::cout << "3 - edit file" << std::endl;
    std::cout << "4 - find something" << std::endl;
    std::cout << "5 - exit" << std::endl;
}

FILE *open(char *name) {
    FILE *f = fopen(name, "rb");
    if (!f) {
        std::cout << "File was created" << std::endl;
    } else {
        std::cout << "File was opened" << std::endl;
    }
    f = fopen(name, "ab+");
    return f;
}

int main() {
    int key = 0;
    FILE *db;
    char name[20];
    while (key != 5) {
        system("cls");
        printMenu();
        std::cin >> key;
        switch (key) {
            case 1: {
                system("cls");
                std::cout << "Input name of file: ";
                std::cin >> name;
                db = open(name);
                getch();
                break;
            }
            case 2: {
                system("cls");
                printTelephones(db);
                getch();
                break;
            }
            case 3: {
                system("cls");
                std::cout << "Choose action:" << std::endl;
                std::cout << "1 - add telephone" << std::endl;
                std::cout << "2 - delete telephone" << std::endl;
                int k;
                std::cin >> k;
                switch (k) {
                    case 1: {
                        system("cls");
                        createTelephone(db);
                        std::cout << "Telephone was successfully added!" << std::endl;
                        printTelephones(db);
                        getch();
                        break;
                    }
                    case 2: {
                        system("cls");
                        db = deleteTelephone(db, name);
                        std::cout << "Telephone was successfully deleted!" << std::endl;
                        printTelephones(db);
                        getch();
                        break;
                    }
                }
                break;
            }
            case 4: {
                system("cls");
                std::cout << "Choose action:" << std::endl;
                std::cout << "1 - specified telephones produced in your country"
                          << std::endl;
                std::cout << "2 - how many telephones you can buy with your money" << std::endl;
                std::cout << "3 - total amount of telephones received, starting from the specified date"
                          << std::endl;
                int k;
                std::cin >> k;
                switch (k) {
                    case 1: {
                        system("cls");
                        isTelephone(db);
                        break;
                    }
                    case 2: {
                        system("cls");
                        howManyTelephones(db);
                        break;
                    }
                    case 3: {
                        system("cls");
                        howMuchFromDate(db);
                        break;
                    }
                }
                getch();
                break;
            }
            case 5: {
                fclose(db);
                break;
            }
        }
    }
    std::cout << "Press ENTER to close...";
    getch();
    return 0;
}
