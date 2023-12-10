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
