//
//  main.cpp
//  hw1 v3
//
//  Created by Iris Pei-Tzu Chen on 9/15/16.
//  Copyright © 2016 Iris. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctype.h>
using namespace std;

void PrintVigenereByRows()
{
    vector <char> alpha;
    char vigenere[26][26];
    for(int i=0; i<26; i++){
        alpha.push_back('A'+i);
    }
    
    for(int i=0; i<26; i++){
        for(int j=0; j<26; j++){
            vigenere[i][j] = alpha[(i+j)%26];
        }
    }
    cout << "This is the Vigenere Cipher: " << endl;
    for(int i=0; i<26; i++){
        for(int j=0; j<26; j++){
            cout << vigenere[i][j];
            if(j==25) cout << endl;
        }
    }
    cout << endl;
}

void PrintVigenereByColumns(){
    vector <char> alpha;
    char vigenere[26][26];
    for(int i=0; i<26; i++){
        alpha.push_back('A'+i);
    }
    
    for(int j=0; j<26; j++){
        for(int i=0; i<26; i++){
            vigenere[j][i] = alpha[(i+j)%26];
        }
    }
    cout << "This is the Vigenere Cipher: " << endl;
    for(int j=0; j<26; j++){
        for(int i=0; i<26; i++){
            cout << vigenere[j][i];
            if(i==25) cout << endl;
        }
    }
    cout << endl;
}

vector<char> GetPlaintext() 
{
    cout << "enter text:";
    string str1;
    getline(cin, str1);
    str1.erase(remove(str1.begin(), str1.end(), ' '), str1.end()); // erase blank space
    vector<char> plaintext(str1.begin(), str1.end()); //saved into a vector named plaintext
    return plaintext;
}

vector<int> TransferToAscii(vector<char> text)
{
    vector<int> NumText(text.size());
    
    for(int i=0; i<text.size(); i++){
        text[i]=toupper(text[i]);
        NumText[i] = text[i]-'A';
    }
    return NumText;

}

vector<char> TransferToLetter(vector<int> text)
{
    vector<char> LetterText(text.size());
    for(int i=0; i<LetterText.size(); i++){
        LetterText[i] = 'A' + text[i];
    }
    return LetterText;
}

vector<char> GetKeyword()
{
    string str;
    cout << "enter keyword:";
    getline(cin, str);
    vector<char> keyword(str.begin(), str.end());
    return keyword;
}

vector<char> ExpandKeyword(vector<char> plaintext, vector<char>keyword)
{
    vector<char> expandKey(plaintext.size());
    for(vector<char>::size_type i=0; i<plaintext.size(); i++){
        expandKey[i] = keyword[ i % keyword.size()];
    }
    return expandKey;
}

vector<int> Encryption(vector<int> expandedkey, vector<int> plaintext)
{
    vector<int> NumEncrypt(expandedkey.size());
    for(int i=0; i<=NumEncrypt.size(); i++){
        NumEncrypt[i]= ( (expandedkey[i] + plaintext[i]) % 26 );
    }
    return NumEncrypt;
}

vector<int> Decryption(vector<int> ExpandedNumKey, vector<int> EncryptedNumText)
{
    vector<int> NumDecrypt(ExpandedNumKey.size());
    for(int i=0; i<NumDecrypt.size(); i++){
        if(EncryptedNumText[i]-ExpandedNumKey[i] < 0){
            NumDecrypt[i] = 26 + (EncryptedNumText[i]-ExpandedNumKey[i]);
        }
        else
            NumDecrypt[i] = ( (EncryptedNumText[i]-ExpandedNumKey[i]) % 26);
        
    }
    return NumDecrypt;
}

int main() {
    
    string instruction;
    while(cin)
    {
        cout << "Enter 1 for Encryption, 2 for Decryption, 3 for printing Vigenere by rows, 4 for printing by columns, or 0 to exit:  ";
        getline(cin, instruction);
    
    if(instruction == "1")
    {
      vector<char> plaintext = GetPlaintext();
      vector<int> AsciiText = TransferToAscii(plaintext);
      vector<char> keyword = GetKeyword();
      vector <char> ExpandedKey = ExpandKeyword(plaintext, keyword);
      vector<int> ExpandedAsciiKeyword = TransferToAscii(ExpandedKey);
      vector<int> EncryptedNum = Encryption(ExpandedAsciiKeyword, AsciiText);
      vector<char> Encrypted = TransferToLetter(EncryptedNum);
      for(int i=0; i<Encrypted.size(); i++){
        cout << Encrypted[i];
      }
      cout << endl;
    }
    
    else if(instruction == "2")
    {
        vector<char> EncryptedText = GetPlaintext();
        vector<int> AsciiText = TransferToAscii(EncryptedText);
        vector<char> keyword = GetKeyword();
        vector<char> ExpandedKey = ExpandKeyword(EncryptedText, keyword);
        vector<int> ExpandAsciiKeyword = TransferToAscii(ExpandedKey);
        vector<int> DecryptedNum = Decryption(ExpandAsciiKeyword, AsciiText);
        vector<char> Decrypted = TransferToLetter(DecryptedNum);
        for(int i=0; i<Decrypted.size(); i++){
            cout << Decrypted[i];
        }
        cout << endl;
    }
    
    else if(instruction == "3")
    {
        PrintVigenereByRows();
    }
        
    else if(instruction == "4")
    {
        PrintVigenereByColumns();
    }

    else if(instruction == "0")
    {
        break;
    }
        
    }
    
    return 0;
}