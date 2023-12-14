#include <iostream>
#include <string>
#include <chrono>
#include "algos.h"

using namespace std;

void testing_RC4(vector<string>& text, const string& key) {
	cout << "RC4 TESTING" << endl << endl;
	cout << "Text: ";
	for (string& str : text) {
		cout << str;
	}
	auto start1 = std::chrono::system_clock::now();
	auto result1 = RC4_Cipher(text, key);
	auto end1 = std::chrono::system_clock::now();
	cout << "\nEncrypted text: " << result1 << endl;
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
	cout << "TIME: " << duration1.count() << " mcs" << endl;
	auto start2 = std::chrono::system_clock::now();
	auto result2 = RC4_Decipher(text, key);
	auto end2 = std::chrono::system_clock::now();
	cout << "Decrypted text: " << result2 << endl;
	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
	cout << "TIME: " << duration2.count() << " mcs" << endl;
	cout << endl << endl;
}

void testing_A5(const string& text) {
	cout << "A5 TESTING" << endl << endl;
	cout << "Text: " << text << endl;
	auto start1 = std::chrono::system_clock::now();
	auto result1 = encrypt(text);
	auto end1 = std::chrono::system_clock::now();
	cout << "Encrypted text: " << result1 << endl;
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
	cout << "TIME: " << duration1.count() << " mcs" << endl;
	auto start2 = std::chrono::system_clock::now();
	auto result2 = decrypt(result1);
	auto end2 = std::chrono::system_clock::now();
	cout << "Decrypted text: " << result2 << endl;
	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
	cout << "TIME: " << duration2.count() << " mcs" << endl;
	cout << endl << endl;
}

void testing_Salsa20(uint8_t* text) {
	cout << "Salsa20 TESTING" << endl << endl;
	cout << "Text: ";
	for (int i = 0; i < sizeof(text); ++i) {
		cout << text[i];
	}
	auto start1 = std::chrono::system_clock::now();
	auto result1 = salsa20Encrypt(text);
	auto end1 = std::chrono::system_clock::now();
	cout << "Encrypted text: " << result1 << endl;
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
	cout << "TIME: " << duration1.count() << " mcs" << endl;
	auto start2 = std::chrono::system_clock::now();
	auto result2 = salsa20Decrypt(text);
	auto end2 = std::chrono::system_clock::now();
	cout << "Decrypted text: " << result2 << endl;
	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
	cout << "TIME: " << duration2.count() << " mcs" << endl;
	cout << endl << endl;
}

int main() {
	vector<string> text1_RC4 = { "Hello, world! :) RC4 is a symmetric key stream cipher..." };
	string keyRC4 = "1*&^567WoRd";
	testing_RC4(text1_RC4, keyRC4);

	string text1_A5 = "Hello, world! :) A5 is a symmetric key stream cipher...";
	testing_A5(text1_A5);

	uint8_t text1_Salsa20[64] = {
		'H', 'e', 'l', 'l', 'o', ',', ' ', 'w',
		'o', 'r', 'l', 'd', '!', ' ', ':', ')',
		'S', 'a', 'l', 's', 'a', '2', '0', ' ',
		'i', 's', ' ', 'a', ' ', 's', 'y', 'm',
		'm', 'e', 't', 'r', 'i', 'c', ' ', 'k',
		'e', 'y', ' ', 's', 't', 'r', 'e', 'a',
		'm', ' ', 'c', 'i', 'p', 'h', 'e', 'r',
		'.', '.', '.'
	};
	//testing_Salsa20(text1_Salsa20);
	return 0;
}
