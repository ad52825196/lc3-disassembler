#include <stdio.h>

void printAddAnd(int*);
int binToDec(int*, int, int);

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    int input, i, ins[12];
    char opcode;

    // process each line
    while (fscanf(file, "%c%x\n", &opcode, &input) != EOF) {
        // decimal to binary
        i = 12;
        while (i > 0) {
            ins[--i] = input & 1;
            input /= 2;
        }

        switch (opcode) {
            case '1':
                fputs("add ", stdout);
                printAddAnd(ins);
                break;
            case '5':
                fputs("and ", stdout);
                printAddAnd(ins);
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
    printf("%c%d", 'r', binToDec(ins, 0, 3));
    putchar(',');
    printf("%c%d", 'r', binToDec(ins, 3, 3));
    putchar(',');
    printf("%c%d", 'r', binToDec(ins, 9, 3));
}

int binToDec(int *a, int start, int length) {
    int base = 1, res = 0, i;

    for (i = start + length - 1; i >= start; i--) {
        res += a[i] * base;
        base *= 2;
    }

    return res;
}
