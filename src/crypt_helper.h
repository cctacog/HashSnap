#ifndef CRYPT_HELPER
#define CRYPT_HELPER

#include "the_round.h"

/*
Sophia Garcia
01-31-2023
*/

//calculator functions
void secret_thru_queue(The_Round *terms);
void secret_thru_stack(The_Round *terms);
char possibleActions(enum Operator i, char c, char k);
char alphabet(int b);
char alphabet_print_listed(char alphabet[]);
char alphabet_print(char alphabet[], int letter);
#endif