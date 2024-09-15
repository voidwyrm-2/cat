#include <stdio.h>
#include <stdlib.h>

#include "include/nucl.h"

#define INSTRUCTION_SIZE 8

/*
int* bytesToInts(char* bytes, int length) {
    if (length % 2 != 0) {
        return NULL;
    }
    int* out = malloc((int)(length / 2));
    int o = 0;
    for (int i = 0; i < length; i += 2) {
        out[o] = (bytes[i] << 8) + bytes[i + 1];
        o++;
    }
    return out;
}
*/

int concatb(const int* code, const int pos, int amount) {
    int out = 0;
    int shift = 8 * amount;
    for (int i = pos; amount != 0; i++) {
        out = code[i] << shift;
        amount--;
    }
    return out;
}

void setRegister(int** registers, const int regcode, const int value) {
    if (regcode != 0) {
        *registers[regcode] = value;
    }
}

void exitCAT(char* code, Arraylist* callStack, Arraylist* stack,
             int* registers) {
    free(registers);
    FreeArraylist(callStack);
    FreeArraylist(stack);
    exit(code);
}

void cpu(char* code) {
    Arraylist callStack = NewArraylist(1);
    Arraylist stack = NewArraylist(1);

    int* registers = malloc(sizeof(int) * 64);

    int pc = 0;
    while (1) {
        switch (concatb(code, pc, 2)) {
            // nop, ecall, call, ret
            case 0:
                break;
            case 1:
                switch (registers[1]) {
                    case 0:
                        exitCAT(registers[3], &callStack, &stack, registers);
                        break;
                    case 2: {
                        char* str = malloc(registers[4]);
                        for (int i = 0; i < registers[4]; i++) {
                            str[i] = code[registers[3] + i];
                        }
                        printf(str);
                        free(str);
                    } break;
                    case 3:
                        printf("interrupt: unknown system call code '%d'\n",
                               registers[1]);
                }
                break;
            case 2: {
                int* old_pc = malloc(sizeof(int));
                *old_pc = pc;
                ALAdd(&callStack, (void*)&old_pc);
                pc = concatb(code, pc + 2, 2);
            } break;
            case 3: {
                if (callStack.len == 0) {
                    printf("interrupt: returned while callstack empty\n");
                    exitCAT(1, &callStack, &stack, registers);
                }
                int* new_pc = (int*)ALRemove(&callStack);
                pc = *new_pc;
                free(new_pc);
            } break;

                // load, store, adr
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;

            default:
                printf("interrupt: unknown opcode '%d'\n", code[pc]);
                exitCAT(1, &callStack, &stack, registers);
        }
        pc += INSTRUCTION_SIZE;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("expected 'catcpu [file]'");
        return 1;
    }

    char* bytes = Readfile(argv[1]);
    if (bytes == NULL) {
        printf("could not get file contents\n");
        return 1;
    }

    cpu(bytes);

    return 0;
}