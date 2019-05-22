// This program show's off the basic "open" system call in Linux
// By: Nick from CoffeeBeforeArch

// For file control operations
#include <fcntl.h>
// For closing a file using the file descriptor
#include <unistd.h>
#include <stdio.h>

int main(){
    // The kernel maintains a list of per-process open files in a
    // file table. Each entry is a non-negative integer called a file
    // descriptor. Table entries also contain information about the
    // file (later).
    // 
    // 3 standard file descriptors:
    //      stdin:  0
    //      stdout: 1
    //      stderr: 2
    int fd;

    // "open" maps a path to a file descriptor
    // Takes a file path, flag (access mode + behavior), and permission
    // if a file is created.
    // Requires an access mode:
    //      O_RDONLY
    //      O_WRONLY
    //      O_RDWR
    //
    // Open a file as write-only
    fd = open("./test.txt", O_WRONLY);

    // Print out the flag and fd
    printf("Flag: 0x%X\n", O_WRONLY );
    printf("File descriptor fd = %d\n", fd);

    // Close the file descriptor
    close(fd);

    // Open the file for write-only mode, and truncate the file
    fd = open("./test.txt", O_WRONLY | O_TRUNC);

    // Print out the flag and fd
    printf("Flag: 0x%X\n", O_WRONLY | O_TRUNC);
    printf("File descriptor fd = %d\n", fd);

    return 0;
}
