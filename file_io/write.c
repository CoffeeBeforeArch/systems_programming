// This program shows off the write system call using C
// By: Nick from CoffeeBeforeArch

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(){
    // Open our example file for reading
    int fd = open("./test.txt", O_WRONLY | O_APPEND);
    if(fd == -1){
        printf("ERROR: Failed to open file\n");
        assert(0);
    }

    // Buffer in which we will store read in characters (only 100)
    const char *message = "This is a test message!";

    // Signed size_t for read return
    size_t len = strlen(message);
    ssize_t ret;

    // Keep track of what part of the message hasn't been written
    int position = 0;

    // Write the entire message
    // Ensure we keep writing on partial writes
    // Break on returns of 0
    while(len != 0 && (ret = write(fd, message + position, len)) != 0){
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

        printf("Written %ld bytes. Updated len to %ld. Updated position to %d\n", ret, len, position);
    }

    // Close the file descriptor
    if(close(fd) == -1){
        printf("ERROR: Failed to close file descriptor\n");
        assert(0);
    }

    // Read succesfully completed - print the message
    printf("Write completed!\n");

    return 0;
}
