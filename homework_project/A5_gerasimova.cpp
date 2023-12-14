#include <iostream>
#include <bitset>
#include <string>
#include <cstdlib> // Для std::strtol

using namespace std;

bitset<19> R1;
bitset<22> R2;
bitset<23> R3;

// Определение большинственного бита
bool majorityBit()
{
    return (R1[8] + R2[10] + R3[10]) >= 2;
}

//Тактирование регистров с учетом большинственного бита
void clockWithMajority() {
    bool majority = majorityBit();
    if (R1[8] == majority) {
        bool new_bit = R1[13] ^ R1[16] ^ R1[17] ^ R1[18];
        R1 >>= 1;
        R1[18] = new_bit;
    }
    if (R2[10] == majority) {
        bool new_bit = R2[20] ^ R2[21];
        R2 >>= 1;
        R2[21] = new_bit;
    }
    if (R3[10] == majority) {
        bool new_bit = R3[7] ^ R3[20] ^ R3[21] ^ R3[22];
        R3 >>= 1;
        R3[22] = new_bit;
    }
}

// Инициализация регистров R1, R2, R3 с ключом и номером кадра
void initializeCipher(unsigned long long key, unsigned long long frame) {

    for (int i = 0; i < 64; ++i) {
        R1[18 - (i % 19)] = (key >> i) & 1;
        R2[21 - (i % 22)] = (key >> i) & 1;
        R3[22 - (i % 23)] = (key >> i) & 1;
    }
    for (int i = 0; i < 22; ++i) {
        R1[18 - (i % 19)] = R1[18 - (i % 19)] ^ (frame >> i) & 1;
        R2[21 - (i % 22)] = R2[21 - (i % 22)] ^ (frame >> i) & 1;
        R3[22 - (i % 23)] = R3[22 - (i % 23)] ^ (frame >> i) & 1;
    }
    for (int i = 0; i < 100; ++i) {
        clockWithMajority();
    }
}

// Генерация байта ключевого потока
char getKeystreamByte() {
    char keystream = 0;
    for (int i = 0; i < 8; ++i) {
        clockWithMajority();
        bool bit = R1[18] ^ R2[21] ^ R3[22];
        keystream |= (bit << i);
    }
    return keystream;
}

// Шифрование текста
string encrypt(const string& plaintext) {
    unsigned long long key = 0x1234567890ABCDEF; // 64-bit key
    unsigned long long frame = 0x134; // Frame number
    initializeCipher(key, frame);
    string ciphertext;
    for (char c : plaintext) {
        char keystream = getKeystreamByte();
        ciphertext += c ^ keystream;
    }
    return ciphertext;
}


// Дешифрование текста
string decrypt(const string& ciphertext) {
    unsigned long long key = 0x1234567890ABCDEF; // 64-bit key
    unsigned long long frame = 0x134; // Frame number
    initializeCipher(key, frame);
    string plaintext;
    for (char c : ciphertext) {
        char keystream = getKeystreamByte();
        plaintext += c ^ keystream;
    }
    return plaintext;
}

string hexStringToBytes(const string& hexString) {
    string bytes;
    for (size_t i = 0; i < hexString.length(); i += 2) {
        string byteString = hexString.substr(i, 2); // Извлекаем два символа
        char byte = static_cast<char>(strtol(byteString.c_str(), nullptr, 16)); // Преобразуем их в число
        bytes.push_back(byte); // Добавляем число в конец строки байтов
    }
    return bytes; // Возвращаем строку байтов
}