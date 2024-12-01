#ifndef UTILS_H
#define UTILS_H

#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// Fill array with ints (user input)
void fill_array(int* arr, int count); 

// Basic util, find minimum number in array
int min(int* arr, int count);

//Read int from user in a safe manner
void read_int(int* target);

#endif
