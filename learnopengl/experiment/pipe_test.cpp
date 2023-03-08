#include <iostream>
#include <stdio.h>
#include <cstring>

int main() {
    // Open the Python script as a read pipe
    FILE* read_pipe = popen("python3 pipe_test.py", "r");
    if (!read_pipe) {
        std::cerr << "Failed to open read pipe" << std::endl;
        return 1;
    }

    // Open the Python script as a write pipe
    FILE* write_pipe = popen("python3 pipe_test.py", "w");
    if (!write_pipe) {
        std::cerr << "Failed to open write pipe" << std::endl;
        return 1;
    }

    // Send a message to the Python script
    std::string message = "Hello from C++";
    fprintf(write_pipe, "%s\n", message.c_str());
    fflush(write_pipe);

    // Receive a message from the Python script
    char buffer[1024];

    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fileno(read_pipe), &fds);

    while(true){
// Wait for the pipe to become readable
      std::cout << "wait for response";
        int ready = select(fileno(read_pipe) + 1, &fds, NULL, NULL, NULL);
        if (ready < 0)
        {
            std::cerr << "select() failed!" << std::endl;
            break;
        }

        // Check if the pipe is ready for reading
        if (FD_ISSET(fileno(read_pipe), &fds))
        {
    }

    fgets(buffer, 1024, read_pipe);
    std::cout << "Received message from Python: " << buffer << std::endl;

    }
    // Close the pipes and exit
    pclose(read_pipe);
    pclose(write_pipe);
    return 0;
}
