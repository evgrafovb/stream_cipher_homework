#pragma once
#ifndef A51CIPHER_H
#define A51CIPHER_H

#include <bitset>
#include <string>

using namespace std;

class A51Cipher {
private:
    bitset<19> R1;
    bitset<22> R2;
    bitset<23> R3;

    void initializeCipher(unsigned long long key, unsigned long long frame);
    bool majorityBit() const;
    void clockWithMajority();

public:
    A51Cipher(unsigned long long key, unsigned long long frame);
    void setKey(unsigned long long newKey, unsigned long long newFrame);
    char getKeystreamByte();
    string encrypt(const string& plaintext);
    string decrypt(const string& ciphertext);
    static string hexStringToBytes(const string& hexString);
};


#endif // A51CIPHER_H

