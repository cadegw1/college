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
        fclose(disk[i]);
    }
}

void write(void)
{

}

void read(void)
{

}

void rebuild(void)
{

}

enum cmd{NUM_DISK = 1, BLOCK_SIZE = 2, COMMAND = 3, INPUT = 4};

int main(int argc, char *argv[])
{
    int num_disks = 0;
    int block_size = 0;
    char * command = "";
    char * input = "";

    // Retrieve command line arguments
    if(argc != 5)
    {
        printf("ERROR: Four arguments expected");
    }
    else
    {
        num_disks = atoi(argv[NUM_DISK]);
        block_size = atoi(argv[BLOCK_SIZE]);
        command = argv[COMMAND];
        input = argv[INPUT];
    }

    clean_dir();
    create_files(num_disks);
    if(argv[COMMAND] == "write")
    {
        write();
    }
    else if(argv[COMMAND] == "read")
    {
        read();
    }
    else if(argv[COMMAND] == "rebuild")
    {
        rebuild();
    }

    return 0;
}