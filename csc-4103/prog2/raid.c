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
    remove("output");

    if(i != 1)
    {
        printf("Removed old disk files ...\r\n");
    }
}
    

// Creates all necessary files
void create_files(int const disk_amt)
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

void write(int const disk_amt, int const block_size, char * input)
{
    // Initialize input data file
    char buff[BUFFER_SIZE];
    FILE *input_data;
    input_data = fopen(input, "r");

    // Initialize disk file array
    FILE *disk[disk_amt];
    char filename[FILENAME_MAX];

    // Add way to know when to skip writing to calculate parity block
    int parity_disk = disk_amt - 1;
    while((fgets(buff, ((block_size) * (disk_amt - 1)) + 1, input_data)) != NULL)
    {
        // Pads data with zeros if it does not fit
        char zeros[block_size * (disk_amt - 1)];
        if(strlen(buff) != block_size * (disk_amt - 1))
        {
            for(int p = 0; p <= block_size * (disk_amt - 1); p++)
            {
                zeros[p] = '0';
                if(p == block_size * (disk_amt - 1))
                {
                    zeros[p] = '\0';
                }
            }
            int diff = (block_size * (disk_amt - 1)) - strlen(buff);
            strcat(buff, zeros);
        }

        // Write data into data disks
        int disks_accessed = 0;
        char disk_data[BUFFER_SIZE];
        for(int j = 0; j < disk_amt; j++)
        {
            if(j != parity_disk)
            {
                sprintf(filename, "disk.%d", j);
                disk[j] = fopen(filename, "a");
                memcpy(disk_data, buff + (block_size * disks_accessed), block_size);
                fprintf(disk[j], "%s\r\n", disk_data);
                fclose(disk[j]);
                disks_accessed++;
            }

            // On final iteration, calculate parity data
            char parity_data[BUFFER_SIZE] = {0};
            if(j == disk_amt - 1)
            {
                disks_accessed = 0;
                for(int curr_disk = 0; curr_disk < disk_amt; curr_disk++)
                {
                    if(curr_disk == parity_disk)
                    {
                        continue;
                    }
                    else
                    {
                        char temp;
                        for(int ch = 0; ch < block_size; ch++)
                        {
                            temp = parity_data[ch] ^ buff[ch + (disks_accessed * block_size)];
                            parity_data[ch] = (char)temp;    
                        }
                    }
                    disks_accessed++;
                }

                // Write parity data to parity disk
                FILE *pdisk;
                sprintf(filename, "disk.%d", parity_disk);
                pdisk = fopen(filename, "a");
                fprintf(pdisk, "%s\r\n", parity_data);
                fclose(pdisk);
            }
        }

        if(parity_disk == 0)
        {
            parity_disk = disk_amt - 1;
        }
        else
        {
            parity_disk--;
        }
    }
    fclose(input_data);
}

void read(int const disk_amt, int const block_size, char * output)
{
    FILE *disk[disk_amt];
    char buff[BUFFER_SIZE];
    char filename[FILENAME_MAX];

    // Open files
    for(int i = 0; i < disk_amt; i++)
    {
        sprintf(filename, "disk.%d", i);
        disk[i] = fopen(filename, "r");
    }
    FILE *out;
    out = fopen("output", "w");

    // Read all data from disks and write to output file
    int i = 0;
    int parity_disk = disk_amt - 1;
    while((fgets(buff, block_size + 4, disk[i]) != NULL))
    {
        fprintf(out, "%s", buff);
        i = (i + 1) % disk_amt;
        if(i == parity_disk)
        {
            i = (i + 1) % disk_amt;
            parity_disk = parity_disk - 1;
            if(parity_disk == -1)
            {
                parity_disk = disk_amt - 1;
            }
        }
    }
    
    // Close all files
    fclose(out);
    for(int j = 0; j < disk_amt; j++)
    {
        fclose(disk[j]);
    }
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
        
        if(strcmp(command, "write") == 0)
        {
            // create_files(num_disks);
            clean_dir();
            write(num_disks, block_size, file);
        }
        else if(strcmp(command, "read") == 0)
        {
            read(num_disks, block_size, file);
        }
        else if(strcmp(command, "rebuild") == 0)
        {
            rebuild(file);
        }
    }

    return 0;
}