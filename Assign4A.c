#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 20


typedef struct {
    int buff[BUFFER_SIZE];     // Buffer of fixed size
    sem_t full, empty;         // Semaphores for full and empty slots
} shared;


shared sh;
int in = 0, out = 0;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int producer_id = *((int *)arg);
     // Each producer produces 3 items
        int item = rand() % 100; // Produce a random item

        sem_wait(&sh.empty);           // Wait for an empty slot
        pthread_mutex_lock(&mutex);     // Lock the buffer

        sh.buff[in % BUFFER_SIZE] = item; // Insert item in buffer
        printf("Producer %d produced: %d\n", producer_id, item);
        in++;                           // Update producer index

        pthread_mutex_unlock(&mutex);   // Unlock the buffer
        sem_post(&sh.full);             // Signal that buffer is not empty
        sleep(1);                       // Simulate production time
    
    pthread_exit(0);
}

void *consumer(void *arg) {
    int consumer_id = *((int *)arg);
    while (1) {
        sem_wait(&sh.full);             // Wait if buffer is empty
        pthread_mutex_lock(&mutex);     // Lock the buffer

        int item = sh.buff[out % BUFFER_SIZE]; // Remove item from buffer
        printf("Consumer %d consumed: %d\n", consumer_id, item);
        out++;                          // Update consumer index

        pthread_mutex_unlock(&mutex);   // Unlock the buffer
        sem_post(&sh.empty);            // Signal that there’s space in buffer
        sleep(1);                       // Simulate consumption time
    }
    pthread_exit(0);
}

int main() {
    int num_producers, num_consumers;


    // Prompt the user for the number of producers and consumers
    printf("Enter the number of producers: ");
    scanf("%d", &num_producers);
    printf("Enter the number of consumers: ");
    scanf("%d", &num_consumers);

    pthread_t producers[num_producers], consumers[num_consumers];
    int producer_ids[num_producers], consumer_ids[num_consumers];

    // Initialize semaphores and mutex
    sem_init(&sh.empty, 0, BUFFER_SIZE); // Buffer initially empty
    sem_init(&sh.full, 0, 0);            // No items initially
    pthread_mutex_init(&mutex, NULL);

    // Create producer threads
    for (int i = 0; i < num_producers; i++) {
        producer_ids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }

    // Create consumer threads
    for (int i = 0; i < num_consumers; i++) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    // Wait for all producer threads to finish
    for (int i = 0; i < num_producers; i++) {
        pthread_join(producers[i], NULL);
    }


    // Consumer threads are infinite, so we don’t join them here

    // Cleanup
    sem_destroy(&sh.empty);
    sem_destroy(&sh.full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

