#include "byte_arr.h"

#include <stdio.h>

ByteArr createByteArr(int size) {
    ByteArr bytes;
    bytes.length = size;
    bytes.b = (byte *)calloc(size, 1);
    return bytes;
}

ByteArr bytesFromString(const char *s) {
    ByteArr bytes;
    int length = strlen(s);
    bytes.length = length;
    bytes.b = (byte *)calloc(length, 1);
    memcpy(bytes.b, s, length);
    return bytes;
}

void deleteByteArr(ByteArr &bytes) {
    free(bytes.b);
}

void resizeByteArr(ByteArr &bytes, int newSize) {
    bytes.b = (byte *)realloc(bytes.b, newSize);
    bytes.length = newSize;
}

/**
 * @note
 * Returns another bytes struct padded with zeroes.
 * 
 * @warning
 * Remember to free the byte array, this function uses calloc.
 */
ByteArr getPaddedByteArr(ByteArr bytes) {
    int zeros = RATE - 1 - bytes.length % RATE;
    int newLength = bytes.length + zeros + 1;
    byte *array = (byte *)calloc(newLength, 1);
    ByteArr padded = {
        .b = array,
        .length = newLength
    };
    memcpy(padded.b, bytes.b, bytes.length);
    memset(padded.b + bytes.length, 0, zeros);
    padded.b[bytes.length] = 0x80;
    return padded;
}

/**
 * @brief
 * Right pads the byte array with 10*
 *
 * @param p
 * Keep p bytes from the left, and pad the byte sequence
 * after it.
 */
void rightPadByteArr(ByteArr &bytes, int p) {
    if (p < bytes.length) {
        bytes.b[p] = 0x80;
    }
    for (int i = p+1; i < bytes.length; ++i) {
        bytes.b[i] = 0x00;
    }
}
