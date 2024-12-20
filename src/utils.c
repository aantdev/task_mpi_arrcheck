#include "../include/utils.h"
#include "../include/display.h"

// basic util, find min in arr.
int min(int* arr, int count){
    int min = arr[0];
    for (int i = 1; i < count; i++) {
        if (arr[i] < arr[i-1]) {
            min = arr[i];
        }
    }
    return min;
}

void read_int(int* target){
    int a;
    char buf[1024]; // use 1KiB just to be sure
    int success; // flag for successful conversion

    do
    {
        if (!fgets(buf, 1024, stdin))
        {
            // reading input failed:
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        // have some input, convert it to integer:
        char *endptr;

        errno = 0; // reset error number
        a = strtol(buf, &endptr, 10);
        if (errno == ERANGE)
        {
            printf("Sorry, this number is too small or too large.\n");
            success = 0;
        }
        else if (endptr == buf)
        {
            // no character was read
            success = 0;
        }
        else if (*endptr && *endptr != '\n')
        {
            // *endptr is neither end of string nor newline,
            // so we didn't convert the whole input
            // This works against cases like "223df" and others.
            success = 0;
        }
        else
        {
            success = 1;
        }
    // Repeat prompting until there is valid input
    } while (!success); 

    *target = a;
}


void fill_array(int* arr, int count){
    for (int i = 0; i < count; i++){
        system("clear");

        printf("Numbers left: %d\n", count - i);
        display_arr(arr, count, i, 0);
        read_int(&arr[i]);

        system("clear");
    }

}
