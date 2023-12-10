#include <iostream>
#include <string>
#include "A51Cipher.h"

using namespace std;

int main() 
{
	unsigned long long key = 0x1234567890ABCDEF; // 64-bit key
	unsigned long long frame = 0x134; // Frame number

	cout << "Enter a Text: ";
	string plaintext;
	getline(cin, plaintext);

	A51Cipher cipher(key, frame);
	string ciphertext = cipher.encrypt(plaintext);

	cout << "Encrypted Text: ";
	for (char c : ciphertext) {
		cout << hex << (int)c << " ";
	}
	return 0;
}