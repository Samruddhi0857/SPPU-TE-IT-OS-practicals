#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define n 5

int main(int argc , char*argv[] )
{

int arr[n];

		for( int i=0;i<n ; i++ )
		{
			arr[i]=atoi(argv[i]);
		}
		
		printf("Array in reverse order:\n");
		
   		for (int i = n - 1; i >= 0; i--) 
   		{
       		 printf("%d ", arr[i]);
   		}
    printf("\n");

}
