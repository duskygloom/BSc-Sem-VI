#pragma once

#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "common.h"

/**
 * @warning
 * The program considers that couple will be in little
 * endian.
 * Not ported for big endian systems.
 * Maybe someday.
 */
struct ByteArr {
    union {
        byte *b;
        word64 *w;
    };
    int length;
};

ByteArr createByteArr(int size);

/**
 * @brief
 * Creates a bytes struct from a string.
 */
ByteArr bytesFromString(const char *s);

/**
 * @brief
 * Frees byte array inside bytes struct.
 */
void deleteByteArr(ByteArr &bytes);

void resizeByteArr(ByteArr &bytes, int newSize);

/**
 * @note
 * Returns another bytes struct padded with zeroes.
 * 
 * @warning
 * Remember to free the byte array, this function uses calloc.
 */
ByteArr getPaddedByteArr(ByteArr bytes);

/**
 * @brief
 * Right pads the byte array with 10*
 *
 * @param p
 * Keep p bytes from the left, and pad the byte sequence
 * after it.
 */
void rightPadByteArr(ByteArr &bytes, int p);
