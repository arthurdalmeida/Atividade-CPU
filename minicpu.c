#include <stdio.h>
#include <stdint.h>

uint8_t mem[256] = {0};
uint8_t reg[4] = {0};
uint8_t pc = 0;
uint8_t zf = 0;
uint8_t running = 1;

int ciclo = 0;

void fetch(uint8_t *op, uint8_t *a, uint8_t *b) {
    *op = mem[pc];
    *a = mem[pc + 1];
    *b = mem[pc + 2];

    pc += 3;
}

void decode_execute(uint8_t op, uint8_t a, uint8_t b) {
    switch (op) {
        case 0x01:
            reg[a] = mem[b];
            break;

        case 0x02:
            mem[b] = reg[a];
            break;

        case 0x03:
            reg[a] = reg[a] + reg[b];
            break;

        case 0x04:
            reg[a] = reg[a] - reg[b];
            break;

        case 0x05:
            reg[a] = b;
            break;

        case 0x06:
            zf = (reg[a] == reg[b]) ? 1 : 0;
            break;

        case 0x07:
            pc = a;
            break;

        case 0x08:
            if (zf) {
                pc = a;
            }
            break;

        case 0x09:
            if (!zf) {
                pc = a;
            }
            break;

        case 0x0A:
            running = 0;
            break;
    }
}

void trace(uint8_t op, uint8_t a, uint8_t b) {
    const char *nomes[] = {
        "",
        "LOAD",
        "STORE",
        "ADD",
        "SUB",
        "MOV",
        "CMP",
        "JMP",
        "JZ",
        "JNZ",
        "HALT"
    };

    printf(
        "Ciclo %d: %-5s %d,%d | "
        "R0=%3d R1=%3d R2=%3d R3=%3d | "
        "PC=%3d ZF=%d\n",
        ciclo,
        nomes[op],
        a,
        b,
        reg[0],
        reg[1],
        reg[2],
        reg[3],
        pc,
        zf
    );
}

int main() {
    mem[0x10] = 34;
    mem[0x11] = 12;
    mem[0x12] = 56;
    mem[0x13] = 3;
    mem[0x14] = 78;
    mem[0x15] = 45;
    mem[0x16] = 9;
    mem[0x17] = 67;

    mem[0x00] = 0x07;
    mem[0x01] = 0x40;
    mem[0x02] = 0x00;

    uint8_t programa[] = {
        0x05, 0x00, 0x00,
        0x05, 0x02, 0x01,

        0x01, 0x01, 0x10,
        0x06, 0x00, 0x01,
        0x08, 0x94, 0x00,

        0x01, 0x01, 0x11,
        0x06, 0x00, 0x01,
        0x08, 0x94, 0x00,

        0x01, 0x01, 0x12,
        0x06, 0x00, 0x01,
        0x08, 0x94, 0x00,

        0x01, 0x01, 0x13,
        0x06, 0x00, 0x01,
        0x08, 0x94, 0x00,

        0x01, 0x01, 0x14,
        0x06, 0x00, 0x01,
        0x08, 0x94, 0x00,

        0x01, 0x01, 0x15,
        0x06, 0x00, 0x01,
        0x08, 0x94, 0x00,

        0x01, 0x01, 0x16,
        0x06, 0x00, 0x01,
        0x08, 0x94, 0x00,

        0x01, 0x01, 0x17,
        0x06, 0x00, 0x01,
        0x08, 0x94, 0x00,

        0x03, 0x00, 0x02,
        0x07, 0x46, 0x00,

        0x02, 0x00, 0x20,
        0x0A, 0x00, 0x00
    };

    int tamanho = sizeof(programa) / sizeof(programa[0]);

    for (int i = 0; i < tamanho; i++) {
        mem[0x40 + i] = programa[i];
    }

    while (running) {
        uint8_t op;
        uint8_t a;
        uint8_t b;

        ciclo++;

        fetch(&op, &a, &b);
        decode_execute(op, a, b);
        trace(op, a, b);
    }

    printf("\nMenor valor encontrado: %d\n", mem[0x20]);
    printf("Resultado armazenado em mem[0x20].\n");

    return 0;
}