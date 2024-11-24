#include <stdio.h>
#include <stdbool.h>
#include <limits.h> // for INT_MAX

// Define a structure to hold process information
struct Process {
    int pid;    // Process ID
    int at;     // Arrival Time
    int bt;     // Burst Time
    int ct;     // Completion Time
    int tt;     // Turnaround Time
    int wt;     // Waiting Time
    int rt;     // Response Time
    int st;     // Start Time
};

int main() {
    int size = 0;
    printf("Enter number of processes: ");
    scanf("%d", &size);
    struct Process ps[size];  // Array of processes

    // Input process details
    printf("\nEnter process details:\n");
    for (int i = 0; i < size; ++i) {
        printf("Enter %d process details:\n", i + 1);
        ps[i].pid = i + 1;
        printf("\tEnter Arrival Time: ");
        scanf("%d", &ps[i].at);
        printf("\tEnter Burst Time: ");
        scanf("%d", &ps[i].bt);
    }

    // Display entered process details
    printf("\n====================================================================================\n\n");
    printf("PID\tAT\tBT\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt);
    }
    printf("\n\n====================================================================================\n\n");

    // Initialize required variables for SJF Preemptive Scheduling
    int completed = 0;
    int currentTime = 0;
    int burstTimeR[size];      // Remaining burst times
    bool iscompleted[size];    // Completion status

    float avgWT = 0, avgTT = 0, avgRT = 0;

    // Initialize burstTimeR and iscompleted arrays
    for (int i = 0; i < size; i++) {
        burstTimeR[i] = ps[i].bt;
        iscompleted[i] = false;
    }

    // SJF Preemptive Scheduling logic
    while (completed != size) 
  {
        int minimum = INT_MAX;
        int miniI = -1;

        // Find the process with the smallest remaining burst time
        for (int i = 0; i < size; i++)
         {
            if (ps[i].at <= currentTime && !iscompleted[i] && burstTimeR[i] < minimum) {
                minimum = burstTimeR[i];
  
              miniI = i;
               }
            // Resolve tie by choosing the process with an earlier arrival timeps
            else if (ps[i].at <= currentTime && !iscompleted[i] && burstTimeR[i] == minimum && ps[i].at < ps[miniI].at) {
                minimum = burstTimeR[i];
                miniI = i;
              }
        }

        // If no process is available, increment currentTime to simulate idle CPU
        if (miniI == -1) {
            currentTime++;
            continue;
        }

        // Check if the process is starting for the first time to calculate response time
        if (burstTimeR[miniI] == ps[miniI].bt) {
            ps[miniI].st = currentTime;
        }

        // Process the selected process for 1 unit of time
        burstTimeR[miniI]--;
        currentTime++;

        // If process is completed, calculate completion, turnaround, waiting, and response times
        if (burstTimeR[miniI] == 0) {
            ps[miniI].ct = currentTime;
            ps[miniI].tt = ps[miniI].ct - ps[miniI].at;
            ps[miniI].wt = ps[miniI].tt - ps[miniI].bt;
            ps[miniI].rt = ps[miniI].st - ps[miniI].at;

            // Accumulate the averages
            avgWT += ps[miniI].wt;
            avgTT += ps[miniI].tt;
            avgRT += ps[miniI].rt;

            completed++;
            iscompleted[miniI] = true;
        }
    }

    // Output results
    printf("PID\tAT\tBT\tCT\tTT\tWT\tRT\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tt, ps[i].wt, ps[i].rt);
    }
    printf("\n\n====================================================================================\n");

    // Display average waiting, turnaround, and response times
    printf("\n\nAverage Waiting Time: %.2f", avgWT / size);
    printf("\nAverage Turnaround Time: %.2f", avgTT / size);
    printf("\nAverage Response Time: %.2f\n", avgRT / size);
    printf("\n\n====================================================================================\n");

    return 0;
}

