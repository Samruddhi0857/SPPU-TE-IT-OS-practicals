#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void *writer_thr(void *temp);
void *reader_thr(void *temp);
sem_t mutex;
sem_t wrt;
int readcount = 0, nwt, nrd;
int data = 0;  // Shared data variable that writers modify and readers read

int main()
{
    long int i;
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    pthread_t reader[100], writer[100];

    printf("\nEnter number of readers: ");
    scanf("%d", &nrd);
    printf("\nEnter number of writers: ");
    scanf("%d", &nwt);
  
    for (i = 1; i <= nrd; i++)
    {
        pthread_create(&reader[i], NULL, reader_thr, (void *)i);
    }
  
    for (i = 1; i <= nwt; i++)
    {
        pthread_create(&writer[i], NULL, writer_thr, (void *)i);
    }  
  
    // Join threads for writers and readers
    for (i = 1; i <= nrd; i++)
    {
        pthread_join(reader[i], NULL);
    }
  
    for (i = 1; i <= nwt; i++)
    {
        pthread_join(writer[i], NULL);
    }
  
    // Destroy semaphores
    sem_destroy(&wrt);
    sem_destroy(&mutex);

    return 0;
}

void *reader_thr(void *temp)
{

    int id = (int)(long)temp;

    printf("\nReader %d is trying to enter database for reading.", id);
    sem_wait(&mutex);
    readcount++;
    if (readcount == 1) // First reader locks the writer semaphore
        sem_wait(&wrt);
    sem_post(&mutex);

    // Reading data
    printf("\nReader %d is now reading database. Data = %d", id, data);
    sleep(1);  // Simulate reading time

    sem_wait(&mutex);
    readcount--;
    if (readcount == 0) // Last r
eader unlocks the writer semaphore
        sem_post(&wrt);  
    sem_post(&mutex);

    printf("\nReader %d has left the database.\n", id);  
    sleep(1);  // Allow some time between accesses
    return NULL;
}

void *writer_thr(void *temp)
{
    int id = (int)(long)temp;

    printf("\nWriter %d is trying to enter database for modifying data.", id);
    sem_wait(&wrt);  // Writer locks the writer semaphore

    // Writing data
    data = rand() % 100;  // Assign a random value to the shared data
    printf("\nWriter %d is writing in database. New Data = %d", id, data);
    sleep(1);  // Simulate writing time

    printf("\nWriter %d is leaving the database.\n", id);
    sem_post(&wrt);  // Writer unlocks the writer semaphore
    sleep(1);  // Allow some time between accesses
    return NULL;
}

