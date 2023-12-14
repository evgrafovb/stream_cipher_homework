#include <iostream>
#include <string>
#include <chrono>
#include "algos.h"

using namespace std;

void testing_RC4(vector<string>& text, const string& key) {
	cout << "RC4 cipher algorithm" << endl;
	auto start1 = std::chrono::system_clock::now();
	auto result1 = RC4_Cipher(text, key);
	auto end1 = std::chrono::system_clock::now();
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
	cout << duration1.count() << " mcs" << endl;
	cout << "RC4 decipher algorithm" << endl;
	auto start2 = std::chrono::system_clock::now();
	auto result2 = RC4_Decipher(text, key);
	auto end2 = std::chrono::system_clock::now();
	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
	cout << duration2.count() << " mcs" << endl;
}

//void testing_A5(const string& text) {
//	cout << "A5 cipher algorithm" << endl;
//	auto start1 = std::chrono::system_clock::now();
//	auto result1 = ;
//	auto end1 = std::chrono::system_clock::now();
//	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
//	cout << duration1 << endl;
//	cout << "RC4 decipher algorithm" << endl;
//	auto start2 = std::chrono::system_clock::now();
//	auto result2 = RC4_Decipher(text, key);
//	auto end2 = std::chrono::system_clock::now();
//	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
//	cout << duration2 << endl;
//
//}

void testing_Salsa20(uint8_t* text) {
	cout << "Salsa20 cipher algorithm" << endl;
	auto start1 = std::chrono::system_clock::now();
	auto result1 = salsa20Encrypt(text);
	auto end1 = std::chrono::system_clock::now();
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
	cout << duration1.count() << " mcs" << endl;
	cout << "Salsa20 decipher algorithm" << endl;
	auto start2 = std::chrono::system_clock::now();
	auto result2 = salsa20Decrypt(text);
	auto end2 = std::chrono::system_clock::now();
	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
	cout << duration2.count() << " mcs" << endl;
}

int main() {
	
	vector<string> text1 = { "Hello, world! :) RC4 is a symmetric key stream cipher..." };
	string keyRC4 = "1*&^567WoRd";
	testing_RC4(text1, keyRC4);

	const uint8_t key[32] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
	};

	const uint8_t nonce[8] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	uint8_t plaintext[64] = {
		'H', 'e', 'l', 'l', 'o', ',', ' ', 'w',
		'o', 'r', 'l', 'd', '!', ' ', ':', ')',
		'S', 'a', 'l', 's', 'a', '2', '0', ' ',
		'i', 's', ' ', 'a', ' ', 's', 'y', 'm',
		'm', 'e', 't', 'r', 'i', 'c', ' ', 'k',
		'e', 'y', ' ', 's', 't', 'r', 'e', 'a',
		'm', ' ', 'c', 'i', 'p', 'h', 'e', 'r',
		'.', '.', '.'
	};
	//testing_Salsa20(plaintext);
	return 0;
}
