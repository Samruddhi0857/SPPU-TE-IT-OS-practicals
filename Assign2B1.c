#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define n 5
int arr[n];
int arr[n];

void printarray(int arr[]) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void bubbleSort(int arr[], int size) { 
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("Array after bubble sort: ");
    printarray(arr);
}

void accept(int arr[]) {
    printf("Enter array elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
}

int main(int argc, char *argv[]) {
    int pid;
    
    char *args[n + 1];
    char sortedarray[n + 1][12];

    accept(arr);
    bubbleSort(arr, n);
    
    pid = fork();
    


    if (pid < 0) {
        return 1;
    }
    
    if (pid == 0) {
        printf("Child process:\n");

        for (int i = 0; i < n; i++)
        {
            sprintf(sortedarray[i], "%d", arr[i]);
            args[i] = sortedarray[i];
        }
        args[n] = NULL;  

         execve("./child", args, NULL);
		
		perror("execve");
        return 1;
        
    }
    else if (pid > 0) {
        wait(NULL);
        printf("Parent process:\n");
    }

    return 0;
}

