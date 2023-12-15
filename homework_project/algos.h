#pragma once
#include <string>
#include <vector>

using namespace std;

string RC4_Cipher(vector<string>& text, const string& key);
string RC4_Decipher(vector<string>& text, const string& key);
string salsa20Encrypt(string& plaintext, const uint8_t* key);
string salsa20Decrypt(string& ciphertext, const uint8_t* key);
string encrypt(string& plaintext, unsigned long long& key);
string decrypt(string& ciphertext, unsigned long long& key);
void initializeCipher(unsigned long long& key, unsigned long long& frame);
