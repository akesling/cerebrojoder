#include <stdio.h>
#include <iostream>

using namespace std;

enum INSTRUCTION {
    INC = 43, IN, DEC, OUT,
    LANGLE = 60,
    RANGLE = 62,
    LBRACK = 91,
    RBRACK = 93,
};

char DATA[60000] = {};

int main() {
    char *ptr = &DATA[30000];
    INSTRUCTION input;
    while ((input = static_cast<INSTRUCTION>(getchar_unlocked())) != -1) {
        switch(input) {
            case LANGLE:
                --ptr;
                break;
            case RANGLE:
                ++ptr;
                break;
            case INC:
                ++*ptr;
                break;
            case DEC:
                --*ptr;
                break;
            case LBRACK:
                putchar_unlocked(input);
                break;
            case RBRACK:
                putchar_unlocked(input);
                break;
            case OUT:
                putchar_unlocked(*ptr);
                break;
            case IN:
                *ptr = getchar_unlocked();
                break;
        }
    }
    return 0;
}
