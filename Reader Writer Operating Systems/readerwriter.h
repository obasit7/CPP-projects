#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define Thread pthread_t
#define Semaphore sem_t
#define newInt(n) (int*)malloc(sizeof(int)*n)
#define wait(semaphore) sem_wait(&semaphore)
#define signal(semaphore) sem_post(&semaphore)
#define joinThread(p) pthread_join(p, NULL)
#define init(semaphore,value) sem_init(&semaphore, 0, value)

