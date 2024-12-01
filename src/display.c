#include "../include/display.h"

int int_len(int n) {
    
    // For digit 0
    if (n == 0) return 1;
    int count = 0;
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

void display_arr(int* arr, int count, int term_index, int num_or_comma){
    putchar('[');
    for (int i = 0; i < count; i++) {
        if (i == count-1) { 
            printf("%d",arr[i]); 
            break; 
        }
        printf("%d,",arr[i]);
    }
    putchar(']');
    
    if (term_index != -1) {
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
        putchar('^');
    }
    putchar('\n');
}