#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

// Function to extract boundary from the multipart/form-data
std::string get_boundary(const std::string& post_body) {
    std::string boundary_prefix = "--";
    std::istringstream stream(post_body);
    std::string first_line;

    // Get the first line from the post_body
    if (std::getline(stream, first_line)) {
        std::size_t boundary_start = first_line.find(boundary_prefix);

        if (boundary_start != std::string::npos) {
            // Remove the boundary prefix
            std::string boundary = first_line.substr(boundary_start + boundary_prefix.length());

            // Remove any trailing newline or carriage return characters
            boundary.erase(std::remove(boundary.begin(), boundary.end(), '\r'), boundary.end());
            boundary.erase(std::remove(boundary.begin(), boundary.end(), '\n'), boundary.end());
            
            return boundary;
        }
    }

    return ""; // Boundary not found
}

// Function to handle the POST request and invoke Python CGI script
void handle_post_request(const std::string& post_data, const std::string& boundary) {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(pipe_fd[1]); // Close write end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to read end of the pipe
        close(pipe_fd[0]); // Close read end of the pipe

        // Set environment variables
        std::string content_length = std::to_string(post_data.size());
        std::string content_type = "multipart/form-data; boundary=" + boundary;
        char *envp[] = {
            (char*)"REQUEST_METHOD=POST",
            (char*)("CONTENT_LENGTH=" + content_length).c_str(),
            (char*)("CONTENT_TYPE=" + content_type).c_str(),
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
    // Simulate raw multipart/form-data POST body
    std::string post_body = "------WebKitFormBoundaryE7NhyyOUKHo0iEZB\r\n"
                            "Content-Disposition: form-data; name=\"name\"\r\n\r\n"
                            "Mai\r\n"
                            "------WebKitFormBoundaryE7NhyyOUKHo0iEZB\r\n"
                            "Content-Disposition: form-data; name=\"age\"\r\n\r\n"
                            "12\r\n"
                            "------WebKitFormBoundaryE7NhyyOUKHo0iEZB--\r\n";

    std::string boundary = get_boundary(post_body);

    if (!boundary.empty()) {
        std::cout << "Boundary: " << boundary << std::endl;
        handle_post_request(post_body, boundary);
    } else {
        std::cout << "Boundary not found" << std::endl;
    }

    return 0;
}
