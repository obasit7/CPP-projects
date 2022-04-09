i#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include "readerwriter.h"

//struct _rwlock_t *lock = malloc(sizeof(struct _rwlock_t));
Semaphore write;
Semaphore read;
Semaphore mutex_lock;
int readCount=0;

//function implementing delay
void reading_writing(){     
    int x=0, T;       
    T = rand()%50000;   
    for(int i = 0; i < T; i++)   
        for(int j = 0; j < T; j++)    
            x=i*j;  
}

//function implementing reader
void* readThread(void* args){
    printf("Create Reader\n");
        wait(read);//obtain read lock
        wait(mutex_lock); //obtain lock 2
            readCount++;
            if(readCount==1) 
                wait(write);//wait for writer
        signal(mutex_lock); //release both locks
        signal(read);

        //critical section
        printf("Reader is reading...\n");
        reading_writing();//delay
        wait(mutex_lock); //locks to decrement readCount appropriately
            readCount--;
            printf("Reader is done reading\n");
            if(readCount==0) 
                signal(write);
        signal(mutex_lock);
    
    return NULL;
}

//implement writer function
void* writeThread(void* args){
    printf("Create Writer\n"); 
        wait(read);//wait for reader
        wait(write);//obtain write lock
            printf("Writer is now writing\n");
            reading_writing();
        signal(write);//release locks
        signal(read);
            printf("Writer is done writing\n");
   
    return NULL;
}

int main()
{
    //variables
    char rw;
    FILE *file;
    int error;
    //open inputfile
    file = fopen("scenarios.txt", "r");

    //initialize lock
    init(mutex_lock, 1); init(write, 1); init(read,1);

    //for threads
    pthread_t thread;

    if (file){
        //scan input file
        printf("Scenario Starts:\n");
        while (fscanf(file, "%c", &rw) != EOF){

            if (rw == 'r'){
                //if read create a thread to run the readThread
                error = pthread_create(&thread, NULL, (void *)readThread, NULL);
                if (error != 0){
                    printf("Can't create thread.\n");
                    return 1;
                }
            }

            else if (rw == 'w'){
                //if write create a thread to run the writeThread
                error = pthread_create(&thread, NULL, (void *)writeThread, NULL);
                if (error != 0){
                    printf("Can't create thread.\n");
                    return 1;
                }
            }
            
        }
        joinThread(thread);
    }

    //close file
    fclose(file);

    //exit threads
    pthread_exit(NULL);

    return 0;
}
