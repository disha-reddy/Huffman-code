/*
    Program Name:   Huffman Code Generator
    Authors:        Iman Abu-Khdair (navigator), Disha Reddy Anugu (driver)
    Purpose:        to take in a string of input, use an algorithm that will convert the
                    code for each character into compressed binary form based on the frequency
                    in the string provided. This will be done through the use of priority
                    queues, maps, and the traversal of a constructed tree. There will also be
                    the serialization of each character, as well as the decompression of the
                    new string into the original one.

*/

#include "HuffmanTree.hpp"
#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>
#include <iostream>
#include <stack>

void HuffmanTree::find(const HuffmanNode* m, std::map<char, std::string>& map2, std::string c) {
    if (m == nullptr){
        return;
    }

    if(m->isLeaf()) {
        map2[m->getCharacter()] = c;
    }

    
    find(m->right, map2, c + "1");
    find(m->left, map2, c + "0");

}

std::string HuffmanTree::compress(const std::string inputStr) {
    
    size_t count[256] = {0};
    std::map<char, size_t>::iterator p;
    std::map<char, size_t> map1;

    //count their frequencies by read characters from input string and storing those frequencies in the array.
    int i = 0;
    while (inputStr[i] != '\0') {
        count[inputStr[i]]++;
        i++;
    }
    int j = 0;
    while(j < 256) {
        if(count[j] != 0){
            map1.insert(std::pair<char,size_t>((char)j, count[j]));
        }
        j++;
    }

//creating Heap Priority Queue
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> q;
    p = map1.begin();
    while (p != map1.end()) {
        HuffmanNode* m = new HuffmanNode(p->first, p->second);
        n++;
        q.insert(m);
        ++p;
    }

//creating huffman tree
    while (q.size() != 1){
        size_t parentFreq;
        HuffmanNode* n1 = q.min();
        q.removeMin();
        HuffmanNode* n2 = q.min();
        q.removeMin();
        parentFreq = (n1->getFrequency() + n2->getFrequency());
        HuffmanNode* parent12 = new HuffmanNode('\0', parentFreq, nullptr, n1, n2);
        n1->parent = parent12;
        n2->parent = parent12;
        q.insert(parent12);
    }
    root = q.min();

    //mapping each character for the huffman coding
    std::string result = "";
    std::map<char, std::string> map2;
    std::string c = "";

    p = map1.begin();
    while ( p != map1.end()) {
        find(q.min(), map2, c);
        ++p;
    }
  
    for (auto i : inputStr) {
        result += map2[i];
    }
    return result;
}
//if the node m encounters branch then will print "B" and prints "L" if it encounters leaf(which has no left or right node)
void HuffmanTree::serialization(const HuffmanNode* m, std::string& outChar) const {
    if (m == nullptr) {
        return;
    }
  
    serialization(m->left, outChar);
    serialization(m->right, outChar);

    if (m->isBranch()){
        outChar += "B";
    }
    else if (m->isLeaf()){
        outChar = outChar + "L" + m->getCharacter();
    }
}

//serializing the huffman tree
std::string HuffmanTree::serializeTree() const {
    std::string result = "";
    if (root == nullptr) {
        return "";
    }

    serialization(root, result);
    return result;
}

//get the result from the serializetree and use that for decompressing the code
std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) {
    
    //size_t length = serializedTree.length();
    std::stack<HuffmanNode*> tree_stack;

//building the code again from the serialized tree
    for(auto letter : serializedTree) {
        if ((letter != 'L') && (letter != 'B')) {
            HuffmanNode* node = new HuffmanNode(letter, 0);
            tree_stack.push(node);
        }
        
        else if (letter == 'B') {
            HuffmanNode* rightnode = tree_stack.top();
            tree_stack.pop();
            HuffmanNode* leftnode = tree_stack.top();
            tree_stack.pop();
            
            HuffmanNode* branch1 = new HuffmanNode('\0', 0, nullptr, leftnode, rightnode);
            tree_stack.push(branch1);
            rightnode->parent = branch1;
            leftnode->parent = branch1;
        }
        
        else if (letter == 'L') {
            continue;
        }
    }

    //once if hits leaf the remanining stack will be the root of the newly constructed tree and clears the stack
    HuffmanNode* root = tree_stack.top();
    tree_stack.pop();

//Using the generated huffman tree to recreate the text from the code
    std::string result = "";
    HuffmanNode* currentnode = root;
    for (auto character : inputCode) {
        if (character != '0')
            currentnode = currentnode->right;
        else
            currentnode = currentnode->left;

//Once you've reached the leaf, add the char to output and restart from the beginning.
        if (currentnode->isLeaf()) {
            result += currentnode->getCharacter();
            currentnode = root;
        }
    }
    return result;
}
