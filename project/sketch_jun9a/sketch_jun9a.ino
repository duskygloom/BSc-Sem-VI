#include "ascon.h"
#include "byte_arr.h"

#include "secure_comm.h"

Key key = {0x1234567890, 0x9876543210};
Key nonce;

Ascon ascon(key, nonce);

ECC bob;
ECC alice;

void setup() {
    Serial.begin(115200);
    Serial.println("\n\n--- New Session ---\n");

    Serial.print("Free heap: ");
    Serial.println(ESP.getFreeHeap());

    ulong start = micros();
    bob.generateKeyPair();
    Serial.println(String("Bob key generation: ") + String(micros()-start) + " us.");

    Serial.print("Free heap: ");
    Serial.println(ESP.getFreeHeap());

    start = micros();
    alice.generateKeyPair();
    Serial.println(String("Alice key generation: ") + String(micros()-start) + " us.");

    Serial.print("Free heap: ");
    Serial.println(ESP.getFreeHeap());

    start = micros();
    bob.generateSharedKey(alice.pubKey);
    Serial.println(String("Bob shared key generation: ") + String(micros()-start) + " us.");
    Serial.println();

    Serial.print("Free heap: ");
    Serial.println(ESP.getFreeHeap());

    start = micros();
    alice.generateSharedKey(bob.pubKey);
    Serial.println(String("Alice shared key generation: ") + String(micros()-start) + " us.");



    Serial.print("Free heap: ");
    Serial.println(ESP.getFreeHeap());
}

void loop() {
    if (Serial.available()) {
        Serial.print("Free heap (before): ");
        Serial.println(ESP.getFreeHeap());

        String s = Serial.readString();
        ByteArr cipher;
        Key tag;
        
        Serial.println("Start.");
        
        ulong start = micros();
        ascon.encrypt(s, "all planned - testing phase", cipher, tag);
        Serial.println(String("Encryption: ") + String(micros()-start) + " us.");
        start = micros();
        String m = ascon.decrypt(cipher, "all planned - testing phase", tag);
        Serial.println(String("Decryption: ") + String(micros()-start) + " us.");

        Serial.print("Cipher: ");
        for (int i = 0; i < s.length(); ++i) {
            Serial.printf("\\%02x", cipher.b[i]);
        }
        Serial.println();

        Serial.println("Plain: " + m);

        deleteByteArr(cipher);

        Serial.println("Done.");

        Serial.print("Free heap (after): ");
        Serial.println(ESP.getFreeHeap());
    }
}
