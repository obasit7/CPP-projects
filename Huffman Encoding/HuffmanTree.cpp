/* Assignent 3
Names: Osama Bin Basit(Driver)  Chen-Yu Liu (Navigator)
Weight: 50 - 50
Unums: U39050886    U39755333
*/
#include "HuffmanTree.hpp"
#include <map>

//function to convert string to 1's and 0's
std::string HuffmanTree::compress(const std::string inputStr){
    std::string output="";
    std::map<char, int> mp; //map of char and int to store character and its frequency
    for(size_t i=0;i<inputStr.size();i++){
        mp[inputStr[i]]++; //add characters to map and increment frequency
    }
    
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> hq; //create heap to store nodes from map  

    //iterates over map, makes node from character and frequency. Then puts it into queue that sorts itself
    for(auto it = mp.begin(); it != mp.end(); it++){
        HuffmanNode* hn = new HuffmanNode(it->first,it->second);
        hq.insert(hn);
    }
    
    //MAKE TREE until only 1 node remains in the heap
    while(hq.size()>1){
        //store freq and char of smallest node
        HuffmanNode* fNode = hq.min();
        hq.removeMin();
        //store freq and char of second smallest node
        HuffmanNode* sNode = hq.min();
        hq.removeMin();
        
        //calculate new freq of new node
        size_t newFreq = fNode->getFrequency()+sNode->getFrequency();
        //make new node with \ char and extracted nodes as children
        HuffmanNode* newNode = new HuffmanNode('\0',newFreq,nullptr,fNode,sNode);
        fNode->parent=sNode->parent=newNode;
        //INSERT FORMED TREE BACK TO HEAP
        hq.insert(newNode);
    }

    std::map<char, std::string> encodeMp; //another map to store character and encoded string

    //set tree stored in queue as treeRoot
    treeRoot = hq.min();

    std::string testStr="";
    encode(treeRoot,testStr,encodeMp); //call to helper function 
    //construct complete string of encoded letters
    for(size_t i=0; i<inputStr.size();i++){
        output = output+encodeMp[inputStr[i]];
    }

    return output;
}

void HuffmanTree::printPostorder(HuffmanNode* temp) const{
    if (temp == NULL)
        return;
 
    // first recur on left subtree
    printPostorder(temp->left);
 
    // then recur on right subtree
    printPostorder(temp->right);
 
    // now deal with the node
    std::cout << temp->getCharacter() << " - "<<temp->getFrequency()<<std::endl;
}

//function that recursively traverses through tree and sets 0's and 1's
void HuffmanTree::encode(HuffmanNode* root, std::string str, std::map<char, std::string> &huffmanCode){
    if (root == nullptr)
		return;
    //if leaf, store constructed string with associated character in map
    if(root->isLeaf()){
        huffmanCode[root->getCharacter()] = str;
    }
    //if not leaf, visit left nodes and then right nodes
    encode(root->left, str + "0", huffmanCode); //add 0 if left node
    encode(root->right, str + "1", huffmanCode); //add 1 to string if right node
}

std::string HuffmanTree::globalString="";

std::string HuffmanTree::serializeTree() const{
    globalString="";
    return serializeHelper(treeRoot); //call to helper function
}

std::string HuffmanTree::serializeHelper(HuffmanNode* node)const{
    if (node == NULL)
        return globalString+"";
    //recursively visits left nodes first and then right nodes
    serializeHelper(node->left);
    serializeHelper(node->right);
    //if node is branch, add B to string
    if(node->isBranch()){
        globalString=globalString+"B";
    }
    //if node is leaf, add L and next char to string
    if(node->isLeaf()){
        globalString=globalString+"L"+node->getCharacter();
    }
    return globalString;
}

std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree){
    std::string decompressedString="";
    HuffmanNode* serializedTreeRoot = makeTree(serializedTree); //helper function helps to make tree
    HuffmanNode* follow = serializedTreeRoot;
    //read string and check with constructd tree
    std::string::const_iterator i;
    for(i=inputCode.begin();i!=inputCode.end();i++){
        //if 0, move to left of tree
        if(*i=='0'){
            follow = follow->left;
        }
        else{ //if char is 1
            follow = follow->right;
        }
        //if its a leaf, add character fro tree to string
        if(follow->isLeaf()){
                decompressedString = decompressedString+ follow->getCharacter();
                follow = serializedTreeRoot;
            }
    }
    
    return decompressedString;
}

HuffmanNode* HuffmanTree::makeTree(const std::string s) const{
    std::stack<HuffmanNode*> treeStack; //create stack to store nodes
    std::string::const_iterator i;
    for(i=s.begin();i!=s.end();i++){
        //std::cout<<"INSIDE MKTREE"<<std::endl;
        if(*i =='L'){ //if leaf, add to stack
            i++;
            HuffmanNode* nodeToInsert = new HuffmanNode(*i,0);
            treeStack.push(nodeToInsert);
        }
        else{ //if B, pop top 2 stored in stack
            HuffmanNode* rightNode = treeStack.top();
            treeStack.pop();
            HuffmanNode* leftNode = treeStack.top();
            treeStack.pop();
            int newF= rightNode->getFrequency()+leftNode->getFrequency();
            //make new node with popped nodes as children and insert back to stack
            HuffmanNode* parentNode = new HuffmanNode('\0',newF,nullptr,leftNode,rightNode);
            // leftNode->parent=parentNode;
            // rightNode->parent=parentNode;
            treeStack.push(parentNode);
        }

    }
    return treeStack.top();
}
/*
int main(){
    HuffmanTree T;
    using namespace std;
    string test1 = "Osama Bin Basit";
    string test2 = "ce  bbbaaa";

    string test3 = "if a machine is expected to be infallible it cannot also be intelligent";
    string testWord = "It is time to unmask the computing community as a Secret Society for the Creation and Preservation of Artificial Complexity";
    string constit = "We the People of the United States, in Order to form a more perfect Union, establish Justice, insure domestic Tranquility, provide for the common defence, promote the general Welfare, and secure the Blessings of Liberty to ourselves and our Posterity, do ordain and establish this Constitution for the United States of America. Article 1.  Section 1 All legislative Powers herein granted shall be vested in a Congress of the United States, which shall consist of a Senate and House of Representatives.  Section 2 The House";

    string compareStr = "0110101100101100010011101111000010010011111010000011101000010001010101010010011000111110001000000111111001001010110000011111001011101111011101011101011101100000111111001100010111110111011001111100101111011010011001001010110000011111011111001101110101101000110011101111";
    string compareWord = "1000101011110000101001100110000010111011001110111101111100011001001011010010000111100111001001110110111101011001010101011111001100000111000010110111101011001000101111100011000011111111110010110100110010111010011111101111001001110011110100111101111110000111001111111111010101110110100110011100100111011010011001001110010101100010110011110010100111000001110100000001001110101001110010010001100101011000101100111101011101011110100010001000110001010110001111000001011001011101001101011001010101010010111101000111000011111111";
    string serializeAsnwer= "LiLmLnBBLrLaBLtBBLPLdBLgLkBBLALIBLvLxBBBLhLlBLCLSBBBLsLpLfBBLoBBL LeLcLuLyBBBBBB";

    string code = T.compress(constit);
    string tree = T.serializeTree();
    if(code==compareWord){
        cout<<"ENCODED STRINGS ARE THE SAME"<<endl;
    }
    if(tree==serializeAsnwer){
        cout<<"SERIALIZE ANSWERS ARE THE SAME!"<<endl;
    }
    std::string ds = T.decompress(code,tree);
    cout<<ds<<endl;
    if(ds == testWord){
        cout<<"DECOMPRESSED STRING IS THE RIGHT STRING! YOU DID IT!!!!!!";
    }
    return 0;
}
*/