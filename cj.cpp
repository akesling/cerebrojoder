#include <stdio.h>
#include <iostream>

using namespace std;

static const int HEAPSIZE=30000;
static const int STACKSIZE=3000;
char DATA[HEAPSIZE] = {};
char CODE[HEAPSIZE] = {};
char *JUMPS[HEAPSIZE] = {};

char *STACK[STACKSIZE] = {};

int main() {
    char **stack_ptr = STACK;
    char input;
    for (char *jumps_ptr = CODE;
         (input = getchar_unlocked()) != -1;) {
        switch(input) {
            case '<':
            case '>':
            case '+':
            case '-':
            case '.':
            case ',':
                *jumps_ptr = input;
                ++jumps_ptr;
                break;
            case '[':
                *stack_ptr = jumps_ptr;
                ++stack_ptr;
                *jumps_ptr = input;
                ++jumps_ptr;
                break;
            case ']':
                --stack_ptr;
                JUMPS[*stack_ptr - CODE] = jumps_ptr;
                JUMPS[jumps_ptr - CODE] = *stack_ptr;
                *jumps_ptr = input;
                ++jumps_ptr;
                break;
        }
    }

    for (char *code_ptr = CODE, *data_ptr = DATA;
         code_ptr < &CODE[HEAPSIZE];
         code_ptr++) {
        switch(*code_ptr) {
            case '<':
                --data_ptr;
                break;
            case '>':
                ++data_ptr;
                break;
            case '+':
                ++*data_ptr;
                break;
            case '-':
                --*data_ptr;
                break;
            case '[':
                if (!*data_ptr) {
                    code_ptr = JUMPS[code_ptr-CODE];
                }
                break;
            case ']':
                if (*data_ptr) {
                    code_ptr = JUMPS[code_ptr-CODE];
                }
                break;
            case '.':
                putchar_unlocked(*data_ptr);
                break;
            case ',':
                *data_ptr = getchar_unlocked();
                break;
        }
    }
    return 0;
}
