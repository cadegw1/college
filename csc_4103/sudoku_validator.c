// Name:            Williams, Cade
// Email:           cwil396@lsu.edu
// Project:         PA-1 (Multithreading)
// Instructor:      Feng Chen
// Class:           cs4103-sp21
// Login ID:        cs4013ap
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct 
{
    int row;
    int column;
} parameters;

// Initialize matrix for sudoku values
int smat[9][9];

// Reads input value and assigns all values to matrix smat
void read_file(void)
{
    FILE *fp = fopen("solution.txt", "r");

    for(int i = 0; i < 9; i++)
    {
        fscanf(fp, "%d %d %d %d %d %d %d %d %d/n", &smat[i][0], &smat[i][1], &smat[i][2], &smat[i][3], &smat[i][4], &smat[i][5], &smat[i][6], &smat[i][7], &smat[i][8]);
    }
}

int main(void)
{
    read_file();
    pthread_t column, row;
    pthread_t sgrid[9];
    int ret[11];

    parameters *data = (parameters*)malloc(sizeof(parameters));
    data->row = 1;
    data->column = 1;

    return 0;
}


