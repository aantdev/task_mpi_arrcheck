#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../include/front.h"
#include "../include/utils.h"

// Fill array with ints (user input)
void fill_array(int* arr, int count); 
// Print front in nicer way, 
// optional index (^) to point at element of choice (-1 to disable)
// num_or_comma to specify, point to num, or between nums (0 - on num, 1 - between, -1 - ignore)
// basic util, return minimum element
int min(int* arr, int count);
void read_int(int* target);

int main(int argc, char** argv){
    // Init the thing
    MPI_Init(&argc, &argv);

    // Get process ID.
    int proc_id, proc_c;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_c);
    
    // Main process 
    if (proc_id == 0){

        int* returns = NULL;
        int* int_list = NULL;
        
        // ask user for input
        int pick = 0;
        while (pick != 1 && pick != 2) {
            system("clear");
            printf("Choose action:\n1) Check list\n2) Abort\n");
            read_int(&pick);
        }
        if (pick == 2) 
            MPI_Abort(MPI_COMM_WORLD, 2); 

        int N = 0;
        while (N <= 1) {
            system("clear");
            printf("Give size of list :\n");
            read_int(&N);
        }

        int_list = calloc(N, sizeof(int));
        if (int_list == NULL) 
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);

        fill_array(int_list, N);
        putchar('\n');

        for (int i = 1; i < proc_c; i++){
            MPI_Send(&N, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(int_list, N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        
        //receive shit back
        int res;

        // Get all non-zero returns, store in array, 
        // determine which failure is the earliest
        int count = 0;
        returns = calloc(proc_c, sizeof(int));
        if (returns == NULL) 
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        for (int i = 1; i < proc_c; i++){
            MPI_Recv(&res, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
            
            if (res > 0) { returns[count] = res; count++; }
        }

        putchar('\n');
        if (count == 0){
            arr_front(int_list, N, -1, -1);
            printf("This array is sorted in ascending order.\n");
        }else {
            int fail_index = min(returns, count);
            arr_front(int_list, N, fail_index, 1);
            printf("Ascending order breaks on these indexes: %d-%d\n", 
                                                    fail_index-1, fail_index);
        }

        free(int_list);
        free(returns);

        int_list = NULL;
        returns = NULL;

    }else {
        int sorted = 0;
        int n;
        int* arr = NULL;

        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        arr = malloc(n * sizeof(int));
        if (arr == NULL) MPI_Abort(MPI_COMM_WORLD, 11);
        MPI_Recv(arr, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Distribute comparisons across ALL processes
        for (int i = proc_id - 1; i < n - 1; i += (proc_c - 1)) {
            
            // debug print lol
            // printf("Rank: %d compares: %d - %d\n", proc_id, arr[i], arr[i+1]);
            if (arr[i] > arr[i+1]) {
                sorted = i+1;
                break;
            }
        }

        free(arr); 
        MPI_Send(&sorted, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}


