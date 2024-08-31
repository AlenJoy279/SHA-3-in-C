#ifndef SHA_3_H
#define SHA_3_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

unsigned char *keccak_hash(unsigned char *data, size_t length);
#endif // SHA_3_H