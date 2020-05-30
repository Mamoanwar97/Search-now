#ifndef TRIENODE_H
#define TRIENODE_H
#include <bits/stdc++.h>
#include <QString>
using namespace std;
class TrieNode
{
private:
    TrieNode* Child[26];
    bool End = 0 ;
    vector<pair<string,int>>DocRep;
public:
    TrieNode();
    vector<pair<string,int>> search(string Word);
    void Insert_Word(string Word,string docNum);
    void Insert_File(string File,string docNum);
    bool is_char(char x);
};

#endif // TRIENODE_H


