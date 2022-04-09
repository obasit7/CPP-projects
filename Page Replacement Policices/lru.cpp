#include "lru.hpp"

void lru(int val, char rw, int cap, std::map<int,int> &lruMap, int&faults, int &hits, std::map<int,int> &write){
   
    if(write.find(val)==write.end()){
        write[val]==0;
    }
    if(rw=='W'){
        write[val]=1;
    }
    //if q full
    if(lruMap.size()==cap){
        if(lruMap.find(val)==lruMap.end()){
            int maxVal = 0;
            int dismissVal;
            
            for(std::pair<int,int> i: lruMap){
                if(i.second>maxVal){
                    dismissVal = i.first;
                    maxVal = i.second;
                }
            }
            lruMap.erase(dismissVal);
            if(write[dismissVal]==1){
                hits++;
                write[dismissVal]=0;
            }

            for(std::pair<int,int> i:lruMap)
                lruMap[i.first]++;
            

            lruMap[val]=0;
            faults++;

        } else{
            
            for(std::pair<int,int> i:lruMap)
                lruMap[i.first]++;
            
            lruMap[val] = 0;
        }           
    }
    //if q not full
    if(lruMap.size()<cap){
        //val not in q
        if(lruMap.find(val)==lruMap.end()){
            //visitMap.insert(val);
            for(std::pair<int,int> i:lruMap)
                lruMap[i.first]++;
                //(i.second) = (i.second+1);
            lruMap[val]=0;
            faults++;

        } else {
            //hits++;
            for(std::pair<int,int> i:lruMap)
                lruMap[i.first]++;
            
            lruMap[val]=0;
        }
    }
}