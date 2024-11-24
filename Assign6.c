#include <stdio.h>
#include <string.h>
#define MAX_BUFF 1024

// Function prototypes for each page replacement algorithm


void fifo(char string[], int frameSize, int count);
void lru(char string[], int frameSize, int count);
void optimal(char string[], int frameSize, int count);

int main() {
    char string[50];
    int frameSize, count = 0;
    int choice = 0;

    printf("Enter the reference string: ");
    scanf("%s", string);

    printf("Enter the frame size: ");
    scanf("%d", &frameSize);

    // Calculate the number of pages in the reference string
    while (string[count] != '\0')
     count++;

    // Menu loop for page replacement algorithm selection
    while (choice != 4) {
        printf("\nChoose the Page Replacement Algorithm:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fifo(string, frameSize, count);
                break;
            case 2:
                lru(string, frameSize, count);
                break;
            case 3:
                optimal(string, frameSize, count);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please select 1, 2, 3, or 4.\n");
                break;
        }
    }
    return 0;
}



// FIFO Page Replacement Algorithm
void fifo(char string[], int frameSize, int count) {
    int faults = 0, front = 0, end = 0;
    char frame[frameSize];

    printf("Page\tFrame\tPage Fault\n");
    printf("============================\n");

    for (int i = 0; i < count; i++) {
        int found = 0;

        for (int j = 0; j < end; j++) {
            if (frame[j] == string[i]) {
                found = 1;
                break;
            }
        }

        if (!found)
      { 
            faults++;
            if (end < frameSize) 
            {
                frame[end++] = string[i]; 
            } else
            {
                frame[front] = string[i]; 
                front = (front + 1) % frameSize;
            }
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++)
            {
                printf("%c ", frame[k]);
            }
            printf("\tY\n");
        } 
     else 
     {
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) {
                printf("%c ", frame[k]);
            }
            printf("\tN\n");
        }
    }
    printf("Total Page Faults: %d\n", faults);
}

// LRU Page Replacement Algorithm
void lru(char string[], int frameSize, int count) {
    int faults = 0, end = 0;
    char frame[frameSize];
    int recent[frameSize];

    printf("Page\tFrame\tPage Fault\n");
    printf("============================\n");

    for (int i = 0; i < count; i++)
    {
        int found = 0, min = 0;

        for (int j = 0; j < end; j++) 
        {
            if (frame[j] == string[i])
            {
                found = 1;
                recent[j] = i;
                break;
            }
        }

        if (!found) 
        { 
            faults++;
            if (end < frameSize) 
            {
                frame[end] = string[i];
                recent[end++] = i;
            } else 
              {
                for (int j = 1; j < end; j++) 
                  {
                    if (recent[j] < recent[min])
                      min = j;
                  }
                frame[min] = string[i];
                recent[min] = i;
              }
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) 
            {
                printf("%c ", frame[k]);
            }
            printf("\tY\n");
        }
         else 
         {
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++)
            {
                printf("%c ", frame[k]);
            }
            printf("\tN\n");
        }
    }
    printf("Total Page Faults: %d\n", faults);
}

// Optimal Page Replacement Algorithm
void optimal(char string[], int frameSize, int count) {
    int faults = 0, end = 0;
    char frame[frameSize];

    printf("Page\tFrame\tPage Fault\n");
    printf("============================\n");

    for (int i = 0; i < count; i++) {
        int found = 0;

        for (int j = 0; j < end; j++) {
            if (frame[j] == string[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            faults++;
            if (end < frameSize) {
                frame[end++] = string[i];
            } else {
                int replace = -1, farthest = i;
                for (int j = 0; j < end; j++) {
                    int k;
                    for (k = i + 1; k < count; k++) {
                        if (frame[j] == string[k]) break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        replace = j;
                    }
                }
                frame[replace] = string[i];
            }
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) {
                printf("%c ", frame[k]);
            }
            printf("\tY\n");
        } else {
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) {
                printf("%c ", frame[k]);
            }
            printf("\tN\n");
        }
    }
    printf("Total Page Faults: %d\n", faults);
}

