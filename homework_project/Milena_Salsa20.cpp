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

string salsa20Encrypt(uint8_t* plaintext) {

    size_t plaintextLength = sizeof(plaintext);

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

        for (int i = 0; i < 16; ++i) {
            for (int j = 0; j < 4; ++j) {
                plaintext[i * 4 + j] ^= block[i] >> (8 * j);
            }
        }

        state[8]++;
        if (state[8] == 0) {
            state[9]++;
        }

        plaintext += 64;
        plaintextLength -= 64;
    }
    string text = "Encrypted message:\n";
    //std::cout << "Encrypted message: ";
    
        for (int i = 0; i < sizeof(plaintext); ++i) {
            //std::cout << plaintext[i];
            text += plaintext[i];
        }
        text += "\n";

        return text;
}

string salsa20Decrypt(uint8_t* ciphertext) {

    size_t ciphertextLength = sizeof(ciphertext);

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

        for (int i = 0; i < 16; ++i) {
            for (int j = 0; j < 4; ++j) {
                ciphertext[i * 4 + j] ^= block[i] >> (8 * j);
            }
        }

        state[8]++;
        if (state[8] == 0) {
            state[9]++;
        }

        ciphertext += 64;
        ciphertextLength -= 64;
    }

    string text = "Decrypted message:\n";
    //std::cout << "Decrypted message: ";
    
    for (int i = 0; i < sizeof(ciphertext); ++i) {
        //std::cout << ciphertext[i];
        text += ciphertext[i];
    }
    
    //std::cout << std::endl;
    return text;
}

//int main() {
//    const uint8_t key[32] = {
//        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
//        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
//        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
//        0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
//    };
//
//    const uint8_t nonce[8] = {
//        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//    };
//
//    uint8_t plaintext[64] = {
//        'H', 'e', 'l', 'l', 'o', ',', ' ', 'w',
//        'o', 'r', 'l', 'd', '!', ' ', ':', ')',
//        'S', 'a', 'l', 's', 'a', '2', '0', ' ',
//        'i', 's', ' ', 'a', ' ', 's', 'y', 'm',
//        'm', 'e', 't', 'r', 'i', 'c', ' ', 'k',
//        'e', 'y', ' ', 's', 't', 'r', 'e', 'a',
//        'm', ' ', 'c', 'i', 'p', 'h', 'e', 'r',
//        '.', '.', '.'
//    };
// 
//    uint8_t plaintext[320] = {
//    'D', 'o', ' ', 'y', 'o', 'u', ' ', 'l', 'i', 'k', 'e', ' ', 'w',
//    'a', 't', 'c', 'h', 'i', 'n', 'g', ' ', 'c', 'a', 'r', 't', 'o',
//    'o', 'n', 's', '?', ' ', 'P', 'r', 'o', 'b', 'a', 'b', 'l', 'y',
//    ' ', 'y', 'o', 'u', ' ', 'd', 'o', '!', ' ', 'B', 'u', 't', ' ',
//    'h', 'o', 'w', ' ', 'd', 'i', 'd', ' ', 't', 'h', 'e', 'y', ' ',
//    'c', 'o', 'm', 'e', ' ', 't', 'o', ' ', 'b', 'e', '?', ' ', 'W',
//    'h', 'o', ' ', 'i', 'n', 'v', 'e', 'n', 't', 'e', 'd', ' ', 't',
//    'h', 'e', 'm', '?', '\n', 'T', 'h', 'i', 's', ' ', 'i', 's',
//    ' ', 'a', 'c', 't', 'u', 'a', 'l', 'l', 'y', ' ', 'a', ' ', 'v',
//    'e', 'r', 'y', ' ', 't', 'o', 'u', 'g', 'h', ' ', 'q', 'u', 'e',
//    's', 't', 'i', 'o', 'n', '.', ' ', 'T', 'h', 'e', ' ', 'f', 'i',
//    'r', 's', 't', ' ', 'c', 'a', 'r', 't', 'o', 'o', 'n', 's', ' ',
//    'w', 'e', 'r', 'e', ' ', 'c', 'r', 'e', 'a', 't', 'e', 'd', ' ',
//    'l', 'o', 'n', 'g', ' ', 'b', 'e', 'f', 'o', 'r', 'e', ' ', 't',
//    'h', 'e', ' ', 'T', 'V', '.', ' ', 'F', 'o', 'r', ' ', 'e', 'x',
//    'a', 'm', 'p', 'l', 'e', ',', ' ', 's', 'h', 'a', 'd', 'o', 'w',
//    ' ', 'p', 'l', 'a', 'y', '2', ' ', 'w', 'a', 's', ' ', 'a', ' ',
//    'v', 'e', 'r', 'y', ' ', 'p', 'o', 'p', 'u', 'l', 'a', 'r', ' ',
//    'f', 'o', 'r', 'm', ' ', 'o', 'f', ' ', 'e', 'n', 't', 'e', 'r',
//    't', 'a', 'i', 'n', 'm', 'e', 'n', 't', '3', ' ', 'i', 'n', ' ',
//    'a', 'n', 'c', 'i', 'e', 'n', 't', ' ', 'C', 'h', 'i', 'n', 'a',
//    '.', ' ', 'S', 'u', 'c', 'h', ' ', 's', 'h', 'o', 'w', 's', ' ',
//    'l', 'o', 'o', 'k', 'e', 'd', ' ', 'a', 'l', 'm', 'o', 's', 't',
//    ' ', 'l', 'i', 'k', 'e', ' ', 'm', 'o', 'd', 'e', 'r', 'n', ' ',
//    'c', 'a', 'r', 't', 'o', 'o', 'n', 's', '!'
//    };
//
//    salsa20Encrypt(plaintext, sizeof(plaintext), key, nonce);
//
//    std::cout << "Encrypted message: ";
//
//    for (int i = 0; i < sizeof(plaintext); ++i) {
//        std::cout << plaintext[i];
//    }
//
//    std::cout << std::endl;
//
//    salsa20Decrypt(plaintext, sizeof(plaintext), key, nonce);
//
//    std::cout << "Decrypted message: ";
//
//    for (int i = 0; i < sizeof(plaintext); ++i) {
//        std::cout << plaintext[i];
//    }
//
//    std::cout << std::endl;
// 
//    return 0;
//}