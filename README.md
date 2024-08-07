# File Encryption/Decryption System

This project implements a multi-process file encryption and decryption system using C++. It allows users to encrypt or decrypt multiple files in a directory concurrently.

## Features

- Recursive directory traversal
- Multi-process execution for improved performance
- Shared memory and semaphores for inter-process communication
- Custom encryption/decryption algorithm
- File I/O handling

## Requirements

- C++17 compatible compiler
- POSIX-compliant operating system (Linux/Unix)
- CMake (for building)

## Building the Project

1. Clone the repository:
```bash
git clone https://github.com/SinghKrAshish/Encrypt-Decrypt-System.git
cd Encrypt-Decrypt-System
```

2. Build the project:
```bash
run this command in the termial: make
```
This will create two executables: `encrypt_decrypt` (main program) and `cryption` (worker program).

## Usage

1. Run the main program:
  ```bash
./encrypt_decrypt
  ```
2. When prompted, enter the directory path containing the files you want to process.

3. Choose the action (encrypt or decrypt).

4. The program will process all files in the specified directory and its subdirectories.

## Project Structure

- `main.cpp`: Entry point of the main program
- `src/app/encryptDecrypt/`: Contains encryption/decryption logic
- `src/app/fileHandling/`: Handles file I/O operations
- `src/app/processes/`: Manages multi-process execution and IPC

## Configuration

- The encryption key is stored in a `.env` file in the project root directory.

## Testing

A Python script `makeFiles.py` is provided to generate test files:
```bash
python makeDirs.py
```
This will create 1000 text files with random content in a `test` directory.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
