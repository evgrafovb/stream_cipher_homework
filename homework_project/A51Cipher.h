#pragma once
#ifndef A51CIPHER_H
#define A51CIPHER_H

#include <bitset>
#include <string>

using namespace std;

class A51Cipher
{
private:
    bitset<19> R1;
    bitset<22> R2;
    bitset<23> R3;

    bool majorityBit() const;
    void clockWithMajority();

public:
    A51Cipher(unsigned long long key, unsigned long long frame);
    char getKeystreamByte();
    string encrypt(const string& plaintext);
};

#endif // A51CIPHER_H