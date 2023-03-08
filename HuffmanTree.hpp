
#ifndef HUFFMANTREE_HPP
#define HUFFMANTREE_HPP

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>

class HuffmanTree : HuffmanTreeBase {
private:
size_t n;
HuffmanNode* root;
public:
std::string compress(const std::string inputStr) override;
std::string serializeTree() const override;
std::string decompress(const std::string inputCode, const std::string serializedTree) override;
void find(const HuffmanNode* m, std::map<char, std::string>& map2, std::string c);
void serialization(const HuffmanNode* node, std::string& outString) const;
};

#endif /*HUFFMANTREE_HPP*/
