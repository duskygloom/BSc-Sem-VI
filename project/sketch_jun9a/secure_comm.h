#pragma once

#include <Arduino.h>
#include <uECC.h>

#include "ascon.h"
#include "byte_arr.h"
#include "rng.h"

class Ascon {
    private:
    const word64 *key;
    const word64 *nonce;

    public:
    Ascon(const Key key, const Key nonce);

    /**
     * @note
     * Do not preallocate byte arrays. The function will allocate byte arrays on
     * its own. Make sure to clean up later tho.
     */
    void encrypt(const String &message, const String &data, ByteArr &cipher, Key tag);

    /**
     * @note
     * Do not preallocate byte arrays. The function will allocate byte arrays on
     * its own. Make sure to clean up later tho.
     */
    String decrypt(const ByteArr &cipher, const String &data, const Key tag);
};

class ECC {
    private:
    uECC_Curve curve;

    public:
    byte pubKey[PUBKEYLEN];
    byte pvtKey[PVTKEYLEN];
    byte shrKey[PVTKEYLEN];
    
    /**
     * @brief
     * Key used for encryption and decryption.
     */
    Key encKey;

    /**
     * @note
     * Uses A0 pin as the entropy source.
     */
    ECC();

    /**
     * @param analogPin
     * An un-initialized analogPin is used to generate
     * truly random numbers.
     */
    ECC(byte analogPin);

    /**
     * @note
     * After generation, public key is stored in ECC::pubKey
     * and private key is stored in ECC::pvtKey
     */
    void generateKeyPair();

    /**
     * @note
     * After generation, shared key is stored in ECC::shrKey
     * Also calculates a 128-bit key for ASCON from shared
     * key.
     * 
     * @param peerPubKey
     * Public key of the peer with whom you want to create
     * a shared key with.
     */
    void generateSharedKey(const byte *peerPubKey);
};
