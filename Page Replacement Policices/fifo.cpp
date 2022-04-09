#include "fifo.hpp"

void fifo(int val, char rw, std::queue<int> &pt, int cap, std::set<int> &mp, int &diskRead, int &diskWrite, std::map<int,int> &write){
    //if q is full
    if(write.find(val)==write.end()){
        write[val]==0;
    }
    if(rw=='W'){
        write[val]=1;
    }

    if(pt.size()==cap){//if table full        
        //and val not in q
        if(mp.find(val)==mp.end()){
            int dismiss = pt.front();
            pt.pop();
            //cout<<val<<": POPPED "<<dismiss<<endl;
            mp.erase(dismiss);
            if(write[dismiss]==1){
                diskWrite++;
                write[dismiss]=0;
            }

            pt.push(val);
            mp.insert(val);
            diskRead++;
        } //else{++;}
        //val in q
    }

    //if q is not full
    if(pt.size()<cap){
        //and val not in q
        if(mp.find(val)==mp.end()){
            mp.insert(val);
            pt.push(val);
            diskRead++;
        } //else{h++;} //cout<<val<<" ALREADY IN NOT FULL Q\n";}
        //val in q: do nothing
        
    }     
}