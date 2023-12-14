#pragma once
#include <string>
#include <vector>


using namespace std;

string RC4_Cipher(vector<string>& text, const string& key);
string RC4_Decipher(vector<string>& text, const string& key);
string salsa20Encrypt(uint8_t* plaintext);
string salsa20Decrypt(uint8_t* ciphertext);
