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

bool create_files(int disk_amt)
{
    // Create files
    FILE *disk[disk_amt];
    char * filename = "";
    for(int i = 0; i < disk_amt; i++)
    {
        sprintf(filename, "%d", i);
        disk[i] = fopen(strcat("disk.", filename), "w+");
    }


    // Close files
    for(int i = 0; i < disk_amt; i++)
    {
        fclose(disk[i]);
    }

    return true;
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
        printf("ERROR: Incorrect number of inputs");
    }
    else
    {
        num_disks = atoi(argv[1]);
        block_size = atoi(argv[2]);
        command = argv[3];
        file_name = argv[4];
    }

    printf("%d %d %s %s\r\n\r\n", num_disks, block_size, command, file_name);

    return 0;
}