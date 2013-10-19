#include <algorithm>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <utility>
#include <vector>

using namespace std;

struct stencil_type {
    int offset;
    int move;
    vector<short> cells;
};

static const int HEAPSIZE=30000;
static const int CODESIZE=30000;
static const int STACKSIZE=3000;
static const int MAXCHAR=255;
static const unsigned char STENCIL_INSTRUCTION = 'O';

static unsigned char DATA[HEAPSIZE] = {};
static unsigned char CODE[CODESIZE] = {};
static int JUMPS[CODESIZE] = {};
static stencil_type STENCILS[CODESIZE] = {};

static int STACK[STACKSIZE] = {};

stencil_type build_stencil() {
    stencil_type stencil;
    stencil.cells.push_back(0);
    int cursor = 0;
    int left_offset = 0;

    char next_char;
    while ((next_char = getchar_unlocked()) != EOF) {
        switch(next_char) {
            case '<':
                if (cursor > 0) {
                    --cursor;
                } else {
                    stencil.cells.insert(stencil.cells.begin(), 0);
                    ++left_offset;
                }
                break;
            case '>':
                ++cursor;
                if (cursor >= (int) (stencil.cells.size())) {
                    stencil.cells.push_back(0);
                }
                break;
            case '+':
                ++stencil.cells[cursor];
                break;
            case '-':
                --stencil.cells[cursor];
                break;
            case '[':
            case ']':
            case '.':
            case ',':
                goto exit_loop;
                break;
        }
    }
    exit_loop:
    stencil.move = cursor - left_offset;
    stencil.offset = left_offset;

    ungetc(next_char, stdin);

    return stencil;
}

unsigned char parse_run(char character) {
    unsigned char number = 1;
    char next_char;
    while ((next_char = getchar_unlocked()) == character &&
           number < 255) {
        ++number;
    }
    ungetc(next_char, stdin);
    return number;
}

void parse_and_compile() {
    int *stack_ptr = STACK;
    char input;

    for (int code_counter = 0; (input = getchar_unlocked()) != EOF;) {
        switch(input) {
            case '<':
            case '>':
            case '+':
            case '-':
                ungetc(input, stdin);
                CODE[code_counter] = STENCIL_INSTRUCTION;
                STENCILS[code_counter] = build_stencil();
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
    unsigned char *tmp_data_ptr;
    unsigned char *data_ptr = DATA;
    stencil_type *stencil;
    for (unsigned char *code_ptr = CODE;
         code_ptr < &CODE[CODESIZE];
         code_ptr++) {
        switch(*code_ptr) {
            case STENCIL_INSTRUCTION:
                stencil = &STENCILS[code_ptr-CODE];
                tmp_data_ptr = data_ptr - stencil->offset;
                data_ptr += stencil->move;

                for (unsigned int i= 0; i < stencil->cells.size(); ++i) {
                    *tmp_data_ptr = (unsigned char) *tmp_data_ptr +
                        stencil->cells[i];
                    ++tmp_data_ptr;
                }
                break;
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

void print_code() {
    vector<unsigned char> instructions = {
        '<', '>', '+', '-', ',',
        '.', '[', ']', STENCIL_INSTRUCTION
        };
    for (auto& c : CODE) {
        if (c > 0) {
            if (find(instructions.begin(), instructions.end(), c) !=
                instructions.end()) {
                cout << c;
            } else {
                cout << (int) c;
            }
        }
    }
    cout << "\n";
}

void print_vec(const std::vector<short>& vec)
{
    for (auto x: vec) {
         cout << ' ' << x;
    }
    cout << '\n';
}


int main() {
    parse_and_compile();
    //print_code();
    run();
    return 0;
}
