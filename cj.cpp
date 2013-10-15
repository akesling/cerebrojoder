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

int main() {
    INSTRUCTION input;;
    while ((input = static_cast<INSTRUCTION>(getchar_unlocked())) != -1) {
        switch(input) {
            case LANGLE:
                putchar_unlocked(input);
                break;
            case RANGLE:
                putchar_unlocked(input);
                break;
            case INC:
                putchar_unlocked(input);
                break;
            case DEC:
                putchar_unlocked(input);
                break;
            case LBRACK:
                putchar_unlocked(input);
                break;
            case RBRACK:
                putchar_unlocked(input);
                break;
            case OUT:
                putchar_unlocked(input);
                break;
            case IN:
                putchar_unlocked(input);
                break;
            default:
                cout << "Invalid char: " << (int) input << "\n";
        }
    }
    return 0;
}
