#include "search_utils.h"
#include <string.h>

//Определить, есть ли в магазине указанный товар производства данной страны.
void isTelephone(FILE *db) {
    char name[20], country[20];
    std::cout << "Input name of the phone: ";
    std::cin >> name;
    std::cout << std::endl << "Input country: ";
    std::cin >> country;
    std::cout << std::endl;
    rewind(db);
    telephone t;
    std::cout << "Telephones " << name << " in " << country << ":" << std::endl;
    int f = 0;
    while (fread(&t, 1, sizeof(telephone), db) > 0) {
        if (strcmp(name, t.name) == 0) {
            if (strcmp(country, t.country) == 0) {
                printTelephone(t);
                f = 1;
            }
        }
    }
    if (!f) {
        std::cout << "There is no such telephones!" << std::endl;
    }
}

//Определить, можно ли приобрести за данную сумму и, если да, то, сколько телефонных аппаратов каждой марки
//(выбрать все варианты по схеме "наименование и марка - максимально возможное количество").
void howManyTelephones(FILE *db) {
    std::cout << "Input the amount: ";
    int amount;
    std::cin >> amount;
    std::cout << std::endl;
    telephone t;
    std::cout << "Telephones that you can buy:" << std::endl;
    int f = 0;
    rewind(db);
    while (fread(&t, 1, sizeof(telephone), db) > 0) {
        if (t.price < amount) {
            int s = amount / t.price;
            std::cout << t.name << " " << t.mark << ": " << s << " telephones" << std::endl;
            f = 1;
        }
    }
    if (!f) {
        std::cout << "There is no such telephones!" << std::endl;
    }
}

//Определить на какую общую сумму поступили товары, начиная с указанной даты.
void howMuchFromDate(FILE *db) {
    std::cout << "Input year: ";
    int year, sum = 0;
    std::cin >> year;
    std::cout << std::endl;
    rewind(db);
    telephone t;
    std::cout << "Telephones that were received since " << year << ":" << std::endl << std::endl;
    while (fread(&t, 1, sizeof(telephone), db) > 0) {
        if (t.date[2] >= year) {
            sum += t.price * t.amount;
            std::cout << t.name << " " << t.mark << ", year: " << t.date[2] << ", price: " << t.price << ", amount: "
                      << t.amount << std::endl;
        }
    }
    if (sum > 0) {
        std::cout << std::endl << "Total sum = " << sum << std::endl;
    } else {
        std::cout << "There is no such telephones!" << std::endl;
    }
}