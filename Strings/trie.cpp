/*
    Trie Implementation for finding the smallest prefix not matching any words
    from dictionary.

    TC: 
        Insert: O(n * L), L:longest string length in dict, n: no. of words in dictionary
        findShortestPrefix: 
            O(min(m, L)), L: longest dict word, m: length of query word
        
*/

#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

class Trie {
private:
    struct TrieNode {
        bool isString = false;
        unordered_map<char, unique_ptr<TrieNode>> leaves;
    };

    unique_ptr<TrieNode> root_ = make_unique<TrieNode>(TrieNode());

public:
    // Inserts a string in Trie
    bool Insert(string& str) {
        
        // get the Tree root
        TrieNode* root = root_.get();
        for (const auto c : str) {
            // if node is there with this char, create one
            if (root->leaves.find(c) == root->leaves.end()) {
                root->leaves.emplace(c, make_unique<TrieNode>(TrieNode()));
            }
            // go further down through via the child nodes
            root = root->leaves[c].get();
        }

        // if the string was already present, we didn't do any insertion
        if (root->isString == true)
            return false;
        else {  // string was inserted successfully
            root->isString = true;
            return true;
        }
    }

    // finds the shortest prefix not part of dictionary set for
    // a given string
    string findShortestPrefix(string& str, unordered_set<string>& dict) {
        string prefix;

        TrieNode* root = root_.get();
        // we will look for the first character for which there is no node
        // in Trie
        for (const auto& c : str) {
            prefix += c;

            if (root->leaves.find(c) == root->leaves.end()) {
                return prefix;
            }
            root = root->leaves[c].get();
        }
        return "";
    }
};


int main() {
    Trie trie;
    string str = "army";
    unordered_set<string> dict = { "arm", "cat", "piano", "germ"};

    for (string word : dict)
        trie.Insert(word);
    
    cout << trie.findShortestPrefix(str, dict);
    return 0;
}
