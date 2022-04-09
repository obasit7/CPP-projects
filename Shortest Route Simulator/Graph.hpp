
/*
    Names: Osama Bin Basit(driver) and Chen-Yu Liu(navigator)
    ID:    U39050886                   U39755333
    Weight:             50 -- 50
*/
#include <iostream>
#include<stdio.h>
#include<map>
#include<set>
#include "GraphBase.hpp"

#define INF 10000; //defining a value for infinity

class Graph: public GraphBase{
    private:
    //adj List stored in a map of pair values string and map of string and weight
    std::map<std::string, std::map<std::string,int>> mpList; 
    
public:
// 2 helper functions to print adj list and add to vector path
    void printList();
    void addPath(std
    ::string label,std::vector<std::string> &path, std::map<std::string, std::string> pathTree);

    void addVertex(std::string label);
    void removeVertex(std::string label);
    void addEdge(std::string label1, std::string label2, unsigned long weight);
    void removeEdge(std::string label1, std::string label2);
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
};