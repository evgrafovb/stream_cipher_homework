#pragma once
#include <string>
#include <vector>


using namespace std;

string RC4_Cipher(vector<string>& text, const string& key);
string RC4_Decipher(vector<string>& text, const string& key);
string salsa20Encrypt(uint8_t* plaintext, size_t plaintextLength, const uint8_t* key, const uint8_t* nonce);
string salsa20Decrypt(uint8_t* ciphertext, size_t ciphertextLength, const uint8_t* key, const uint8_t* nonce);
