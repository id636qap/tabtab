#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
	char command[100];
	// Continuously read commands from the user
	while (fgets(command, sizeof(command), stdin) != NULL) {
		// Remove newline character
		command[strlen(command) - 1] = '\0';
		// Fork a child process
		pid_t pid = fork();
		if (pid == 0) {
			// Child process
			// Execute the command using execlp
			execlp(command, command, NULL);
			// If execlp fails, print an error message and exit
			perror("execlp");
			exit(EXIT_FAILURE);
		} else {
			// Parent process
			int status;
			// Wait for the child process to complete and get its exit status
			wait(&status);
			// Print the exit status of the child process
			printf("Child process %d exited with status %d\n", pid,
			WEXITSTATUS(status));
		}
	}
return 0;
}
