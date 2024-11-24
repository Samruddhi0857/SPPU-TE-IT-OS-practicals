#include <stdio.h>
#include <stdlib.h>
#define MAX_REQUESTS 100

void SSTF();
void SCAN();
void CLOOK();
int main() {
    int choice;
    do {
        printf("\n\n----------- MENU-----------");
        printf("\n1: SSTF");
        printf("\n2: SCAN");
        printf("\n3: CLOOK");
        printf("\n4: EXIT");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: SSTF();
             break;
            case 2: SCAN(); 
            break;
            case 3: CLOOK(); 
            break;
            case 4: exit(0);
            default: printf("\nInvalid choice! Please try again.");
        }
    } while (1);
    return 0;
}
void SSTF() {
    int requests[MAX_REQUESTS], n, initial, totalHeadMovement = 0;
    printf("Enter the number of Requests: ");
    scanf("%d", &n);
    printf("Enter the Requests sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d", &initial);
    for (int count = 0; count < n; count++) 
    {//ensures that each request is handled.
        int minDistance = 1000, index = -1;
        for (int i = 0; i < n; i++) // inner loop finds the nearest request.
        {
            int distance = abs(requests[i] - initial);
            if (distance < minDistance) 
            {
                minDistance = distance;
                index = i;  //found the minimum distance
            }   
            
         }
        totalHeadMovement += minDistance;
        initial = requests[index];
        requests[index] = 1000;  // Mark requests[index] as processed by setting it to a large number
      }
    printf("Total head movement is %d\n", totalHeadMovement);	
    
  }
void SCAN() {
    int requests[MAX_REQUESTS], n, initial, size, totalHeadMovement = 0, direction;
    printf("Enter the number of Requests: ");
    scanf("%d", &n);
    printf("Enter the Requests sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);  }   
     printf("Enter initial head position: ");
    scanf("%d", &initial);
    printf("Enter total disk size: ");
    scanf("%d", &size);
    printf("Enter direction (1 for high, 0 for low): ");
    scanf("%d", &direction);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }  }  }
    int index;//Find the starting point for the scan: Set index to the first position in requests[]
    for (index = 0; index < n; index++)
     {
        if (initial < requests[index]) 
        {
            break;   
        }  
          
      }
    if (direction == 1)
     {
        for (int i = index; i < n; i++) 
        {
            totalHeadMovement += abs(requests[i] - initial);
            initial = requests[i]; //imp 
        }
        totalHeadMovement += abs(size - 1 - requests[n - 1]);//
        initial = size - 1;
        for (int i = n - 1; i >= 0; i--)
         {
            totalHeadMovement += abs(requests[i] - initial);
            initial = requests[i];  
         }
    } 
    else 
    {
        for (int i = index - 1; i >= 0; i--) 
        {
            totalHeadMovement += abs(requests[i] - initial);
            initial = requests[i];  
        }
        totalHeadMovement += abs(0 - requests[0]);
        initial = 0;
        for (int i = index; i < n; i++)
         {
            totalHeadMovement += abs(requests[i] - initial);//
            initial = requests[i];   
         }  
      }
    printf("Total head movement is %d\n", totalHeadMovement);
}

void CLOOK() {
    int requests[MAX_REQUESTS], n, initial, totalHeadMovement = 0;
    int direction;
    printf("Enter the number of Requests: ");
    scanf("%d", &n);
    printf("Enter the Requests sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);   }
    printf("Enter initial head position: ");
    scanf("%d", &initial);
    printf("enter the direction:,0:low ,1:high)\n");
    scanf("%d",&direction);
    
   for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;    }   }   }
    int index;
    for (index = 0; index < n; index++) {
        if (initial < requests[index]) {
            break;   }   }
            
   if(direction==1)
   {
            for (int i = index; i < n; i++) {
        totalHeadMovement += abs(requests[i] - initial);
        initial = requests[i];   }   
for (int i = 0; i < index; i++) {
        totalHeadMovement += abs(requests[i] - initial);
        initial = requests[i];   }
            
   }
   else
   {
     for(int i=index-1;i>=0;i--)
     {
        totalHeadMovement +=abs(requests[i]-initial);
        initial=requests[i];
     }
    
    // Move upward through remaining requests
    for (int i = n - 1; i >= index; i--) {
        totalHeadMovement += abs(requests[i] - initial);
        initial = requests[i];
    }
   
   }
    
    printf("Total head movement is %d\n", totalHeadMovement);
}
