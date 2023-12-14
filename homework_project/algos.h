#pragma once
#include <string>
#include <vector>


using namespace std;

string RC4_Cipher(vector<string>& text, const string& key);
string RC4_Decipher(vector<string>& text, const string& key);
string salsa20Encrypt(string plaintext);
string salsa20Decrypt(string ciphertext);
string encrypt(const string& plaintext);
string decrypt(const string& ciphertext);
