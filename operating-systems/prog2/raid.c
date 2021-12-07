// Name:        Williams, Cade
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
        printf("Removed old disk files\r\n");
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
    printf("Wrote to disks\r\n");
}

void read(int const disk_amt, int const block_size, char * output)
{
    char buff[BUFFER_SIZE];
    char filename[FILENAME_MAX];

    // Open files
    FILE *disk[disk_amt];
    for(int i = 0; i < disk_amt; i++)
    {
        sprintf(filename, "disk.%d", i);
        disk[i] = fopen(filename, "r");
    }
    FILE *out;
    out = fopen(output, "w");

    // Read all data from disks and write to output file
    int i = 0;
    int parity_disk = disk_amt - 1;
    while((fgets(buff, block_size + 4, disk[i]) != NULL))
    {
        if(parity_disk == -1 && i == 0)
        {
            parity_disk = disk_amt - 1;
        }

        if(i != parity_disk)
        {
            fprintf(out, "%s", buff);
        }
        else
        {
            parity_disk = parity_disk - 1;
        }
        i = (i + 1) % disk_amt;
    }
    
    // Close all files
    fclose(out);
    for(int j = 0; j < disk_amt; j++)
    {
        fclose(disk[j]);
    }
    printf("Data read to: %s\r\n", output);
}

void rebuild(int const disk_amt, int const block_size, char * rebuild_disk)
{
    remove(rebuild_disk);
    char filename[FILENAME_MAX];
    int num_rdisk = atoi(rebuild_disk + 5);
    char buff[BUFFER_SIZE];

    // Open files
    FILE *disk[disk_amt];
    for(int i = 0; i < disk_amt; i++)
    {
        sprintf(filename, "disk.%d", i);
        if(i != num_rdisk)
        {
            disk[i] = fopen(filename, "r");
        }
        else
        {
            disk[num_rdisk] = fopen(filename, "a");
        }
    }

    // XOR data blocks from member disks
    int i = num_rdisk == 0 ? 1 : 0;
    char result[BUFFER_SIZE] = {0};
    while((fgets(buff, block_size + 4, disk[i]) != NULL) || i == num_rdisk)
    {
        if(i != num_rdisk)
        {
            char temp;
            for(int ch = 0; ch < block_size; ch++)
            {
                temp = result[ch] ^ buff[ch];
                result[ch] = (char)temp;    
            }
        }
        
        if(i == disk_amt - 1)
        {
            fprintf(disk[num_rdisk], "%s\r\n", result);
            memset(result, 0, sizeof(result));
        }
        i = (i + 1) % disk_amt;
    }

    // Close all files
    for(int j = 0; j < disk_amt; j++)
    {
        fclose(disk[j]);
    }
    printf("Rebuilt %s\r\n", rebuild_disk);
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
            clean_dir();
            write(num_disks, block_size, file);
        }
        else if(strcmp(command, "read") == 0)
        {
            read(num_disks, block_size, file);
        }
        else if(strcmp(command, "rebuild") == 0)
        {
            if(strncmp(file, "disk", 4) != 0 || atoi(file + 5) > num_disks - 1)
            {
                printf("Invalid file: %s\r\n", file);
            }
            else
            {
                rebuild(num_disks, block_size, file);
            }
        }
    }

    return 0;
}