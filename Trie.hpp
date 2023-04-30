#ifndef _TRIE_HPP_
#define _TRIE_HPP_
#include <iostream>
#include <exception>
using namespace std;

class illegal_exception{ // : public exception

};

class Node{
public:
    Node* children[26];
    //bool isEnd;     //the end of one word, doesn't mean the end of the branch
    //bool isMore;    //end of one letter doesn't mean end of the branch, might have continuation afterwards
    int index;
    string val;

    Node(){
        this->isEnd = false;
        this->isMore = false;
        this->val = "";

        for(int i = 0; i<26; i++){
            this->children[i] = NULL;
        }
    }
    ~Node();

    bool get_end(){
        return this->isEnd;
    }
    void set_end(bool val){
        this->isEnd = val;
        return;
    }
    bool get_more(){
        return this->isMore;
    }
    void set_more(bool val){
        this->isMore = val;
        return;
    }

    bool hasChildren(Node* temp);
    int numChildren(Node* temp);
    void insertWord(string textInput, int &totWord);
    void i_insert(string word, int &totWord);
    void c_helper(string prefix, Node* temp, int &num);
    void outputSimilar(string prefix, Node* temp, int &numCount);
    bool findWord(string word);
    void erase(string word, int &totWord, Node* temp);
    void print(Node* temp, vector<char> &store);
    void printSimilar(vector<char> prefix, vector<char> &addOnPrefix, Node* temp);
    void spellcheck(string word);
    void checkEmpty(int totWord);
    void clearAll(Node* temp, int &totWord);
    void size(int totWord);

private:
    bool isEnd;     //the end of one word, doesn't mean the end of the branch
    bool isMore;    //end of one letter doesn't mean end of the branch, might have continuation afterwards
};
#endif