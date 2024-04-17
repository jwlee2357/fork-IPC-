#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <string.h> // Include for strlen()

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) { // create the pipe
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    pid = fork(); // fork a child process
    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork failed");
        return 1;
    }
    if (pid > 0) { /* parent process */
        close(fd[READ_END]); // close the unused end of the pipe
        /* write to the pipe */
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
        /* close the write end of the pipe */
        close(fd[WRITE_END]);
    } else { /* child process */
        close(fd[WRITE_END]); // close the unused end of the pipe
        /* read from the pipe */
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        read_msg[strlen(write_msg)] = '\0'; // Null-terminate the read message
        printf("read: %s\n", read_msg);
        /* close the read end of the pipe */
        close(fd[READ_END]);
    }
    return 0;
}

