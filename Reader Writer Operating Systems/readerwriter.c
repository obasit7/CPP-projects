#include "readerwriter.h"

void reading_writing(){     
    int x=0, T;       
    T = rand()%50000;   
    for(int i = 0; i < T; i++)   
        for(int j = 0; j < T; j++)    
            x=i*j;  
}

void* readThread(void* args){
    printf("Create Reader\n");
        wait(read);
        wait(mutex_lock);
            readCount++;
            if(readCount==1) 
                wait(write);
        signal(mutex_lock);
        signal(read);

        //critical section
        printf("Reader is reading...\n");
        reading_writing();
        wait(mutex_lock);
            readCount--;
            printf("Reader is done reading\n");
            if(readCount==0) 
                signal(write);
        signal(mutex_lock);
    
    return NULL;
}

void* writeThread(void* args){
    printf("Create Writer\n");
    //for(int i=0;i<5;i++){ 
        wait(read);
        wait(write);
            printf("Writer is now writing\n");
            reading_writing();
        signal(write);
        signal(read);
            printf("Writer is done writing\n");
    //}
    return NULL;
}


