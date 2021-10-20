// Name:            Williams, Cade
// Email:           cwil396@lsu.edu
// Project:         PA-1 (Multithreading)
// Instructor:      Feng Chen
// Class:           cs4103-sp21
// Login ID:        cs4013ap
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct 
{
    int row;
    int column;
    int subgrid;
} parameters;

// Initialize matrix for sudoku values
int smat[9][9];

// Reads input value and assigns all values to matrix smat
void read_file(char * input_file)
{
    FILE *fp = fopen(input_file, "r");

    for(int i = 0; i < 9; i++)
    {
        fscanf(fp, "%d %d %d %d %d %d %d %d %d/n", &smat[i][0], &smat[i][1], &smat[i][2], &smat[i][3], &smat[i][4], &smat[i][5], &smat[i][6], &smat[i][7], &smat[i][8]);
    }
}

// Prints Valid if column is valid, Else Invalid
void *validate_column(void *ptr)
{
    parameters *data = (parameters *)ptr;
    
    int cell[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for(int i = 0; i < 9; i++)
    {
        switch(smat[i][data->column])
        {
            case 1: cell[0]++; break;
            case 2: cell[1]++; break;
            case 3: cell[2]++; break;
            case 4: cell[3]++; break;
            case 5: cell[4]++; break;
            case 6: cell[5]++; break;
            case 7: cell[6]++; break;
            case 8: cell[7]++; break;
            case 9: cell[8]++; break;
        }
    }

    bool valid = true;
    for(int i = 0; i < 9; i++)
    {
        if(cell[i] != 1)
        {
            valid = false;
        }
    }

    printf("Thread %ld, Column %d, %s\r\n", pthread_self(), data->column, valid ? "Valid" : "Invalid");
    pthread_exit(NULL);
}

// Prints Valid if row is valid, Else Invalid
void *validate_row(void *ptr)
{
    parameters *data = (parameters *)ptr;
    
    int cell[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for(int i = 0; i < 9; i++)
    {
        switch(smat[data->row][i])
        {
            case 1: cell[0]++; break;
            case 2: cell[1]++; break;
            case 3: cell[2]++; break;
            case 4: cell[3]++; break;
            case 5: cell[4]++; break;
            case 6: cell[5]++; break;
            case 7: cell[6]++; break;
            case 8: cell[7]++; break;
            case 9: cell[8]++; break;
        }
    }

    bool valid = true;
    for(int i = 0; i < 9; i++)
    {
        if(cell[i] != 1)
        {
            valid = false;
        }
    }

    printf("Thread %ld, Row %d, %s\r\n", pthread_self(), data->row, valid ? "Valid" : "Invalid");
    pthread_exit(NULL);
}

// Prints Valid if subgrid is valid, Else Invalid
void *validate_subgrid(void *ptr)
{
    parameters *data = (parameters *)ptr;
    
    int cell[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int ind_row = (data->subgrid % 3) * 3;
    int ind_col = data->subgrid < 3 ? 0 : data->subgrid < 6 ? 3 : 6;
    for(int i = ind_row; i < ind_row + 3; i++) // Iterate through rows of subgrid
    {
        for(int j = ind_col; j < ind_col + 3; j++) // Iterate through column of subgrid
        {
            switch(smat[j][i])
            {
                case 1: cell[0]++; break;
                case 2: cell[1]++; break;
                case 3: cell[2]++; break;
                case 4: cell[3]++; break;
                case 5: cell[4]++; break;
                case 6: cell[5]++; break;
                case 7: cell[6]++; break;
                case 8: cell[7]++; break;
                case 9: cell[8]++; break;
            }
        }
    }

    bool valid = true;
    for(int i = 0; i < 9; i++)
    {
        if(cell[i] != 1)
        {
            valid = false;
        }
    }

    printf("Thread %ld, Subgrid %d, %s\r\n", pthread_self(), data->column, valid ? "Valid" : "Invalid");
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if(argv[1] == NULL)
    {
        printf("ERROR: No input file\r\n");
        return 0;
    }

    read_file(argv[1]);
    pthread_t column_pt, row_pt, sgrid_pt;
    parameters *data = (parameters*)malloc(sizeof(parameters));
    
    for(int i = 0; i < 9; i++)
    {
        data->row = i;
        data->column = i;
        data->subgrid = i;
        
        // Thread creation
        pthread_create(&column_pt, NULL, validate_column, (void *)data);
        pthread_create(&row_pt, NULL, validate_row, (void *)data);
        pthread_create(&sgrid_pt, NULL, validate_subgrid, (void *)data);

        // Syncronization technique
        pthread_join(column_pt, NULL);
        pthread_join(row_pt, NULL);
        pthread_join(sgrid_pt, NULL);
    }

    return 0;
}


