#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <stdbool.h>

int main(int nargs, char **args) {

    // EXEMPLO:
    //
    // cache = 32
    // bloco = 2
    // associatividade = 8
    //
    // 32 / 2 = 16 / 8 = 2 linhas, cada uma com 8 tags e 8 bits de validade, cada tag uma com 2 blocos

    FILE* ptr;

    // All the variables used to read the file and configure the cache, as well as compute hits, misses and other global attributes
    int hits, misses;
    int total_time = 0;
    int associativity = 8;
    int cache_size;
    int block_size;
    int time_to_access_cache;
    int time_to_read_dram;
    int time_to_write_dram;
    int number_of_operations;
    long int cicle;
    char type_of_cicle;
    long int address;

    // Tryes to open the file
    ptr = fopen(args[1], "r");
    if (ptr == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    // Reads the first line of the file, which contains the cache size, block size, associativity, time to access cache, time to read from dram and time to write to dram
    fscanf(ptr, "%d %d %d %d %d", &cache_size, &block_size, &time_to_access_cache, &time_to_read_dram, &time_to_write_dram);
    fscanf(ptr, "%d", &number_of_operations);
    printf("%d %d %d FIFO WT WNA %d %d %d\n", cache_size, associativity, block_size, time_to_access_cache, time_to_read_dram, time_to_write_dram);

    // Calculates the number of lines in the cache
    int number_of_lines = (cache_size / block_size) / associativity;

    // If there are not enough lines in the cache, the program exits
    if (number_of_lines == 0) {
        printf("Error: cache size is too small\n");
        exit(1);
    }
    
    // Creates the cache
    BLOCO *cache = (BLOCO*) malloc(sizeof(BLOCO) * number_of_lines);
    for (int i = 0; i < number_of_lines; i++) {
        cache[i].time = (long int*) malloc(sizeof(long int) * associativity);
        cache[i].valid = (int*) malloc(sizeof(int) * associativity);
        cache[i].tag = (long int*) malloc(sizeof(long int) * associativity);
        cache[i].data = (long int*) malloc(sizeof(long int) * associativity * block_size);
        cache[i].what_to_print = (long int*) malloc(sizeof(long int) * associativity);
    }

    // Main loop, reads the lines from the file containing the values
    for (int i = 0; i < number_of_operations; i++) {

        // Reads the line
        fscanf(ptr, "%ld %c %ld", &cicle, &type_of_cicle, &address);

        // If the line is a read operation
        if (type_of_cicle == 'R') {
            
            // If the address is in the cache, it is a hit  
            if (find_item(cache, number_of_lines, associativity, block_size, address)) {
                hits++;
                total_time += time_to_access_cache;
            
            // If the address is not in the cache, it is a miss
            } else {
                misses++;
                if (!insert_item(cache, number_of_lines, associativity, block_size, address, cicle)) {
                    fifo(cache, number_of_lines, associativity, block_size, address, cicle);
                    insert_item(cache, number_of_lines, associativity, block_size, address, cicle);
                }
                total_time += time_to_read_dram;
                total_time += time_to_access_cache;
            }
        
        // If the line is a write operation
        } else if (type_of_cicle == 'W') {

            // If the address is in the cache, it is a hit
            if (find_item(cache, number_of_lines, associativity, block_size, address)) {
                hits++;
                total_time += time_to_write_dram;

            // If the address is not in the cache, it is a miss
            } else {
                misses++;
                total_time += time_to_write_dram;
            }
        }

    }

    // Prints the results
    printf("%d\n", total_time);
    printf("%d %d\n", hits, misses);
    printf("%d\n", number_of_lines);
    print_weird(cache, number_of_lines, associativity, block_size);

    // Frees the file
    fclose(ptr);

    // Frees the cache
    free_cache(cache, number_of_lines, associativity);

}