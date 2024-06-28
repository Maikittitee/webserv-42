#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <vector>

void handle_post_request(const std::string& post_data) {
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
        std::string content_length = std::to_string(post_data.size());
        char *envp[] = {
            (char*)"REQUEST_METHOD=POST",
            (char*)("CONTENT_LENGTH=" + content_length).c_str(),
            (char*)"CONTENT_TYPE=application/x-www-form-urlencoded",
            nullptr
        };

        // Prepare arguments for execve
        char *argv[] = { (char*)"/usr/bin/python3", (char*)"hello.py", nullptr };
        
        execve(argv[0], argv, envp);
        perror("execve");
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

int main() {
    // Simulate receiving POST data
    std::string post_data = "name=John&age=30";

    handle_post_request(post_data);

    return 0;
}
