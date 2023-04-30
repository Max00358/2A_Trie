#include <iostream>
#include <fstream>
#include <vector>

#include "Trie.hpp"
#include "TrieFunction.cpp"
using namespace std;

bool check_illegal(string input){
    const char* InputLetter = input.c_str();
    int valueCheck = 0;

    for(int i = 0; i < input.length(); i++){
        valueCheck = (int) InputLetter[i];
        if(valueCheck < 65 || valueCheck > 90){
            return true;
        }
    }
    return false;   //return false if no illegal argument detected
}
int main(){     //memory leak at line 24 and line 35
    string input;
    string textInput;
    Node* myTrie = new Node();
    ifstream text("corpus.txt");
    int count = 0;
    int totWord = 0;    //total words added in the Trie, initially zero, increment 1 when one word added, decrement one when one word erased

    while(cin>>input){
        if(input == "exit"){
            break;
        }
        if(input == "load"){
            while(text >> textInput){
                myTrie->insertWord(textInput, totWord);
            }
            cout << "success" << endl;
        }
        try{
            if(input == "i"){
                string insertWord;
                cin >> insertWord;

                if(check_illegal(insertWord) == true){
                    throw illegal_exception();
                }
                else{
                    myTrie->i_insert(insertWord, totWord);
                }
            }
        }
        catch(illegal_exception e1){
            cout << "illegal argument" << endl;
        }
        try{
            if(input == "c"){
                string prefix;
                cin >> prefix;
                int numCount = 0;

                if(check_illegal(prefix) == true){
                    throw illegal_exception();
                }
                else{
                    myTrie->outputSimilar(prefix, myTrie, numCount);
                }
            }
        }
        catch(illegal_exception e2){
            cout << "illegal argument" << endl;
        }
        try{
            if(input == "e"){
                string eraseWord;
                cin >> eraseWord;

                if(check_illegal(eraseWord) == true){
                    throw illegal_exception();
                }
                else{
                    myTrie->erase(eraseWord, totWord, myTrie);
                }
            }
        }
        catch(illegal_exception e3){
            cout << "illegal argument" << endl;
        }
        if(input == "p"){
            vector<char> store;
            myTrie->print(myTrie, store);

            for(int i = 0; i<26; i++){
                if(myTrie->children[i] != NULL){
                    cout << "" << endl;
                    break;
                }
            }
            //cout << "" << endl;
        }
        if(input == "spellcheck"){
            string wordCheck;
            cin >> wordCheck;
            myTrie->spellcheck(wordCheck);
            //cout << "" << endl;
        }
        if(input == "empty"){
            myTrie->checkEmpty(totWord);
        }
        if(input == "clear"){
            myTrie->clearAll(myTrie, totWord);
            cout << "success" << endl;
        }
        if(input == "size"){
            myTrie->size(totWord);
        }
    }
    delete myTrie;
    myTrie = NULL;
}