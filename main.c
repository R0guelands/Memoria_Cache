#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(int nargs, char **args) {
    FILE* ptr;
    int size_of_cache;
    int size_of_block;
    int time_of_access;
    int time_to_read_dram;
    int time_to_write_dram;

    int number_of_sets;

    int cicle;
    char type_of_cicle;
    long int address;

    ptr = fopen("file.txt", "r");
    if (ptr == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    fscanf(ptr, "%d %d %d %d %d", &size_of_cache, &size_of_block, &time_of_access, &time_to_read_dram, &time_to_write_dram);
    fscanf(ptr, "%d", &number_of_sets);
    printf("%d %d %d %d %d\n", size_of_cache, size_of_block, time_of_access, time_to_read_dram, time_to_write_dram);
    printf("%d\n", number_of_sets);
    for (int i = 0; i < number_of_sets; i++) {
        fscanf(ptr, "%d %c %ld", &cicle, &type_of_cicle, &address);
        printf("%d %c %ld\n", cicle, type_of_cicle, address);
    }

    fclose(ptr);

}