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

#define FILENAME_SIZE       100

// Function removes old disk files in the current directory 
void clean_dir(void)
{
    FILE *old_disk;
    int i = 0;
    char filename[FILENAME_SIZE];
    sprintf(filename, "disk.%d", i++);
    while(old_disk = fopen(filename, "r"))
    {
        fclose(old_disk);
        remove(filename);
        sprintf(filename, "disk.%d", i++);
    } 
    printf("Removed old disk files\r\n");
}

// Creates all necessary files
void create_files(int disk_amt)
{
    // Create files
    FILE *disk[disk_amt];
    char filename[FILENAME_SIZE];
    for(int i = 0; i < disk_amt; i++)
    {
        sprintf(filename, "disk.%d", i);
        disk[i] = fopen(filename, "w+");
        fprintf(disk[i], "bruh");
        fclose(disk[i]);
    }
}

int main(int argc, char *argv[])
{
    int num_disks = 0;
    int block_size = 0;
    char * command = "";
    char * file_name = "";

    // Retrieve command line arguments
    if(argc != 5)
    {
        printf("ERROR: Four arguments expected");
    }
    else
    {
        num_disks = atoi(argv[1]);
        block_size = atoi(argv[2]);
        command = argv[3];
        file_name = argv[4];
    }

    clean_dir();
    // create_files(num_disks);

    return 0;
}