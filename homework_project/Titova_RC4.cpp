#include <iostream>
#include <vector>
using namespace std;
//Алгоритм шифрования RC4
vector<unsigned char> RC4_Cipher(vector<unsigned char> text, vector<unsigned char> key)
{
    vector<unsigned char> cipher_text;
    vector<unsigned char> S(256);
    vector<unsigned char> T(256);

    for (int i = 0; i < 256; i++)
    {
        S[i] = i;
        T[i] = key[i % key.size()];
    }

    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + S[i] + T[i]) % 256;
        swap(S[i], S[j]);
    }

    int i = 0;
    j = 0;
    for (unsigned char byte: text)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        int t = (S[i] + S[j]) % 256;
        cipher_text.push_back(byte ^ S[t]);
    }
    return cipher_text;
}
//Дешифрование зашифрованного алгоритма
vector<unsigned char> RC4_Decipher(vector<unsigned char> cipher_text, vector<unsigned char> key)
{
    return RC4_Cipher(cipher_text, key); 
}

int main
{
    vector<unsigned char> text = { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd', '!' };
    vector<unsigned char> key = { 'c', 'i', 'p', 'h', 'e', 'r' };
    vector<unsigned char> cipher_text = RC4_Cipher(text, key);
    vector<unsigned char> decipher_text = RC4_Decipher(cipher_text, key);

    cout << "Text: ";
    for (unsigned char byte: text)
    {
        cout << byte;
    }
    cout << endl;

    cout << "Cipher_text: ";
    for (unsigned char byte: cipher_text)
    {
        cout << byte;
    }
    cout << endl;

    cout << "Decipher_text: ";
    for (unsigned char byte: decipher_text)
    {
        cout << byte;
    }
    cout << endl;

	return 0;
}