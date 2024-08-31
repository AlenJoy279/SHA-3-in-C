// #include "sha-3.h"
// #include "../externals/keccak/keccak.h"
// #include <stdio.h>
// #include <string.h>

// // Function to print bytes for debugging
// void print_hex(const uint8_t *data, size_t size) {
//     for (size_t i = 0; i < size; i++) {
//         printf("%02x", data[i]);
//     }
//     printf("\n");
// }

// // Test function for SHA3-256
// int test_sha3_256() {
//     uint8_t message[] = "The quick brown fox jumps over the lazy dog";
//     uint8_t output[32]; // SHA3-256 produces a 256-bit hash
//     uint8_t expected_output[32] = {
//         0xA7, 0x98, 0x8D, 0xA7, 0x79, 0xBA, 0xC1, 0xDE,
//         0x44, 0x8B, 0xB6, 0x25, 0xC6, 0x53, 0xD0, 0x77,
//         0xF0, 0x9B, 0x7A, 0x7C, 0x2F, 0x85, 0x0E, 0x40,
//         0x78, 0x8C, 0xA6, 0x98, 0xCE, 0xD7, 0x5F, 0xE4
//     };

//     sha3_256(message, strlen((char *)message), output);

//     if (memcmp(output, expected_output, 32) == 0) {
//         printf("SHA3-256 Test passed!\n");
//         return 0;
//     } else {
//         printf("SHA3-256 Test failed!\n");
//         print_hex(output, 32);
//         return 1;
//     }
// }

// int main() {
//     return test_sha3_256();
// }
