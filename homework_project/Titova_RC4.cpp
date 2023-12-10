#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Алгоритм шифрования RC4
string RC4_Cipher(vector<string>& text, const string& key)
{
    vector<int> S(256);
    int i = 0, j = 0;
    string result = "";

    for (int k = 0; k < 256; k++)
    {
        S[k] = k;
    }

    for (int k = 0; k < 256; k++)
    {
        j = (j + S[k] + key[k % key.size()]) % 256;
        swap(S[k], S[j]);
    }

    i = 0;
    j = 0;
    for (auto& str : text)
    {
        for (char& c : str)
        {
            i = (i + 1) % 256;
            j = (j + S[i]) % 256;
            swap(S[i], S[j]);
            c ^= S[(S[i] + S[j]) % 256];
            result += c;
        }
    }
    return result;
}
//Дешифрование зашифрованного алгоритма
string RC4_Decipher(vector<string>& text, const string& key)
{
    string res = "";
    res = RC4_Cipher(text, key);
    return res;
}