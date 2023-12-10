#include "A51Cipher.h"
#include <fstream>
#include <string>

A51Cipher::A51Cipher(unsigned long long key, unsigned long long frame)
{
    for (int i = 0; i < 64; ++i) {
        R1[18 - (i % 19)] = (key >> i) & 1;
        R2[21 - (i % 22)] = (key >> i) & 1;
        R3[22 - (i % 23)] = (key >> i) & 1;
    }
    for (int i = 0; i < 22; ++i) {
        R1[18 - (i % 19)] = R1[18 - (i % 19)] ^ (frame >> i) & 1;
        R2[21 - (i % 22)] = R2[21 - (i % 22)] ^ (frame >> i) & 1;
        R3[22 - (i % 23)] = R3[22 - (i % 23)] ^ (frame >> i) & 1;
    }
    for (int i = 0; i < 100; ++i) {
        clockWithMajority();
    }
}

bool A51Cipher::majorityBit() const
{
    return (R1[8] + R2[10] + R3[10]) >= 2;
}

void A51Cipher::clockWithMajority() {
    bool majority = majorityBit();
    if (R1[8] == majority) {
        bool new_bit = R1[13] ^ R1[16] ^ R1[17] ^ R1[18];
        R1 >>= 1;
        R1[18] = new_bit;
    }
    if (R2[10] == majority) {
        bool new_bit = R2[20] ^ R2[21];
        R2 >>= 1;
        R2[21] = new_bit;
    }
    if (R3[10] == majority) {
        bool new_bit = R3[7] ^ R3[20] ^ R3[21] ^ R3[22];
        R3 >>= 1;
        R3[22] = new_bit;
    }
}

char A51Cipher::getKeystreamByte() {
    char keystream = 0;
    for (int i = 0; i < 8; ++i) {
        clockWithMajority();
        bool bit = R1[18] ^ R2[21] ^ R3[22];
        keystream |= (bit << i);
    }
    return keystream;
}

string A51Cipher::encrypt(const string& plaintext) {
    string ciphertext;
    for (char c : plaintext) {
        char keystream = getKeystreamByte();
        ciphertext += c ^ keystream;
    }
    return ciphertext;
}