#include <memory.h>
#include <stdint.h>
#include <stdio.h>

#include "ascon.h"
#include "byte_arr.h"

State state;

/**
 * @brief
 * Circular right rotate w by r.
 */
word64 crotr(word64 w, int r) {
    r %= 64; // decrease value of r if exceeds 64
    return (w >> r) | (w << (64 - r));
}

void printState() {
    for (int i = 0; i < 5; ++i) {
        printf("x%d=%016lx\n", i, state[i]);
    }
}

void substitutionLayer(State state) {
    state[0] ^= state[4];
    state[4] ^= state[3];
    state[2] ^= state[1];
    for (int j = 0; j < 5; ++j) {
        state[j] ^= ~state[(j+1)%5] & state[(j+2)%5];
    }
    state[0] ^= state[4];
    state[1] ^= state[0];
    state[2] = ~state[2];
    state[3] ^= state[2];
}

void diffusionLayer(State state) {
    state[0] ^= crotr(state[0], 19) ^ crotr(state[0], 28);
    state[1] ^= crotr(state[1], 61) ^ crotr(state[1], 39);
    state[2] ^= crotr(state[2], 1) ^ crotr(state[2], 6);
    state[3] ^= crotr(state[3], 10) ^ crotr(state[3], 17);
    state[4] ^= crotr(state[4], 7) ^ crotr(state[4], 41);
}

void asconPerm(State state, byte rounds) {
    byte cr = 0xf0 - (12-rounds)*0x0f; // round constant
    for (int i = 0; i < rounds; ++i) {
        // constant addition
        state[2] ^= cr;
        cr -= 0x0f;
        // substitution
        substitutionLayer(state);
        // diffusion
        diffusionLayer(state);
    }
}

/**
 * @brief
 * Sets an initial state value. Then you can proceed with
 * encryption.
 * @param a
 * Number of initialization or final rounds for permutation.
 * There are 12 rounds btw.
 * @param b
 * Number of intermediate rounds for permutation.
 * There are 8 intermediate rounds (so that I don't forget).
 */
void asconInit(State state, const Key key, const Key nonce,
               byte a, byte b) {
    /* state[0] will be the first 64 bits of IV */
    word64 IV = (word64)KEYLEN << 56 |
              (word64)(8 * RATE) << 48 |
              (word64)a << 40 | (word64)b << 32;
    state[0] = IV;
    /* state[1, 2] will consist of the key */
    state[1] = key[0];
    state[2] = key[1];
    /* state[3] and state[4] will be the nonce */
    state[3] = nonce[0];
    state[4] = nonce[1];
    /* initial permutation */
    asconPerm(state, a);
    /* XOR with key */
    state[3] ^= key[0];
    state[4] ^= key[1];
}

void asconProcessData(State state, byte b, ByteArr data) {
    if (data.length > 0) {
        ByteArr padded = getPaddedByteArr(data);
        /* XOR every RATE bytes from padded with first RATE
            bytes of state. Note that the following code is
            hardcoded for RATE = 8. */
        for (int i = 0; i < padded.length/RATE; ++i) {
            state[0] ^= padded.w[i];
            asconPerm(state, b);
        }
        free(padded.b);
    }
    state[4] ^= 0x01;
}

/**
 * @note
 * Array inside the returned byte has been calloc'ed. Remember
 * to clean it!
 */
ByteArr asconProcessText(State state, byte b, ByteArr plain) {
    ByteArr padded = getPaddedByteArr(plain);
    ByteArr cipher = createByteArr(padded.length);
    /* XOR every RATE bytes from padded with first RATE
        bytes of state. Note that the following code is
        hardcoded for RATE = 8. */
    int i;
    for (i = 0; i < padded.length/RATE - 1; ++i) {
        state[0] ^= padded.w[i];
        cipher.w[i] = state[0];
        asconPerm(state, b);
    }
    state[0] ^= padded.w[i];
    cipher.w[i] = state[0];
    deleteByteArr(padded);
    /* truncate and return */
    cipher.length = plain.length;
    resizeByteArr(cipher, plain.length);
    return cipher;
}

/**
 * @note
 * Array inside the returned byte has been calloc'ed. Remember
 * to clean it!
 */
ByteArr asconProcessCipher(State state, byte b, ByteArr cipher) {
    ByteArr padded = getPaddedByteArr(cipher);
    ByteArr plain = createByteArr(padded.length);
    /* XOR every RATE bytes from padded with first RATE
        bytes of state. Note that the following code is
        hardcoded for RATE = 8. */
    int i;
    for (i = 0; i < padded.length/RATE - 1; ++i) {
        plain.w[i] = state[0] ^ padded.w[i];
        state[0] = padded.w[i];
        asconPerm(state, b);
    }
    plain.w[i] = state[0] ^ padded.w[i];

    deleteByteArr(padded);
    rightPadByteArr(plain, cipher.length);
    state[0] ^= plain.w[i];
    resizeByteArr(plain, cipher.length);
    return plain;
}

/**
 * @brief
 * This function calculates the tag and stores it in the tag array
 * provided in the arguments.
 */
void finalization(State state, const Key key, byte a, Key tag) {
    state[1] ^= key[0];
    state[2] ^= key[1];
    asconPerm(state, a);
    tag[0] = state[3] ^ key[0];
    tag[1] = state[4] ^ key[1];
}

/**
 * @note
 * Array inside the returned byte has been calloc'ed. Remember
 * to clean it!
 * 
 * @param tag
 * Tag is a key array. Create it before hand and pass it to args.
 * The function will store the tag in it.
 */
ByteArr asconEncrypt(const Key key, const Key nonce, const ByteArr data,
                     const ByteArr text, Key tag) {
    byte a = 12; // initial or final rounds
    byte b = 6; // intermediate rounds

    memset(state, 0, 40); // 320 bits = 40 bytes
    asconInit(state, key, nonce, a, b);
    asconProcessData(state, b, data);
    ByteArr cipher = asconProcessText(state, b, text);
    finalization(state, key, a, tag);
    return cipher;
}

ByteArr asconDecrypt(const Key key, const Key nonce, const ByteArr data,
                     const ByteArr cipher, const Key tag) {
    byte a = 12; // initial or final rounds
    byte b = 6; // intermediate rounds

    memset(state, 0, 40); // 320 bits = 40 bytes
    asconInit(state, key, nonce, a, b);
    asconProcessData(state, b, data);
    ByteArr plain = asconProcessCipher(state, b, cipher);
    Key newTag;
    finalization(state, key, a, newTag);
    if (newTag[0] == tag[0] && newTag[1] == tag[1]) {
        return plain;
    } else {
        return createByteArr(0);
    }
}
