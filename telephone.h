#include <iostream>
#include <iomanip>

#ifndef DZ2_1_TELEPHONE_H
#define DZ2_1_TELEPHONE_H

struct telephone {
    char name[100], mark[100];
    int date[3], amount, price;
    char country[100];
};

void add(telephone *t, FILE *db);
void getDate(int *date);
void createTelephone(FILE *db);
void printDate(telephone *t);
void printTelephone(telephone &t);
void printTelephones(FILE *db);
void deleteTelephone(FILE *db, char *name);

#endif //DZ2_1_TELEPHONE_H
