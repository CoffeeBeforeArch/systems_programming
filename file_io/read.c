// This program shows off the read system call using C
// By: Nick from CoffeeBeforeArch

#include <fcntl.h>
// For reading the file and closing it
#include <unistd.h>
// For errno (only significant if a system call fails)
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(){
    // Open our example file for reading
    int fd = open("./test.txt", O_RDONLY);
    if(fd == -1){
        printf("ERROR: Failed to open file\n");
        assert(0);
    }

    // Buffer in which we will store read in characters (only 100)
    int len = 100;
    int position = 0;
    char *buffer = (char*)calloc(len, sizeof(char));
    
    // Signed size_t for read return
    ssize_t ret;

    // Read in all bytes from file
    // Ensure we don't exceed the buffer
    // Stop reading if EOF (i.e. ret = 0)
    while(len != 0 && (ret = read(fd, buffer + position, len)) != 0){
        // Problem with the read
        if(ret == -1){
            // A signal was received before any bytes were read
            // Safe to re-issue
            if(errno == EINTR){
                continue;
            }

            // Fail if non-recoverable error
            printf("ERROR: read unsuccesful\n");
            assert(0);
        }

        // Decrease the amount left to read by what was read
        len -= ret;

        // Move over the position of the buffer by an equal amount
        position += ret;

        printf("Read %ld bytes. Updated len to %d. Updated position to %d\n", ret, len, position);
    }

    // Close the file descriptor
    if(close(fd) == -1){
        printf("ERROR: Failed to close file descriptor\n");
        assert(0);
    }

    // Read succesfully completed - print the message
    printf("Read completed!\n");
    printf("Message: %s\n", buffer);

    return 0;
}
