#include <stdio.h>

int main() {
    int n, i, time, remaining, flag = 0;
    int time_quantum;
    int wait_time = 0, turnaround_time = 0;
    int burst_time[20], remaining_time[20];

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    remaining = n;  // Number of processes yet to finish

    // Input burst time for each process and initialize remaining time
    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];
    }

    // Input the fixed time quantum
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    
    // Simulation loop for round robin scheduling
    for (time = 0, i = 0; remaining != 0;) {
        if (remaining_time[i] <= time_quantum && remaining_time[i] > 0) {
            time += remaining_time[i];
            remaining_time[i] = 0;
            flag = 1;
        } else if (remaining_time[i] > 0) {
            remaining_time[i] -= time_quantum;
            time += time_quantum;
        }

        // If a process finished in this cycle, calculate its metrics
        if (remaining_time[i] == 0 && flag == 1) {
            remaining--;
            printf("P%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], time - burst_time[i], time);
            wait_time += time - burst_time[i];
            turnaround_time += time;
            flag = 0;
        }
        // Move to the next process cyclically
        i = (i + 1) % n;
    }

    // Display average waiting and turnaround times
    printf("\nAverage Waiting Time: %.2f\n", (float)wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)turnaround_time / n);

    return 0;
}