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
	return 0;
}