#include "trienode.h"

TrieNode::TrieNode()
{
    this->End=0;
    for(int i=0 ; i<26 ; i++)
        this->Child[i]=nullptr;
}

bool TrieNode::is_char(char x)
{
    if((x>=65&&x<=90)||(x>=97&&x<=122))
            return 1;
        return 0;
}


vector<pair<string,int>> TrieNode::search(string Word)
{
    vector<pair<string,int>>RepWords;
    TrieNode* curr = this;
    if (curr == nullptr)
        return RepWords;
    for (uint i = 0; i < Word.length(); i++)
    {
        char temp = Word[i] ;
        if(temp < 97)
            temp += 32;
        temp -= 'a';
        curr = curr->Child[temp];
        if (curr == nullptr)
            return RepWords;
    }
    if(curr->End==1)
        return curr->DocRep;
    else
        return RepWords;
}

void TrieNode::Insert_Word(string Word,string docNum)
{
    TrieNode* curr = this;
    for (uint i = 0; i < Word.length(); i++)
    {
        char chara = Word[i] ;
        if(chara < 97)
            chara += 32;
        chara -= 'a';
        if ( curr->Child[chara] == nullptr)
            curr->Child[chara] = new TrieNode();
        curr = curr->Child[chara];
     }
    curr->End = 1;
    uint i ;
    for(i=0 ; i<curr->DocRep.size();i++)
    {
        if(curr->DocRep[i].first==docNum)
        {
            curr->DocRep[i].second++;
            return;
        }
    }
    curr->DocRep.push_back(pair<string,int>(docNum,1));
}
void TrieNode::Insert_File(string File,string docNum)
{
    File += " ";
    while(File.length())
    {
        string sent =File.substr(0,File.find(" "));
        int i=0;
        while(sent[i]!='\0')//loop to remove any strange char
        {
            if(!is_char(sent[i]))
            {
               sent.erase(sent.begin()+i);
               i--;//3shan el lenght bta3 el kelma bey2el f momken ye3ady 7arf lma a3mel i++ ba3d keda
             }
                 ++i;
         }
         if(sent.length()!=0)
         {
          Insert_Word(sent,docNum);
         }
        File.erase(0,File.find(" ")+1);
    }

}
