#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>

void handle_post_request(const std::string& post_data, char **env) {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(pipe_fd[1]); // Close write end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to read end of the pipe
        close(pipe_fd[0]); // Close read end of the pipe

        // Set environment variables
        setenv("REQUEST_METHOD", "POST", 1);
        setenv("CONTENT_LENGTH", std::to_string(post_data.size()).c_str(), 1);
        setenv("CONTENT_TYPE", "application/x-www-form-urlencoded", 1);


		char *arg[] = {"/usr/bin/python3", "python3", "hello.py", NULL};
		execve(arg[0], arg, env);
        execl("/usr/bin/python3", "python3", "hello.py", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipe_fd[0]); // Close read end of the pipe
        write(pipe_fd[1], post_data.c_str(), post_data.size());
        close(pipe_fd[1]); // Close write end of the pipe

        // Wait for the child process to complete
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            std::cout << "Child process exited with status " << WEXITSTATUS(status) << std::endl;
        }
    }
}

int main(int ac, char **av, char **env) {
    // Simulate receiving POST data
    std::string post_data = "name=MAIZA&age=20";

    handle_post_request(post_data, env);

    return 0;
}
