#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

#define MAX 1000

// Function to check if a number is prime
int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

// Child process function to find primes in a range
void find_primes_in_range(int start, int end, int child_num) {
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);  // Start timing

    printf("Child %d (PID: %d) finding primes in range %d to %d.\n", child_num, getpid(), start, end);
    for (int i = start; i <= end; i++) {
        if (is_prime(i)) {
            printf("Child %d (PID: %d) found prime: %d\n", child_num, getpid(), i);
        }
    }

    gettimeofday(&end_time, NULL);  // End timing

    long seconds = end_time.tv_sec - start_time.tv_sec;
    long microseconds = end_time.tv_usec - start_time.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    printf("Child %d (PID: %d) completed in %.6f seconds.\n", child_num, getpid(), elapsed);
    exit(0);
}

int main() {
    FILE *file;
    char filename[] = "numbers.txt";
    int numbers[MAX], num_count = 0;
    
    // Open the file to read numbers
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    // Read numbers from the file
    while (fscanf(file, "%d", &numbers[num_count]) != EOF) {
        num_count++;
    }
    fclose(file);
    
    if (num_count == 0) {
        printf("No numbers to process.\n");
        return 1;
    }

    int n = 3; // Number of child processes (set based on preference, or from file)

    printf("Creating %d child processes.\n", n);

    int range_per_child = num_count / n;
    
    // Fork child processes
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        }
        else if (pid == 0) { // Child process
            int start = i * range_per_child;
            int end = (i == n - 1) ? num_count - 1 : (i + 1) * range_per_child - 1;  // Last child gets the remaining numbers
            find_primes_in_range(start, end, i + 1);  // Pass child number (i + 1)
        }
    }

    // Parent waits for all child processes to finish
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("All child processes have completed. Parent (PID: %d) is displaying the final message.\n", getpid());
    return 0;
}
