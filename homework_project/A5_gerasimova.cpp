#include <iostream>
#include <bitset>
#include <string>
#include <cstdlib> // Для std::strtol

using namespace std;


class A51Cipher {
private:
    bitset<19> R1;
    bitset<22> R2;
    bitset<23> R3;

    void initializeCipher(unsigned long long key, unsigned long long frame);
    bool majorityBit() const;
    void clockWithMajority();

public:
    A51Cipher(unsigned long long key, unsigned long long frame);
    void setKey(unsigned long long newKey, unsigned long long newFrame);
    char getKeystreamByte();
    string encrypt(const string& plaintext);
    string decrypt(const string& ciphertext);
    static string hexStringToBytes(const string& hexString);
};


A51Cipher::A51Cipher(unsigned long long key, unsigned long long frame) {
    initializeCipher(key, frame);
}

// Инициализация регистров R1, R2, R3 с ключом и номером кадра
void A51Cipher::initializeCipher(unsigned long long key, unsigned long long frame) {

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
// Определение большинственного бита
bool A51Cipher::majorityBit() const
{
    return (R1[8] + R2[10] + R3[10]) >= 2;
}

//Тактирование регистров с учетом большинственного бита
void A51Cipher::clockWithMajority() {
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

// Генерация байта ключевого потока
char A51Cipher::getKeystreamByte() {
    char keystream = 0;
    for (int i = 0; i < 8; ++i) {
        clockWithMajority();
        bool bit = R1[18] ^ R2[21] ^ R3[22];
        keystream |= (bit << i);
    }
    return keystream;
}

// Шифрование текста
string A51Cipher::encrypt(const string& plaintext) {
    string ciphertext;
    for (char c : plaintext) {
        char keystream = getKeystreamByte();
        ciphertext += c ^ keystream;
    }
    return ciphertext;
}


// Дешифрование текста
string A51Cipher::decrypt(const string& ciphertext) {
    string plaintext;
    for (char c : ciphertext) {
        char keystream = getKeystreamByte();
        plaintext += c ^ keystream;
    }
    return plaintext;
}

void A51Cipher::setKey(unsigned long long newKey, unsigned long long newFrame) {
    initializeCipher(newKey, newFrame);
}

string A51Cipher::hexStringToBytes(const string& hexString) {
    string bytes;
    for (size_t i = 0; i < hexString.length(); i += 2) {
        string byteString = hexString.substr(i, 2);
        char byte = static_cast<char>(strtol(byteString.c_str(), nullptr, 16));
        bytes.push_back(byte);
    }
    return bytes;
}

int main() {
    unsigned long long key = 0x1234567890ABCDEF; // 64-bit key
    unsigned long long frame = 0x134; // Frame number

    A51Cipher cipher(key, frame);

    cout << "Enter a Text: ";
    string plaintext;
    getline(cin, plaintext);

    // Шифрование текста
    string ciphertext = cipher.encrypt(plaintext);
    cout << "Encrypted Text: ";
    for (char c : ciphertext) {
        cout << hex << (int)(unsigned char)c << "";
    }
    cout << endl;

    // Дешифрование зашифрованного текста
    cipher.setKey(key, frame); // Переустановка ключа перед дешифрованием
    string decryptedText = cipher.decrypt(ciphertext);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}

