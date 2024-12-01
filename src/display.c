#include "../include/display.h"

// return count of digits in integer
int int_len(int n) {
    
    // For digit 0
    int count = 0;
    if (n == 0) 
        return 1;
    if (n < 0) 
        count++;
    while (n != 0) {
        // Increment count
        count++;
        // Remove last digit from number
        // till number is 0
        n /= 10;
    }

    // return the count of digit
    return count;
}

// user menu
int menu(){

    int pick = 0;
    while (pick != 1 && pick != 2) {
        system("clear");
        printf("Choose action:\n1) Check list\n2) Abort\n");
        read_int(&pick);
    }

    return pick;
}

// display array in nice way
void display_arr(int* arr, int count, int term_index, int num_or_comma){
    // put two brackets in stdout, 
    putchar('[');
    for (int i = 0; i < count; i++) {
        // last int is printed without a comma
        if (i == count-1) { 
            printf("%d",arr[i]); 
            break; 
        }
        printf("%d,",arr[i]);
    }
    putchar(']');
    
    if (term_index != -1) {
        // to flush stdout.
        putchar('\n');
        if (num_or_comma == 0) putchar(' ');
        
        //calculate required white space
        int sum = 0; 
        for (int i = 0; i < term_index; i++){
            sum += int_len(arr[i])+1;
        }

        for (int i = 0; i < sum; i++) {
            printf(" ");
        }
        // print the arrow character after whitespace.
        putchar('^');
    }
    putchar('\n');
}
