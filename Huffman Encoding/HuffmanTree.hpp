/* Assignent 3
Names: Osama Bin Basit(Driver)  Chen-Yu Liu (Navigator)
Weight: 50 - 50
Unums: U39050886    U39755333
*/

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include "vector"
#include"map"
#include "stack"

class HuffmanTree : public HuffmanTreeBase {
  public:
  virtual std::string compress(const std::string inputStr);
  virtual std::string serializeTree() const;
  virtual std::string decompress(const std::string inputCode, const std::string serializedTree);

  //HeapQueue<HuffmanNode*, HuffmanNode::Compare> hq; 
  void encode(HuffmanNode* root, std::string str, std::map<char, std::string> &huffmanCode);  
  void printPostorder(HuffmanNode* temp) const;
  HuffmanNode* makeTree(const std::string s) const;
  std::string serializeHelper(HuffmanNode* node) const;  

  private:
    HuffmanNode* treeRoot;
    static std::string globalString;

};

#endif