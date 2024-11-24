#include <stdio.h>
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int n, m;
int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int safesequence[MAX_PROCESSES];

void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void display() {
    printf("\nProcess\tAllocation\tMax\t\tNeed\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < m; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

int isSafeState() {
    int work[MAX_RESOURCES], finish[MAX_PROCESSES] = {0};
    int count = 0;
    
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }
    
    for (int k = 0; k < n; k++) {
        int found = 0;
        
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int flag = 1;
                
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 0;
                        break;
                    }
                }
                
                if (flag) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safesequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        
        if (!found) {
            break;
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (finish[i] == 0) {
            return 0;
        }
    }
    
    return 1;
}

int requestResources(int process, int request[]) {
    for (int i = 0; i < m; i++) {
        if (request[i] > need[process][i]) {
            printf("\nError: Process has exceeded its maximum claim.\n");
            return 0;
        }
    }
    
    for (int i = 0; i < m; i++) {
        if (request[i] > available[i]) {
            printf("\nProcess P%d must wait: Not enough resources available.\n", process);
            return 0;
        }
    }
    
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }
    
    if (isSafeState()) {
        printf("\nResources allocated to process P%d.\n", process);
        return 1;
    } else {
        printf("\nUnsafe state detected! Rolling back resource allocation for process P%d.\n", process);
        
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        
        return 0;
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter available resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    printf("\nEnter maximum resources required by each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d:\n", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter allocated resources for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d:\n", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    
    calculateNeed();
    display();
    
    if (isSafeState()) {
        printf("\nThe system is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safesequence[i]);
        }
        printf("\n");
    } else {
        printf("\nThe system is not in a safe state!\n");
    }
    
    int process, request[MAX_RESOURCES];
    printf("\nEnter the process number that is requesting resources: ");
    scanf("%d", &process);
    printf("Enter the resources requested by process P%d: ", process);
    
    for (int i = 0; i < m; i++) {
        scanf("%d", &request[i]);
    }
    
    requestResources(process, request);
    
    return 0;
}

