#include <stdio.h>

#include "byte_arr.h"
#include "ascon.h"

int main() {
    ByteArr plain = bytesFromString("For lists of detected and suppressed errors, rerun with: -s");
    ByteArr assData = bytesFromString("Yo mista white");

    Key key = {2025, 2003};
    Key nonce = {2020, 2004};
    Key tag;

    ByteArr cipher = asconEncrypt(key, nonce, assData, plain, tag);
    deleteByteArr(plain);
    printf("Cipher: ");
    for (int i = 0; i < cipher.length; ++i)
        printf("%c", cipher.b[i]);
    putchar('\n');
    printf("Tag: %016lx %016lx\n", tag[0], tag[1]);

    ByteArr recovered = asconDecrypt(key, nonce, assData, cipher, tag);
    deleteByteArr(assData);
    printf("Recovered: ");
    for (int i = 0; i < recovered.length; ++i)
        printf("%c", recovered.b[i]);
    putchar('\n');

    deleteByteArr(cipher);
    deleteByteArr(recovered);
}
