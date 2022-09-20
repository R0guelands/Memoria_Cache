#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"
#include <stdbool.h>

void print_cache(int size_of_cache, int size_of_block, int associatividade, int cache[size_of_cache][1 + (1 + size_of_block) * associatividade]) {
    for (int i = 0; i < size_of_cache; i++) {
        for (int j = 0; j < 1 + (1 + size_of_block) * associatividade; j++) {
            printf("%d ", cache[i][j]);
        }
        printf("\n");
    }
}

int define_line(int size_of_cache, int size_of_block, long int address) {
    int line = address & (size_of_cache - 1)<<size_of_block/2;
    return line>>size_of_block/2;
}

int define_block(int size_of_block, long int address) {
    int block = address & (size_of_block - 1);
    return block;
}

bool is_hit(int size_of_cache, int size_of_block, int associatividade, int cache[size_of_cache][1 + (1 + size_of_block) * associatividade], int line, int block, long int address) {
    for (int i = 1; i <= associatividade; i+= 1 + size_of_block) {
        if (cache[line][i] != 0) {
            
        }
    }
    return false;
}