#pragma once

#include <bitset>
#include <string>

using namespace std;

class A51Cipher
{
private:
    bitset<19> R1;
    bitset<22> R2;
    bitset<23> R3;

public:
    A51Cipher(unsigned long long key, unsigned long long frame);
};

