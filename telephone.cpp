#include "telephone.h"

void add(telephone *t, FILE *db) {
    fseek(db, 0, SEEK_END);
    fwrite(t, 1, sizeof(telephone), db);
}

void getDate(int *date) {
    for (int i = 0; i < 3; ++i) {
        std::cin >> *(date + i);
        std::cin.ignore();
    }
}

void createTelephone(FILE *db) {
    telephone *t = new telephone;
    std::cout << "Input name: ";
    std::cin >> t->name;
    std::cout << std::endl << "Input mark: ";
    std::cin >> t->mark;
    std::cout << std::endl << "Input date (DD.MM.YYYY): ";
    getDate(t->date);
    std::cout << std::endl << "Input amount: ";
    std::cin >> t->amount;
    std::cout << std::endl << "Input price: ";
    std::cin >> t->price;
    std::cout << std::endl << "Input country: ";
    std::cin >> t->country;
    add(t, db);
    delete t;
}

void printDate(telephone *t) {
    std::cout << "  " << t->date[0] << "." << t->date[1] << "." << t->date[2];
}

void printTelephone(telephone &t) {
    std::cout << std::setw(10) << t.name << " |" <<
              std::setw(10) << t.mark << " |";
    printDate(&t);
    std::cout << " |" << std::setw(10) << t.amount << " |" << std::setw(10)
              << t.price << " |" << std::setw(13) << t.country << " |" << std::endl;
}

void printTelephones(FILE *db) {
    std::cout << "The file:" << std::endl;
    rewind(db);
    telephone t;
    std::cout << std::setw(6) << "Num |" << std::setw(12) << "Name |" <<
              std::setw(12) << "Mark |" << std::setw(14) << "Date |" << std::setw(12) <<
              "Amount |" << std::setw(12) << "Price |" << std::setw(15) << "Country |" << std::endl;
    int i = 1;
    while (fread(&t, sizeof(telephone), 1, db) > 0) {
        std::cout << "-----------------------------------------------------------------------------" << std::endl;
        std::cout << std::setw(4) << i << " |";
        printTelephone(t);
        ++i;
    }
    std::cout << "-----------------------------------------------------------------------------" << std::endl;
}

//TODO: не работает
void deleteTelephone(FILE *db, char *name) {
    rewind(db);
    std::cout << "Input index: ";
    int n, k = 1;
    std::cin >> n;
    std::cout << std::endl;
    telephone t;
    rewind(db);
    FILE *tmp;
    tmp = fopen("tmpf", "wb");
    while (fread(&t, sizeof(telephone), 1, db) > 0) {
        k++;
        if (k != n)
            fwrite(&t, sizeof(telephone), 1, tmp);
    }
    fclose(tmp);
    fclose(db);
    unlink(name);
    rename("tmpf", name);
    db = fopen(name, "a+b");
    rewind(db);
}