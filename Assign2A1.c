/*
A. Implement the C program in which main program accepts the integers to be sorted. Main program uses the FORK system call to create a new process called a child process. Parent process sortsthe integers using sorting algorithm and waits for child process using WAIT system call to sort the integers using any sorting algorithm. Also demonstrate zombie and orphan states
*/
//orphan state

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void bubble_sort(int arr[], int size) {
	for(int i=0; i<size-1; i++) {
         for(int j=0; j<size-i-1; j++)
{
      if(arr[j]>arr[j+1])
      {
        temp=arr[j];
        arr[j]=arr[j+1];
        arr[j+1]=temp;
       }
     }
  }
       for(int i=0;i<size;i++)
       {
         printf("%d" , arr[i]);
       }
    }
    

void insertionSort(int arr[],size) {
    int i, key, j;
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    printf("Array after insertion sort (Parent): ");
     for(int i=0;i<size;i++)
       {
         printf("%d" , arr[i]);
       }
}


int main() {
    int size;

    printf("Enter size of array: ");
    scanf("%d", &size);

    int arr[size];

    printf("Enter %d numbers in array: ", size);
    for(int i=0; i<size; i++) {
        scanf("%d", &arr[i]);
    }

    int pid = fork();

    if(pid == 0) {
        printf("\n-------Hello from child process-------\n");
        printf("Childs parent process id: %d\n", getppid());

        sleep(3);

        printf("Child process id: %d\n", getpid());
        printf("Childs parent process id: %d\n", getppid());
        bubble_sort(arr, 0, size);
    }
    else if(pid != 0) {
        printf("\n-------Hello from parent process-------\n");
        printf("Parent process id: %d\n", getpid());
        insertionsort(arr, 0, size);
    }
}
