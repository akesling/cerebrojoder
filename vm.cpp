#include <iostream>
#include <stdio.h>
#include <utility>

using namespace std;

static const int HEAPSIZE=30000;
static const int CODESIZE=30000;
static const int STACKSIZE=3000;

unsigned char DATA[HEAPSIZE] = {};
unsigned char CODE[CODESIZE] = {};
int JUMPS[HEAPSIZE] = {};

int STACK[STACKSIZE] = {};

unsigned char parse_run(char character) {
/* This code makes a ton of assumptions... not all of them technically
 * valid BrainFuck... one such being that there can be a max run of 255
 * of the same symbol (for some symbols) in a row.
 */
    unsigned char number = 1;
    char next_char;
    while ((next_char = getchar_unlocked()) == character) {
        ++number;
    }
    ungetc(next_char, stdin);
    return number;
}

void parse_and_compile() {
    int *stack_ptr = STACK;
    char input;
    for (int code_counter = 0; (input = getchar_unlocked()) != -1;) {
        switch(input) {
            case '<':
            case '>':
            case '+':
            case '-':
                CODE[code_counter] = input;
                ++code_counter;
                CODE[code_counter] = parse_run(input);
                ++code_counter;
                break;
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
}

void run() {
    for (unsigned char *code_ptr = CODE, *data_ptr = DATA;
         code_ptr < &CODE[CODESIZE];
         code_ptr++) {
        switch(*code_ptr) {
            case '<':
                ++code_ptr;
                data_ptr -= *code_ptr;
                break;
            case '>':
                ++code_ptr;
                data_ptr += *code_ptr;
                break;
            case '+':
                ++code_ptr;
                *data_ptr += *code_ptr;
                break;
            case '-':
                ++code_ptr;
                *data_ptr -= *code_ptr;
                break;
            case '[':
                if (!*data_ptr) {
                    code_ptr =
                        (unsigned char*) (CODE + JUMPS[code_ptr-CODE]);
                }
                break;
            case ']':
                if (*data_ptr) {
                    code_ptr =
                        (unsigned char*) (CODE + JUMPS[code_ptr-CODE]);
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
}

int main() {
    parse_and_compile();
    /*
    for (auto& c : CODE) {
        if (c > 0 ) {
            cout << c;
        }
    }
    */
    run();
    return 0;
}
