#include <cstdlib>
#include <iostream>
#include <string>
#include "algorithms.hpp"
#include "fifo.hpp"
#include "lru.hpp"
#include "segmented-fifo.hpp"

int main(int argc, char* argv[]){
    
    std::queue<int> pageTable; //for FIFO
    std::set<int> visited; //for FIFO
    std::map<int,int> lruMp; //for LRU
    std::map<int,int> write;  //to store if address was overwritten
    int diskRead=0, diskWrite =0;    

    std::string addr;
    char rw; int traceCount = 0;
    std::string fileName = argv[1];
    std::ifstream f(fileName);
    
    int tableSize = atoi(argv[2]);
    char replacementAlgorithm = argv[3][0];
    char mode = argv[4][0];
    int p;
    if(replacementAlgorithm=='v'){
        p = atoi(argv[4
        ]);
        mode = argv[5][0];
    }
    
    std::cout<<"Replacement Algorithm: " << argv[3]<<std::endl;
    while ( !f.eof())
    {
        f >> addr;
        f >> rw;
    
        switch(replacementAlgorithm){
            case 'f':
                fifo(getPageNumber(addr), rw,pageTable,tableSize, visited, diskRead, diskWrite, write);
                break;
            case 'l':
                lru(getPageNumber(addr), rw, tableSize, lruMp, diskRead, diskWrite, write);
                break;
            case 'v':
                sfifo(getPageNumber(addr),rw, pageTable, tableSize, p, visited, lruMp, diskRead, diskWrite, write);
        }

        traceCount++;

        if(mode=='d'){
            std::cout<<"For address: "<< addr<<std::endl;
            std::cout<<"Frames     : " << tableSize <<std::endl;
            std::cout<<"Trace Count: " << traceCount <<std::endl;
            std::cout<<"Read Count : " << diskRead << std::endl;
            std::cout<<"Write Count: " << diskWrite << std::endl;
            std::cout<<std::endl;
        } 
        

    } 
    
    if(mode=='q'){
        std::cout<<"Frames     : " << tableSize << std::endl;
        std::cout<<"Trace Count: " << traceCount << std::endl;
        std::cout<<"Read Count : " << diskRead << std::endl;
        std::cout<<"Write Count: " << diskWrite << std::endl;
    }

    return 0;
}
