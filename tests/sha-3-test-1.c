#include "sha-3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to print bytes for debugging
void print_hex(const uint8_t *data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

// Test function for SHA3-256
int test_sha3_256() {
    struct {
        char *message;
        uint8_t expected[32];
    } test_cases[] = {
        {
            "The quick brown fox jumps over the lazy dog",
            {
                0xA7, 0x98, 0x8D, 0xA7, 0x79, 0xBA, 0xC1, 0xDE,
                0x44, 0x8B, 0xB6, 0x25, 0xC6, 0x53, 0xD0, 0x77,
                0xF0, 0x9B, 0x7A, 0x7C, 0x2F, 0x85, 0x0E, 0x40,
                0x78, 0x8C, 0xA6, 0x98, 0xCE, 0xD7, 0x5F, 0xE4
            }
        },
        {
            "",
            {
                // Fill with the expected hash for an empty string after calculation or known hash
            }
        },
    };

    int errors = 0;
    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        uint8_t *output = keccak_hash((uint8_t *)test_cases[i].message, strlen(test_cases[i].message));

        if (memcmp(output, test_cases[i].expected, 32) != 0) {
            printf("SHA3-256 Test failed for message: %s\n", test_cases[i].message);
            printf("Expected: ");
            print_hex(test_cases[i].expected, 32);
            printf("Got:      ");
            print_hex(output, 32);
            errors++;
        } else {
            printf("SHA3-256 Test passed for message: %s\n", test_cases[i].message);
        }

        free(output); // Freeing the dynamically allocated memory
    }

    return errors;
}

int main() {
    if (test_sha3_256() == 0) {
        printf("All tests passed.\n");
        return 0;
    } else {
        printf("Some tests failed.\n");
        return 1;
    }
}
