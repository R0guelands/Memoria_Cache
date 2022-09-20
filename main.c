#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <stdbool.h>

int main(int nargs, char **args) {

    int *main_memory = (int *) malloc(1 * sizeof(int));
    int numbers_in_main_memory = 0;


    int associatividade = 8;
    FILE* ptr;
    int size_of_cache;
    int size_of_block;
    int time_of_access;
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

    fscanf(ptr, "%d %d %d %d %d", &size_of_cache, &size_of_block, &time_of_access, &time_to_read_dram, &time_to_write_dram);
    fscanf(ptr, "%d", &number_of_operations);
    printf("%d %d %d %d %d\n", size_of_cache, size_of_block, time_of_access, time_to_read_dram, time_to_write_dram);
    printf("%d\n", number_of_operations);

    int cache[size_of_cache][1 + (1 + size_of_block) * associatividade];

    for (int i = 0; i < size_of_cache; i++) {
        for (int j = 0; j < 1 + (1 + size_of_block) * associatividade; j++) {
            if (j == 0) {
                cache[i][j] = i;
            } else {
                cache[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < number_of_operations; i++) {
        fscanf(ptr, "%d %c %ld", &cicle, &type_of_cicle, &address);
        printf("%d %c %ld  ", cicle, type_of_cicle, address);
        printf("Line:%d; Block:%d; ", define_line(size_of_cache, size_of_block, address), define_block(size_of_block, address));
        if (is_hit(size_of_cache, size_of_block, associatividade, cache, define_line(size_of_cache, size_of_block, address), address)) {
            printf("hit\n");
            if (type_of_cicle == 'W') {
                main_memory[numbers_in_main_memory] = address;
                numbers_in_main_memory++;
                main_memory = (int *) realloc(main_memory, (numbers_in_main_memory + 1) * sizeof(int));
            }
            
        } else {
            printf("miss\n");
            if (type_of_cicle == 'W') {
                main_memory[numbers_in_main_memory] = address;
                numbers_in_main_memory++;
                main_memory = (int *) realloc(main_memory, (numbers_in_main_memory + 1) * sizeof(int));
            }
        }
    }

    print_cache(size_of_cache, size_of_block, associatividade, cache);

    fclose(ptr);

}