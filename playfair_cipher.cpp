#include <bits/stdc++.h>
using namespace std;

void upperCasetoLowerCase(string &s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] > 64 and s[i] < 91)
        {
            s[i] += 32;
        }
    }
}

int removeSpaces(string &s)
{
    int count = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != ' ')
        {
            s[count++] = s[i];
        }
    }
    s[count] = '\0';
    return count;
}

void generateKeyTable(string &s, char keyTable[5][5])
{
    int m, n;
    int dict[26] = {0};
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != 'j')
        {
            dict[s[i] - 97] = 2;
        }
    }
    dict['j' - 97] = 1;

    m = n = 0;

    for (int i = 0; i < s.length(); i++)
    {
        if (dict[s[i] - 97] == 2)
        {
            dict[s[i] - 97] = 1;
            keyTable[m][n] = s[i];
            n++;
            if (n == 5)
            {
                m++;
                n = 0;
            }
        }
    }

    for (int i = 0; i < 26; i++)
    {
        if (dict[i] == 0)
        {
            keyTable[m][n] = (char)(i + 97);
            n++;
            if (n == 5)
            {
                m++;
                n = 0;
            }
        }
    }
}

void search(char keyTable[5][5], char a, char b, int arr[])
{
    int i, j;

    if (a == 'j')
        a = 'i';
    else if (b == 'j')
        b = 'i';

    for (i = 0; i < 5; i++)
    {

        for (j = 0; j < 5; j++)
        {

            if (keyTable[i][j] == a)
            {
                arr[0] = i;
                arr[1] = j;
            }
            else if (keyTable[i][j] == b)
            {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

int mod5(int a)
{
    if (a < 0)
        a += 5;
    return (a % 5);
}

int prepare(string &s)
{
    int ptrs=s.length();
    if (ptrs % 2 != 0) {
        s[ptrs++] = 'z';
        s[ptrs] = '\0';
    }
    return ptrs;
}

void encrypt(string &s, char keyTable[5][5])
{
    int i, a[4];
 
    for (i = 0; i < s.length(); i += 2) {
 
        search(keyTable, s[i], s[i + 1], a);
 
        if (a[0] == a[2]) {
            s[i] = keyTable[a[0]][mod5(a[1] + 1)];
            s[i + 1] = keyTable[a[0]][mod5(a[3] + 1)];
        }
        else if (a[1] == a[3]) {
            s[i] = keyTable[mod5(a[0] + 1)][a[1]];
            s[i + 1] = keyTable[mod5(a[2] + 1)][a[1]];
        }
        else {
            s[i] = keyTable[a[0]][a[3]];
            s[i + 1] = keyTable[a[2]][a[1]];
        }
    }
}

void encryptByPlayfairCipher(string &s, string &key)
{
    char keyTable[5][5];
    int ks,ps;
 
    ks = key.length();
    ks = removeSpaces(key);
    upperCasetoLowerCase(key);
 
    ps = s.length();
    ps = removeSpaces(s);
    upperCasetoLowerCase(s);
 
    ps = prepare(s);
 
    generateKeyTable(key, keyTable);
 
    encrypt(s, keyTable);
}

void decrypt(string &s, char keyTable[5][5])
{
    int i, a[4];
    for (i = 0; i < s.length(); i += 2) {
        search(keyTable, s[i], s[i + 1], a);
        if (a[0] == a[2]) {
            s[i] = keyTable[a[0]][mod5(a[1] - 1)];
            s[i + 1] = keyTable[a[0]][mod5(a[3] - 1)];
        }
        else if (a[1] == a[3]) {
            s[i] = keyTable[mod5(a[0] - 1)][a[1]];
            s[i + 1] = keyTable[mod5(a[2] - 1)][a[1]];
        }
        else {
            s[i] = keyTable[a[0]][a[3]];
            s[i + 1] = keyTable[a[2]][a[1]];
        }
    }
}

void decryptByPlayfairCipher(string &s, string &key)
{
    char keyTable[5][5];
    int ks,ps;
 
    // Key
    ks = key.length();
    ks = removeSpaces(key);
    upperCasetoLowerCase(key);
 
    // ciphertext
    ps = s.length();
    ps = removeSpaces(s);
    upperCasetoLowerCase(s);
 
    generateKeyTable(key, keyTable);
 
    decrypt(s, keyTable);
}

int main(){
    string s="mitul";
    string key="vardhan";
    encryptByPlayfairCipher(s,key);
    cout<<s<<endl;
    return 0;
}


