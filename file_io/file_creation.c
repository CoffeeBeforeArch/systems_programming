// This program shows off file creation in C with the "creat" syscall
// By: Nick from CoffeeBeforeArch

#include <fcntl.h>
// For mode bits
#include <sys/stat.h>
#include <stdio.h>
#include <assert.h>

int main(){
    // File descriptor for our new file
    int fd;

    // We ignored the possible mode argument of "open(...)" in the
    // previous example because we did not create a file.
    // This sets permissions at the:
    //  Owner
    //  Group
    //  Everyone else
    // levels. (More bit masks for read, write, and execute)
    
    // Set RWX permissions for owner, and R permissions for everyone
    // else
    // At a bit level, this looks like:
    //  111 100 100
    mode_t mode = S_IWUSR | S_IRUSR | S_IXUSR | S_IRGRP | S_IROTH;
    
    // We could also just specify this in octal...
    mode = 0744;

    // Let us give our file a name
    const char *name = "creat_test.txt";

    // Creating a new file with the flags:
    //  O_WRONLY:   Write-only
    //  O_CREAT:    Create a file if it doesn't exist already
    //  O_TRUNC:    Truncate the file
    // is very common, so there is function specifically for this.
    // "creat(..)" is the equvilant of "open(...)" with some pre-set
    // arguments.
    fd = creat(name, mode);
    if(fd == -1){
        printf("ERROR: File creation failed!\n");
        assert(0);
    }

    // Print the name and fd if file created succesfully
    printf("Created file %s with fd %d\n", name, fd);

    return 0;
}
