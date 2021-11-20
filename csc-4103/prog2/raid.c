// Name:        Cade Williams
// Email:       cwil396@lsu.edu
// Project:     PA-2 (RAID)
// Instructor:  Feng Chen
// Class:       cs4103-au21
// Login ID:    cs4103ap

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE     4096

// Function removes old disk files in the current directory 
void clean_dir(void)
{
    FILE *old_disk;
    int i = 0;
    char filename[FILENAME_MAX];
    sprintf(filename, "disk.%d", i++);
    while(old_disk = fopen(filename, "r"))
    {
        fclose(old_disk);
        remove(filename);
        sprintf(filename, "disk.%d", i++);
    } 
    if(i != 1)
    {
        printf("Removed old disk files ...\r\n");
    }
}
    

// Creates all necessary files
void create_files(int disk_amt)
{
    // Create files
    FILE *disk[disk_amt];
    char filename[FILENAME_MAX];
    for(int i = 0; i < disk_amt; i++)
    {
        sprintf(filename, "disk.%d", i);
        disk[i] = fopen(filename, "w+");
        fclose(disk[i]);
    }
}

void write(int disk_amt, int block_size, char * input)
{
    // Initialize input data file
    char buff[BUFFER_SIZE];
    FILE *input_data;
    input_data = fopen(input, "r");

    // Initialize disk file array
    FILE *disk[disk_amt];
    char filename[FILENAME_MAX];

    // Add way to know when to skip writing to calculate parity block
    int i = 0;
    while((fgets(buff, block_size + 1, input_data)) != NULL)
    {
        sprintf(filename, "disk.%d", i);
        disk[i] = fopen(filename, "w");
        // fprintf(disk);
        fclose(disk[i]);
    }
    fclose(input_data);
}

void read(char * output)
{

}

void rebuild(char * disk)
{

}

int main(int argc, char *argv[])
{
    int num_disks = 0;
    int block_size = 0;
    char * command = "";
    char * file = "";

    // Retrieve command line arguments
    clean_dir();
    if(argc != 5)
    {
        printf("ERROR: Four arguments expected\r\n");
    }
    else
    {
        num_disks = atoi(argv[1]);
        block_size = atoi(argv[2]);
        command = argv[3];
        file = argv[4];

        create_files(num_disks);
        if(strcmp(command, "write") == 0)
        {
            write(num_disks, block_size, file);
        }
        else if(strcmp(command, "read") == 0)
        {
            read(file);
        }
        else if(strcmp(command, "rebuild") == 0)
        {
            rebuild(file);
        }
    }

    return 0;
}