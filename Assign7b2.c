//server
#include <sys/ipc.h>  
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include<unistd.h>

int main() {
    void *shared_memory;// shared memory address
    char str[100]; //buffer

    // CREATE KEY
    key_t k = 1234;  //any number to assign to shared segment

    // CREATE SHARED MEMORY 
    int shmid = shmget(k, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("Shared memory creation failed");
        return 1;
    }
    
    //print key

    // process ATTACH to shared MEMORY segment
    shared_memory = shmat(shmid, NULL, 0);
    
    if (shared_memory == (void *)-1) {
        perror("Shared memory attachment failed");
        return 1;
    }
    
    printf("process attached at %p:",shared_memory); //p =prints memory address

    // INPUT DATA TO SHARE
    printf("Write data: \n");
    read(0, str, 100);  // Reads input safely into the buffer

    // COPY DATA TO SHARED MEMORY
    strcpy(shared_memory, str);  //string copy
    printf("Data written in memory: %s\n", (char *)shared_memory);

    // DETACH MEMORY
    shmdt(shared_memory);

    return 0;
}
