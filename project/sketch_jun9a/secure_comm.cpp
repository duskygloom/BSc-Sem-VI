#include "secure_comm.h"

Ascon::Ascon(const Key key, const Key nonce)
: key(key), nonce(nonce) {}

void Ascon::encrypt(const String &message, const String &data, ByteArr &cipher, Key tag) {
    ByteArr dataBytes = bytesFromString(data.c_str());
    ByteArr plainBytes = bytesFromString(message.c_str());
    cipher = asconEncrypt(key, nonce, dataBytes, plainBytes, tag);
    deleteByteArr(dataBytes);
    deleteByteArr(plainBytes);
}

String Ascon::decrypt(const ByteArr &cipher, const String &data, const Key tag) {
    ByteArr dataBytes = bytesFromString(data.c_str());
    ByteArr plain = asconDecrypt(key, nonce, dataBytes, cipher, tag);
    deleteByteArr(dataBytes);
    String s;
    for (int i = 0; i < plain.length; ++i)
        s += plain.b[i];
    deleteByteArr(plain);
    return s;
}

ECC::ECC() : ECC(A0) {}

ECC::ECC(byte analogPin) {
    curve = uECC_secp256r1();
    randomSeed(trulyRandom(analogPin));
    uECC_set_rng(rngFunc);
}

void ECC::generateKeyPair() {
    if (!uECC_make_key(pubKey, pvtKey, curve))
        Serial.println("!!FAILED TO GENERATE KEY PAIRS!!");
}

void ECC::generateSharedKey(const byte *peerPubKey) {
    if (!uECC_shared_secret(peerPubKey, pvtKey, shrKey, curve)) {
        Serial.println("!!FAILED TO GENERATE SHARED KEY!!");
        return;
    }

    // shuffle and store the shared key as encryption key
    for (int i = 0; i < 8; ++i)
        encKey[1] = (encKey[1] << 8) | shrKey[2*i];
    for (int i = 0; i < 8; ++i)
        encKey[0] = (encKey[0] << 8) | shrKey[4*i+1];
}
