#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include<stdbool.h>

int main(int nargs, char **args) {

    // EXEMPLO:
    //
    // cache = 32
    // bloco = 2
    // associatividade = 8
    //
    // 32 / 2 = 16 / 8 = 2 linhas, cada uma com 8 tags e 8 bits de validade, cada tag uma com 2 blocos

    int hits, misses;
    int total_time = 0;
    int associativity = 8;
    FILE* ptr;

    int cache_size;
    int block_size;
    int time_to_access_cache;
    int time_to_read_dram;
    int time_to_write_dram;

    int number_of_operations;

    int cicle;
    char type_of_cicle;
    long int address;

    ptr = fopen("file.txt", "r");
    if (ptr == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    fscanf(ptr, "%d %d %d %d %d", &cache_size, &block_size, &time_to_access_cache, &time_to_read_dram, &time_to_write_dram);
    fscanf(ptr, "%d", &number_of_operations);
    printf("%d %d %d FIFO WT WNA %d %d %d\n", cache_size, associativity, block_size, time_to_access_cache, time_to_read_dram, time_to_write_dram);

    int number_of_lines = (cache_size / block_size) / associativity;

    if (number_of_lines == 0) {
        printf("Error: cache size is too small\n");
        exit(1);
    }
    
    BLOCO *cache = (BLOCO*) malloc(sizeof(BLOCO) * number_of_lines);
    for (int i = 0; i < number_of_lines; i++) {
        cache[i].time = (int*) malloc(sizeof(int) * associativity);
        cache[i].valid = (int*) malloc(sizeof(int) * associativity);
        cache[i].tag = (int*) malloc(sizeof(int) * associativity);
        cache[i].data = (int*) malloc(sizeof(int) * associativity * block_size);
    }

    for (int i = 0; i < number_of_operations; i++) {
        fscanf(ptr, "%d %c %ld", &cicle, &type_of_cicle, &address);

        if (type_of_cicle == 'R') {
            if (find_item(cache, number_of_lines, associativity, block_size, address)) {
                hits++;
                total_time += time_to_access_cache;
            } else {
                misses++;
                if (!insert_item(cache, number_of_lines, associativity, block_size, address, cicle)) {
                    fifo(cache, number_of_lines, associativity, block_size, address, cicle);
                    insert_item(cache, number_of_lines, associativity, block_size, address, cicle);
                }
                total_time += time_to_read_dram;
                total_time += time_to_access_cache;
            }
        } else if (type_of_cicle == 'W') {
            if (find_item(cache, number_of_lines, associativity, block_size, address)) {
                hits++;
                total_time += time_to_write_dram;
            } else {
                misses++;
                total_time += time_to_write_dram;
            }
        }

    }

    printf("%d\n", total_time);
    printf("%d %d\n", hits, misses);

    print_cache(cache, number_of_lines, associativity, block_size);

    fclose(ptr);

}