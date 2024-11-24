//client
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>

int main() {
    void *shared_memory;
    //void* - is used to store any data type
    /A void is a generic pointer type that can point to any data type. However, you can’t dereference a void* directly because it doesn't have a type associated with it.
To use the data at a void* pointer, you must cast it to the appropriate type, such as char*, int*, etc.*/
    int shmid;

    // Access shared memory with same key as from server
    shmid = shmget((key_t)1234, 1024, 0666); //dont IPC create as shared memory already created
    if (shmid == -1) {
        perror("Shared memory access failed");
        return 1;
    }

    // Attach the shared memory to this process
    shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (void *)-1) {
        perror("Shared memory attachment failed");
        return 1;
    }

    // Read and display the data from shared memory
    printf("Data from shared memory: %s\n", (char *)shared_memory);

    // Detach from shared memory
    if (shmdt(shared_memory) == -1) {
        perror("Shared memory detachment failed");
        return 1;
    }

    return 0;
}
