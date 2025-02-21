#include <stdio.h>    // For printf
#include <unistd.h>   // For fork, exec, getpid, getppid
#include <sys/wait.h> // For wait

int main()
{
    pid_t pid = fork(); // Step 1: Create a new process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // This is the child process
        printf("Child Process (PID: %d, Parent PID: %d)\n", getpid(), getppid());
        
        // Step 2: Replace process with a new program using exec
        // Runs the "ls" command to list directory contents
        execlp("ls", "ls", "-l", NULL);

        // If exec fails, this will run
        perror("Exec failed");
        return 1;
    } else {
        // This is the parent process
        printf("Parent Process (PID: %d, Child PID: %d)\n", getpid(), pid);

        // Step 3: Wait for the child to finish
        int status;
        wait(&status);

        // Step 4: Check if the child exited properly
        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child did not exit properly\n");
        }
    }

    printf("Process (PID: %d) finished.\n", getpid());
    return 0;
}

