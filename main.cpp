
#include <iostream>
#include <filesystem>
#include "./src/app/processes/ProcessManagement.hpp"
#include "./src/app/processes/Task.hpp"
#include <ctime>
#include <iomanip>
#include <sys/wait.h>

namespace fs = std::filesystem;

void processFile(const std::string& filePath, const std::string& action, ProcessManagement& processManagement) {
    IO io(filePath);
    std::fstream f_stream = std::move(io.getFileStream());

    if (f_stream.is_open()) {
        Action taskAction = (action == "encrypt") ? Action::ENCRYPT : Action::DECRYPT;
        auto task = std::make_unique<Task>(std::move(f_stream), taskAction, filePath);
        
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        std::cout << "Starting the " << action << " at: " << std::put_time(now, "%Y-%m-%d %H:%M:%S") << " for file: " << filePath << std::endl;
        processManagement.submitToQueue(std::move(task));
    } else {
        std::cout << "Unable to open file: " << filePath << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::string path;
    std::string action;

    std::cout << "Enter the file path or directory path: ";
    std::getline(std::cin, path);

    std::cout << "Enter the action (encrypt/decrypt): ";
    std::getline(std::cin, action);

    try {
        ProcessManagement processManagement;

        if (fs::is_regular_file(path)) {
            // Process single file
            processFile(path, action, processManagement);
        } else if (fs::is_directory(path)) {
            // Process all files in the directory
            for (const auto& entry : fs::recursive_directory_iterator(path)) {
                if (entry.is_regular_file()) {
                    processFile(entry.path().string(), action, processManagement);
                }
            }
        } else {
            std::cout << "Invalid path. Please provide a valid file or directory path." << std::endl;
            return 1;
        }

        // Wait for all child processes to finish
        int status;
        pid_t wpid;
        while ((wpid = wait(&status)) > 0) {
            if (WIFEXITED(status)) {
                std::cout << "Child process " << wpid << " exited with status " << WEXITSTATUS(status) << std::endl;
            } else if (WIFSIGNALED(status)) {
                std::cout << "Child process " << wpid << " killed by signal " << WTERMSIG(status) << std::endl;
            }
        }

    } catch (const fs::filesystem_error& ex) {
        std::cout << "Filesystem error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
