# 2A_Trie
Spellchecking using Trie ADT

In this project, a trie ADT is used to implement a spell-checker. This program should take in a text document containing paragraphs of words, which you may assume are correctly spelled. The program then input this data into the trie. Your trie may not contain duplicate words, so this must be accounted for when you are parsing the document. You will also implement code to use, manipulate, and analyze the trie.

**Command/Allowed user inputs**: 
   
   **load**:Load the .txt file into the trie, ensuring that duplicate words are not added. You should do this by opening the file and reading it one word at a time. In the corpus, a “word” is separated from other words by whitespace.
   
   **i (for insertion)**: Insert a new word into the trie.
   
   **c (for finding common prefix of multiple inputs)**: Outputs a count of all words in the trie that have the given prefix. The prefix does not need to be a full word in the trie, although it may be. For example, if the Trie contains the words “CAR”, “CARD”, and “CARMEN” only, then searching for the prefix CA should return a count of 3, as should searching for the prefix CAR.
   
   **e (for erase)**: Erase the word in the trie.
   
   **p (for print)**: Prints all words in the trie in alphabetical order on a single line (use depth-first traversal).
   
   **spellcheck**: Spell-checks the word or offers suggestions if the word is not spelled correctly.
For example, assume the trie contains the words: YOU, YOUN, YOUNG, YOUR.
The command: spellcheck YOL will print a list of all words in the trie starting with “YO”. It should print this list alphabetically.

   **empty**: Checks if the trie is empty.
   
   **clear**: Deletes all words from the trie.
   
   **size**: Prints a message indicating the number of words in the trie.
   
   **exit**: Last command for all input files.

