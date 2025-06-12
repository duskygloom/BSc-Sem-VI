#pragma once

#include <stdint.h>

/**
 * @warning
 * 128 has been used as key and nonce length in the entire code.
 * Things may break if it is changed. Will be changed later.
 */
#define KEYLEN 128

#define PUBKEYLEN 64
#define PVTKEYLEN 32

/**
 * @warning
 * 16 has been chosen as the rate. Since this is a block cipher,
 * plain text and associated data will be broken down into blocks
 * of size RATE bytes.
 * I will not be responsible if your code breaks after changing this!
 * Although it shouldn't break for reasonable values of RATE.
 */
#define RATE 8

typedef uint8_t byte;
typedef uint64_t word64;
typedef unsigned long ulong;

typedef uint64_t Key[KEYLEN/64]; // 2*64 = 128 bits

typedef uint64_t State[5]; // 5*64 = 320 bits
