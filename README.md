# LC-3 Disassembler
This is a simple disassembler for a subset of the LC-3 assembly language. It can translate machine code into assembly code and supports the following instruction type:

-   AND (Register mode & Immediate mode)
-   ADD (Register mode & Immediate mode)
-   JMP
-   BR

## Usage:
`$ program input [starting address]`

-   program - compiled source code
-   input - a file containing a list of machine code
-   starting address - address of the first assembly instruction used for PC relative calculation (default 0x0)

## Sample:
The input file contains:
```
1283
5105
0ffd
0802
1df7
506f
c080
```

Compile this program:
`gcc –o main disassembler.c`

The execution and the output of the program:
```
$ main input 3000
add r1,r2,r3
and r0,r4,r5
brnzp 0x3000
brn 0x3006
add r6,r7,-9
and r0,r1,15
jmp r2
```
