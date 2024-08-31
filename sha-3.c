#include "sha-3.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

// Implementation references: https://github.com/davidsteinsland/keccak/blob/master/keccak.c, https://github.com/brainhub/SHA3IUF, https://github.com/brainhub/SHA3IUF/blob/master/README.md
// Parameters for SHA-3-256
#define STATE_SIZE 200  // 5x5x64 bits / 8 bits/byte = 200 bytes
#define RATE 136        // 1088 bits / 8 bits/byte
#define CAPACITY 64     // 512 bits / 8 bits/byte
#define KECCAK_ROUNDS 24
#define OUTPUT_LENGTH 32 // Output length for SHA-3-256 in bytes

// Define rotation constants and round constants
static const unsigned RHO_OFFSETS[5][5] = {
    {0, 1, 62, 28, 27},
    {36, 44, 6, 55, 20},
    {3, 10, 43, 25, 39},
    {41, 45, 15, 21, 8},
    {18, 2, 61, 56, 14}
};

static const uint64_t ROUND_CONSTANTS[KECCAK_ROUNDS] = {
    0x0000000000000001, 0x0000000000008082, 0x800000000000808A,
    0x8000000080008000, 0x000000000000808B, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009, 0x000000000000008A,
    0x0000000000000088, 0x0000000080008009, 0x000000008000000A,
    0x000000008000808B, 0x800000000000008B, 0x8000000000008089,
    0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
    0x000000000000800A, 0x800000008000000A, 0x8000000080008081,
    0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};

// Helpers for bit manipulation and state manipulation
uint64_t rotate_left(uint64_t x, unsigned s) {
    return (x << s) | (x >> (64 - s));
}

// Keccak-f permutation
static void keccak_f(uint64_t state[25]) {
    int i, j, round;
    uint64_t temp[5], t;
    uint64_t R[5][5];

    // Load state into 5x5 matrix
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            R[i][j] = state[i * 5 + j];
        }
    }

    for (round = 0; round < KECCAK_ROUNDS; round++) {
        // Theta step
        for (i = 0; i < 5; i++) {
            temp[i] = R[i][0] ^ R[i][1] ^ R[i][2] ^ R[i][3] ^ R[i][4];
        }
        for (i = 0; i < 5; i++) {
            t = temp[(i + 4) % 5] ^ rotate_left(temp[(i + 1) % 5], 1);
            for (j = 0; j < 5; j++) {
                R[i][j] ^= t;
            }
        }

        // Rho and Pi steps
        uint64_t last = R[0][1];
        for (i = 0; i < 24; i++) {
            int x = (i + 1) % 5;
            int y = (2 * i + 3 * i) % 5;
            t = R[x][y];
            R[x][y] = rotate_left(last, RHO_OFFSETS[x][y]);
            last = t;
        }

        // Chi step
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                temp[j] = R[i][j];
            }
            for (j = 0; j < 5; j++) {
                R[i][j] = temp[j] ^ (~temp[(j + 1) % 5] & temp[(j + 2) % 5]);
            }
        }

        // Iota step
        R[0][0] ^= ROUND_CONSTANTS[round];
    }

    // Unload state from 5x5 matrix
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            state[i * 5 + j] = R[i][j];
        }
    }
}

// SHA3-256 hashing function
unsigned char *keccak_hash(unsigned char *data, size_t length) {
    uint64_t state[25] = {0};
    size_t rate_in_bytes = RATE / 8;
    unsigned char *output = malloc(OUTPUT_LENGTH);

    if (!output) return NULL;

    // Absorb phase
    size_t i;
    for (i = 0; i < length; i += rate_in_bytes) {
        size_t block_size = length - i < rate_in_bytes ? length - i : rate_in_bytes;
        for (size_t j = 0; j < block_size; j++) {
            ((unsigned char*)state)[j] ^= data[i + j];
        }
        keccak_f(state);
    }

    // Squeeze phase
    memcpy(output, state, OUTPUT_LENGTH);

    return output;
}