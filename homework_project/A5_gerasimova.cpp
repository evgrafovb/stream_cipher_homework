#include <iostream>
#include "A51Cipher.h"
#include <string>

using namespace std;

int main() {
    unsigned long long key = 0x1234567890ABCDEF; // 64-bit key
    unsigned long long frame = 0x134; // Frame number

    /* unsigned long long key, frame;
     cout << "Enter new key: ";
     cin >> key;
     cout << "Enter new frame number: ";
     cin >> frame;

     cin.ignore(); // Очистить буфер
     */

     // Создание экземпляра шифра с введенными ключом и номером кадра
    A51Cipher cipher(key, frame);

    // Шифрование текста
    cout << "Enter a Text: ";
    string plaintext;
    getline(cin, plaintext);


    string ciphertext = cipher.encrypt(plaintext);
    cout << "Encrypted Text: ";
    for (char c : ciphertext) {
        cout << hex << (int)(unsigned char)c << "";
    }
    cout << endl;

    // Ввод зашифрованного текста для дешифрования
    cout << "Enter Encrypted Text to Decrypt: ";
    string encryptedText;
    getline(cin, encryptedText);

    string hexToDecrypt = A51Cipher::hexStringToBytes(encryptedText);

    // Дешифрование зашифрованного текста
    cipher.setKey(key, frame); // Переустановка ключа перед дешифрованием
    string decryptedText = cipher.decrypt(hexToDecrypt);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}