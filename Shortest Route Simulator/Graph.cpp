/*
    Names: Osama Bin Basit(driver) and Chen-Yu Liu(navigator)
    ID:    U39050886                   U39755333
    Weight:             50 -- 50
*/
#include <iostream>
#include "Graph.hpp"

void Graph::addVertex(std::string label){    
    //add vetex with label to adjacency list
    mpList[label];
}

void Graph::removeVertex(std::string label){
    //remove all occurrences of label where it is an edge in the adjacency list
    for(auto key : mpList)
        for(auto edge:key.second)
            if(edge.first == label)
                removeEdge(key.first,label);
    //remove the key for label       
    mpList.erase(label);
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight){
    //make a pair of label name and its weight for both keys
    auto p1 = std::pair<std::string,int>(label2,weight);
    mpList[label1].insert(p1); //adding label 2 as edge of label 1
    auto p2 = std::pair<std::string,int>(label1,weight);
    mpList[label2].insert(p2); //adding label 1 as edge of vertex label 2
}

void Graph::removeEdge(std::string label1, std::string label2){
    //removing label 2 as edge of label 1 and vice versa
    mpList[label1].erase(label2);
    mpList[label2].erase(label1);
}

//helper function to test code by printing the adjacency list for graph
void Graph::printList(){
    for(auto strKey : mpList){
        std::cout<<strKey.first<<": ";
        for(auto edge : strKey.second)
            std::cout<<edge.first<<"/"<<edge.second<<" ";
        
        std::cout<<std::endl;
    }
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){
    std::map<std::string, unsigned long> distanceList;
    std::set<std::pair<unsigned long,std::string>> s; //declaring a set of pair values
    std::map<std::string, std::string> pathTree;   

    //initialize all distances of vertices to INF(1000)
    for(auto vertex: mpList)
        distanceList[vertex.first] = INF;
       
    //set distance of startLabel to 0 and insert in set of pairs
    distanceList[startLabel]=0;
    pathTree[startLabel]="src";

    //path.push_back(startLabel);
    s.insert(std::make_pair(0,startLabel));

    while(!s.empty()){
        //find pair values at front
        auto p = *(s.begin());
        std::string front = p.second;
        unsigned long d = p.first;
        //remove pair from set
        s.erase(s.begin());

        //iterate over each adjacent vertex of current vertex
        for(auto adjVertex: mpList[front]){
            //check if distance of vertex from parent vertex is less than distance of vertex in distances array
            //update if true
            if(d+adjVertex.second < distanceList[adjVertex.first]){
                pathTree[adjVertex.first] = front;
                
                //add updated pair of values to set
                distanceList[adjVertex.first]=d+adjVertex.second;
                s.insert(std::make_pair(distanceList[adjVertex.first],adjVertex.first));
            }
        }
    }

    std::vector<std::string> route;
    route.push_back(startLabel);
    addPath(endLabel,route, pathTree);
    path = route;
    route.clear();
    return distanceList[endLabel];

}

//recursive function to add the vertices visited to reach destination in path vector
void Graph::addPath(std::string label, std::vector<std::string> &path, std::map<std::string, std::string> pathTree ){
    if(pathTree[label]=="src")
        return;
    
    addPath(pathTree[label],path,pathTree);
    path.push_back(label);
}


/*
int main(){
    Graph g;
    g.addVertex("BSN");
    g.addVertex("LIB");
    g.addVertex("ENB");
    g.addVertex("MSC");
    g.addVertex("CAS");
    g.addVertex("SUB");
    g.addVertex("SUN");
    //g.removeVertex("B");
    
   // g.printList();
    g.addEdge("BSN","LIB", 871);
    g.addEdge("BSN","CAS", 1672);
    g.addEdge("BSN","MSC", 2355);
    g.addEdge("SUN","SUB", 1265);
    g.addEdge("LIB","MSC", 1615);
    g.addEdge("LIB","SUN", 1847);
    g.addEdge("ENB","SUN", 2885);
    g.addEdge("ENB","CAS", 454);
    g.addEdge("ENB","LIB", 1078);
    std::vector<std::string>path;
    
    //g.removeEdge("D","A");
    g.printList();
    std::cout<<g.shortestPath("ENB","SUN",path);
    std::cout<<std::endl;

    //g.removeVertex("4");
    // g.removeEdge("4","5");
    // g.removeVertex("3");
    //g.printList();
    //std::cout<<g.shortestPath("5","2",path);
    std::cout<<std::endl;
    
    //std::cout<<g.shortestPath("5","2",path);
    // std::cout<<std::endl;
    for(auto node:path){
        std::cout<<node<<" -> ";
    }
    // std::cout<<"\n"<<path.size();
}
*/