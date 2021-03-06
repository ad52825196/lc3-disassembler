#include <stdio.h>
#include <stdbool.h>

void printAddAnd(int*);
int binToDec(int*, int, int, bool);

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    int input, pc = 0, i, ins[12];
    char opcode;

    if (argc > 2) {
        sscanf(argv[2], "%x", &pc);
    }

    // process each line
    while (fscanf(file, "%c%x\n", &opcode, &input) != EOF) {
        // decimal to binary
        i = 12;
        while (i > 0) {
            ins[--i] = input & 1;
            input /= 2;
        }

        // increment program counter
        pc++;

        switch (opcode) {
            case '0':
                fputs("br", stdout);
                if (ins[0]) {
                    putchar('n');
                }
                if (ins[1]) {
                    putchar('z');
                }
                if (ins[2]) {
                    putchar('p');
                }
                putchar(' ');
                printf("%#x", pc + binToDec(ins, 3, 9, true));
                break;
            case '1':
                fputs("add ", stdout);
                printAddAnd(ins);
                break;
            case '5':
                fputs("and ", stdout);
                printAddAnd(ins);
                break;
            case 'c':
                fputs("jmp ", stdout);
                printf("%c%d", 'r', binToDec(ins, 3, 3, false));
                break;
            default:
                fputs("Invalid instruction", stdout);
                break;
        }

        printf("\n");
    }
    fclose(file);

    return 0;
}

void printAddAnd(int *ins) {
    printf("%c%d", 'r', binToDec(ins, 0, 3, false));
    putchar(',');
    printf("%c%d", 'r', binToDec(ins, 3, 3, false));
    putchar(',');
    if (ins[6]) {
        printf("%d", binToDec(ins, 7, 5, true));
    } else {
        printf("%c%d", 'r', binToDec(ins, 9, 3, false));
    }
}

int binToDec(int *a, int start, int length, bool isSigned) {
    int base = 1, res = 0, i;

    for (i = start + length - 1; i > start; i--) {
        res += a[i] * base;
        base *= 2;
    }
    if (isSigned) {
        res -= a[i] * base;
    } else {
        res += a[i] * base;
    }

    return res;
}
