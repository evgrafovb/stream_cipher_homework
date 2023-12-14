#include <iostream>
#include <cstdint>
#include <cstring>
#include <string>

using namespace std;

void quarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d) {
    b ^= ((a + d) << 7) | ((a + d) >> (32 - 7));
    c ^= ((b + a) << 9) | ((b + a) >> (32 - 9));
    d ^= ((c + b) << 13) | ((c + b) >> (32 - 13));
    a ^= ((d + c) << 18) | ((d + c) >> (32 - 18));
}

string salsa20Encrypt(string plaintext) {

    int plaintextLength = plaintext.length();

    int k = 0;

    const uint8_t key[32] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
    };

    const uint8_t nonce[8] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    uint32_t state[16] = {
        0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
        *reinterpret_cast<const uint32_t*>(key),
        *reinterpret_cast<const uint32_t*>(key + 4),
        *reinterpret_cast<const uint32_t*>(key + 8),
        *reinterpret_cast<const uint32_t*>(key + 12),
        0,
        *reinterpret_cast<const uint32_t*>(nonce),
        *reinterpret_cast<const uint32_t*>(nonce + 4),
        0,
        0,
        1,
        0,
        1
    };

    uint32_t block[16];

    while (plaintextLength > 0) {
        memcpy(block, state, sizeof(block));

        for (int i = 0; i < 10; ++i) {
            quarterRound(block[0], block[4], block[8], block[12]);
            quarterRound(block[5], block[9], block[13], block[1]);
            quarterRound(block[10], block[14], block[2], block[6]);
            quarterRound(block[15], block[3], block[7], block[11]);

            quarterRound(block[0], block[1], block[2], block[3]);
            quarterRound(block[5], block[6], block[7], block[4]);
            quarterRound(block[10], block[11], block[8], block[9]);
            quarterRound(block[15], block[12], block[13], block[14]);
        }

        for (int i = 0; i < 16; ++i) {
            block[i] += state[i];
        }
        float f = 0;
        for (int i = 0; i < 16; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (i * 4 + j + k == plaintext.length())
                {
                    f = 1;
                    break;
                }
                plaintext[i * 4 + j] ^= block[i] >> (8 * j);
            }
            if (f) break;
        }

        state[8]++;
        if (state[8] == 0) {
            state[9]++;
        }

        k += 64;
        plaintextLength -= 64;
    }

        return plaintext;
}

string salsa20Decrypt(string ciphertext) {

    int ciphertextLength = ciphertext.length();
    int k = 0;

    const uint8_t key[32] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
    };
        
    const uint8_t nonce[8] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    uint32_t state[16] = {
        0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
        *reinterpret_cast<const uint32_t*>(key),
        *reinterpret_cast<const uint32_t*>(key + 4),
        *reinterpret_cast<const uint32_t*>(key + 8),
        *reinterpret_cast<const uint32_t*>(key + 12),
        0,
        *reinterpret_cast<const uint32_t*>(nonce),
        *reinterpret_cast<const uint32_t*>(nonce + 4),
        0,
        0,
        1,
        0,
        1
    };

    uint32_t block[16];

    while (ciphertextLength > 0) {
        memcpy(block, state, sizeof(block));

        for (int i = 0; i < 10; ++i) {
            quarterRound(block[0], block[4], block[8], block[12]);
            quarterRound(block[5], block[9], block[13], block[1]);
            quarterRound(block[10], block[14], block[2], block[6]);
            quarterRound(block[15], block[3], block[7], block[11]);

            quarterRound(block[0], block[1], block[2], block[3]);
            quarterRound(block[5], block[6], block[7], block[4]);
            quarterRound(block[10], block[11], block[8], block[9]);
            quarterRound(block[15], block[12], block[13], block[14]);
        }

        for (int i = 0; i < 16; ++i) {
            block[i] += state[i];
        }
        float f = 0;
        for (int i = 0; i < 16; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (i * 4 + j + k == ciphertext.length())
                {
                    f = 1;
                    break;
                }
                ciphertext[i * 4 + j] ^= block[i] >> (8 * j);
            }
            if (f) break;
        }

        state[8]++;
        if (state[8] == 0) {
            state[9]++;
        }

        k += 64;
        ciphertextLength -= 64;
    }

    return ciphertext;
}