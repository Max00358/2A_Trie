#include <iostream>
#include "Trie.hpp"
using namespace std;

Node::~Node(){
    for(int i = 0; i < 26; i++){
        delete children[i];
        children[i] = NULL;
    }
}
bool Node::hasChildren(Node* temp){
    for(int i = 0; i < 26; i++){
        if(temp->children[i] != NULL){
            return true;
        }
    }
    return false;
}
int Node::numChildren(Node* temp){
    int numChildren = 0;
    if(hasChildren(temp) == true){
        for(int i = 0; i < 26; i++){
            if(temp->children[i] != NULL){
                numChildren++;
            }
        }
    }
    return numChildren;
}
void Node::insertWord(string textInput, int &totWord){
    Node* temp = this;
    int index;
    const char* InputLetter = textInput.c_str();  //copy string textInput into char array

    if(findWord(textInput) == true){
        return;
    }
    for(int i = 0; i < textInput.length(); i++){
        index = (int) InputLetter[i] - 'A';
        if(temp->children[index] == NULL){
            Node* newLetter = new Node();
            temp->children[index] = newLetter;
            newLetter->index = index;
            newLetter = NULL;
        }
        else if(temp->children[index]->get_end() == true && i < textInput.length()-1){//if we see a node that has isEnd to true while we are in insertion, then set inMore to true
            temp->children[index]->set_more(true);
        }
        temp = temp->children[index];
    }

    temp->set_end(true);
    if(hasChildren(temp) == true){
        temp->set_more(true); //temp->isMore = true;
    }
    else{
        temp->set_more(true); //temp->isMore = false;
    }
    totWord++;
    return;
}
void Node::i_insert(string word, int &totWord){
    Node* temp = this;
    const char* InputLetter = word.c_str();
    int countRepeat = 0;
    int index = 0;

    if(findWord(word) == true){    //if the word is already in Trie, then output failure
        cout << "failure" << endl;
        return;
    }
    for(int i = 0; i < word.length(); i++){
        index = (int) InputLetter[i] - 'A';
        if(temp->children[index] == NULL){
            Node* newLetter = new Node();
            temp->children[index] = newLetter;
            newLetter->index = index;
            newLetter = NULL;
        }
        else if(temp->children[index]->get_end() == true && i < word.length()-1){ //word.length()-1 means we have more letters to add
            temp->children[index]->set_more(true); //temp->children[index]->isMore = true;
            //cout << to_string(index + 'A') << endl;
        }
        temp = temp->children[index];
    }

    temp->set_end(true); //temp->isEnd = true;
    if(hasChildren(temp) == true){
        temp->set_more(true); //temp->isMore = true;
    }
    else{
        temp->set_more(false); //temp->isMore = false;
    }
    totWord++;
    cout << "success" << endl; //if insertion is successful
    return;
}
void Node::c_helper(string prefix, Node* temp, int &num){
    if(temp == NULL){
        return;
    }
    else if(temp != NULL){
        if(temp->get_end() == true){    //temp->isEnd == true
            num++;
            if(temp->get_more() == false){  //temp->isMore == false
                return;
            }
        }
        for(int i = 0; i < 26; i++){
            c_helper(prefix, temp->children[i], num);
        }
    }
}
void Node::outputSimilar(string prefix, Node* temp, int &num){
    const char* InputLetter = prefix.c_str();
    int index;
    
    for(int i = 0; i<prefix.length(); i++){
        index = (int) InputLetter[i] - 'A';
        if(temp->children[index] == NULL){
            cout << "not found" << endl; //if any letter of the prefix is never inserted, then we say it's not found
            return;
        }
        //cout << (char) (index + 'A')<< endl;
        temp = temp->children[index];
    }
    c_helper(prefix, temp, num);
    cout << "count is " + to_string(num) << endl;
    return;
}
bool Node::findWord(string word){   //helper function for erase
    const char* InputLetter = word.c_str();
    Node* temp = this;
    int index;
    int count = 0;

    for(int i = 0; i < word.length(); i++){
        index = (int) InputLetter[i] - 'A';
        if(temp->children[index] == NULL){
            return false;
        }
        temp = temp->children[index];
    }
    if(temp->get_end() == true){    //temp->isEnd == true
        return true;
    }
    return false;
}
void Node::erase(string word, int &totWord, Node* temp){
    if(totWord == 0 || findWord(word) == false){    //trie is empty or word not found
        cout << "failure" << endl;
        return;
    }
    else{
        vector<Node*> store;
        int countEnd = 0;
        
        for(int i = 0; i < word.length(); i++){ //push the word to be deleted into the vector
            int index = (int) word[i] - 'A';
            store.push_back(temp->children[index]);
            temp = temp->children[index];
        }

        //this is for the case where word to be delete is included in other words
        Node * current = store[store.size()-1];
        if(current->get_end() == true && numChildren(current) > 0){ //current->isEnd == true
            current->set_end(false); //current->isEnd = false;
            totWord--;
            cout << "success" << endl;
            return;
        }
        //stop deletion condition: if parent has termintion condition (isEnd) OR parent has more than one children
        for(int i = store.size()-1; i >= 0; i--){ 
            if(i >= 1){
                //store[i-1]->isEnd == true
                if(store[i-1]->get_end() == true || numChildren(store[i-1]) > 1){   //if parent node is the end of another word OR parent has more than one child, end deletion
                    int newIndex = store[i]->index;
                    Node* tempNull = store[i-1]->children[newIndex]; 
                    delete tempNull;
                    store[i-1]->children[newIndex] = NULL;  //need to store store[i]->index in newIndex because store[i]->index cannot be accessed after deletion
                    break;
                }
                else if(numChildren(store[i]) == 0){
                    int newIndex = store[i]->index;
                    Node* tempNull = store[i-1]->children[newIndex];
                    delete tempNull;
                    store[i-1]->children[newIndex] = NULL;
                }
            }
            else if(numChildren(store[i]) == 0 && i == 0){
                int newIndex = store[i]->index;
                Node* tempNull = this->children[newIndex];
                delete tempNull;
                this->children[newIndex] = NULL;
            }
        }
    }
    totWord--;
    cout << "success" << endl;
    return;
}
void Node::print(Node* temp, vector<char> &store){
    if(temp == NULL){
        return;
    }
    else if(temp->get_end() == true){   //temp->isEnd == true
        for(int i = 0; i < store.size(); i++){  //print out vector content
            cout << store[i];
        }
        cout << " ";
    }
    for(int i = 0; i<26; i++){
        if(temp->children[i] != NULL){
            char letter = (char) (i + 'A');
            store.push_back(letter);
            print(temp->children[i], store);
            store.pop_back();
        }
    }
}
void Node::printSimilar(vector<char> originPrefix, vector<char> &addOnPrefix, Node* temp){  //helper function for spellcheck
    if(temp == NULL){
        return;
    }
    else if(temp->get_end() == true){   //temp->isEnd == true
        for(int i = 0; i<originPrefix.size(); i++){
            cout << originPrefix[i];
        }
        for(int j = 0; j<addOnPrefix.size(); j++){
            cout << addOnPrefix[j];
        }
        cout << " ";
    }
    //The idea is to have an original prefix and add-on prefix to do the job of printing these letters
    for(int i = 0; i < 26; i++){
        if(temp->children[i] != NULL){
            char letter = (char) (i + 'A');
            addOnPrefix.push_back(letter);
            printSimilar(originPrefix, addOnPrefix, temp->children[i]);
            addOnPrefix.pop_back();
        }
    }
    return;
}
void Node::spellcheck(string word){
    const char* InputLetter = word.c_str();
    Node* temp = this;
    int index;
    vector<char> prefix;
    vector<char> addOnPrefix;

    if(findWord(word) == true){
        cout << "correct" << endl;;
        return;
    }
    index = (int) InputLetter[0] - 'A';
    if(this->children[index] == NULL){
        cout << "\n";    //if no word start with that first letter, then produce no output other than a new line
        return;
    }
    else{
        for(int i = 0; i < word.length(); i++){
            //cout << "1" << endl;
            index = (int) InputLetter[i] - 'A';
            if(temp->children[index] != NULL){
                //cout << "2" << endl;
                char letter = (char) (index + 'A');
                prefix.push_back(letter);
            }
            if(temp->children[index] == NULL || i == word.length()-1){    //when the letter is not inserted, that letter is misspelled, we have gathered all letters for prefix
                //cout << "3" << endl;
                if(temp->children[index] != NULL){
                    temp = temp->children[index];
                }
                printSimilar(prefix, addOnPrefix, temp);
            }

            if(temp->children[index] == NULL){
                //cout << "4" << endl;
                break;
            }
            else{
                //cout << "5" << endl;
                temp = temp->children[index];
            }
        }
        cout << "" << endl;
    }
}
void Node::checkEmpty(int totWord){
    if(totWord == 0){
        cout << "empty 1" << endl;  //empty 0 if trie is empty
    }
    else{
        cout << "empty 0" << endl;  //empty 0 if trie not empty
    }
    return;
}
void Node::clearAll(Node* temp, int &totWord){
    if(temp == NULL){
        return;
    }
    else{
        for(int i = 0; i<26; i++){
            //if(temp->children[i] != NULL){ 
            clearAll(temp->children[i], totWord);
            //}
            delete temp->children[i];
            temp->children[i] = NULL;
        }
    }
    totWord = 0;
    return;
}
void Node::size(int totWord){
    cout << "number of words is " + to_string(totWord) << endl;
    return;
}