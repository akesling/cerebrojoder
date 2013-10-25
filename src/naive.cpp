#include <stdio.h>

static const int HEAPSIZE=30000;
static const int STACKSIZE=3000;
char DATA[HEAPSIZE] = {};
char CODE[HEAPSIZE] = {};
int JUMPS[HEAPSIZE] = {};

int STACK[STACKSIZE] = {};

int main() {
    int *stack_ptr = STACK;
    char input;
    for (int code_counter = 0;
         (input = getchar_unlocked()) != -1;) {
        switch(input) {
            case '<':
            case '>':
            case '+':
            case '-':
            case '.':
            case ',':
                CODE[code_counter] = input;
                ++code_counter;
                break;
            case '[':
                *stack_ptr = code_counter;
                ++stack_ptr;
                CODE[code_counter] = input;
                ++code_counter;
                break;
            case ']':
                --stack_ptr;
                JUMPS[*stack_ptr] = code_counter;
                JUMPS[code_counter] = *stack_ptr;
                CODE[code_counter] = input;
                ++code_counter;
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
                    code_ptr = (char*) (CODE + JUMPS[code_ptr-CODE]);
                }
                break;
            case ']':
                if (*data_ptr) {
                    code_ptr = (char*) (CODE + JUMPS[code_ptr-CODE]);
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
