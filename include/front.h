#ifndef FRONT_H
#define FRONT_H

#include <stdio.h>
#include <string.h>

// Get length of array
int int_len(int n); 

// Print front in nicer way, 
// optional index (^) to point at element of choice (-1 to disable)
// num_or_comma to specify, point to num, or between nums (0 - on num, 1 - between, -1 - ignore)
void arr_front(int* arr, int count, int term_index, int num_or_comma);

#endif
