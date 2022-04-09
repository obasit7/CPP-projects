#include "segmented-fifo.hpp"
#include "fifo.hpp"
#include "lru.hpp"

void sfifo(int val, char rw, std::queue<int> &pt, int cap, int percentage, std::set<int> &mp, std::map<int,int> &secondaryBuffer, int &f, int &h, std::map<int,int> &write){
    if(percentage==0){fifo(val,rw,pt,cap,mp,f,h,write); return;}
    if(percentage==100){lru(val,rw,cap,secondaryBuffer,f,h,write); return;}

    if(write.find(val)==write.end()){
        write[val]==0;
    }
    if(rw=='W'){
        write[val]=1;
    }

    int cap2 = (cap * percentage)/100;
    int cap1 = cap - cap2;

    if(pt.size()!=cap1){//primary is not full and val not in primary
        if(mp.find(val)==mp.end()){
            pt.push(val);
            mp.insert(val);
            f++;
        }
        //else{}
    }
    
    else if(pt.size()==cap1 && mp.find(val)==mp.end() && secondaryBuffer.find(val)==secondaryBuffer.end()){//p1 is full and val not in p1 or p2
        int move = pt.front(); //moving front of queue to p2
        pt.pop();
        mp.erase(move);
        if(secondaryBuffer.size()==cap2 ){ //p2 full. use LRU tov remove and replace with MOVE 
            int maxVal=0; int remove;
            for(std::pair<int,int> i: secondaryBuffer){
                if(i.second>maxVal){
                    maxVal = i.second;
                    remove = i.first;
                }
            }
            if(write[remove]==1){
                h++;
                write[remove]=0;
            }
            secondaryBuffer.erase(remove);
            for(std::pair<int,int> i:secondaryBuffer) secondaryBuffer[i.first]++;
            secondaryBuffer[move]=0;
        }
        else if(secondaryBuffer.size()<cap2){ //p2 not full and not in p2
            if(secondaryBuffer.size()!=0) for(std::pair<int,int> i:secondaryBuffer) secondaryBuffer[i.first]++;
            secondaryBuffer[move]=0;
        }
        
        pt.push(val); f++; //INSERT VAL IN P1
        mp.insert(val);
    }

    else if(pt.size()==cap1 && mp.find(val)==mp.end()){ //not in p1 but found in p2
        int move = pt.front();
        pt.pop(); //remove from p1 front
        mp.erase(move);

        secondaryBuffer.erase(val);
        for(std::pair<int,int> i:secondaryBuffer) secondaryBuffer[i.first]++; //increment everything in lru
        secondaryBuffer[move]=0; //add to p2lru

        pt.push(val); //add to p1
        mp.insert(val);
        //h++;
    }
    else{
        if(!secondaryBuffer.empty()){
            for(std::pair<int,int> i:secondaryBuffer) secondaryBuffer[i.first]++; //increment everything in lru
        }
        //h++;
    }
}