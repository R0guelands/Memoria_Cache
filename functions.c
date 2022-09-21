#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"
#include<stdbool.h>

void print_cache(BLOCO *cache, int number_of_lines, int associativity, int block_size) {
    for (int i = 0; i < number_of_lines; i++) {
        printf("line %d: | ", i);
        for (int j = 0; j < associativity; j++) {
            printf("%d ", cache[i].time[j]);
            printf("%d ", cache[i].valid[j]);
            printf("%d ", cache[i].tag[j]);
            for (int k = 0; k < block_size; k++) {
                printf("%d ", cache[i].data[j * block_size + k]);
            }
            printf(" | ");
        }
        printf("\n");
    }
}

int define_offset(int block_size, long int address) {
    int offset = address & (block_size - 1);
    return offset;
}

int define_index(int number_of_lines, int block_size, long int address) {
    int index = address & ((number_of_lines - 1) << block_size / 2);
    return index>>block_size/2;
}

int define_tag(int number_of_lines, int block_size, long int address) {
    return address >> (block_size / 2 + number_of_lines / 2);
}

void fifo(BLOCO *cache, int number_of_lines, int associativity, int block_size, long int address, int cicle) {
    int index = define_index(number_of_lines, block_size, address);
    int biggest_index = 821347982;
    int index_to_replace = 0;
    for (int i = 0; i < associativity; i++) {
        if (cache[index].time[i] < biggest_index) {
            biggest_index = cache[index].time[i];
            index_to_replace = i;
        }
    }
    cache[index].time[index_to_replace] = 0;
    cache[index].valid[index_to_replace] = 0;
    cache[index].tag[index_to_replace] = 0;
    for (int i = 0; i < block_size; i++) {
        cache[index].data[index_to_replace * block_size + i] = 0;
    }
}

bool insert_item(BLOCO *cache, int number_of_lines, int associativity, int block_size, long int address, int cicle) {
    int index = define_index(number_of_lines, block_size, address);
    int tag = define_tag(number_of_lines, block_size, address);
    for (int i = 0; i < associativity; i++) {
        if (cache[index].valid[i] == 0) {
            cache[index].time[i] = cicle;
            cache[index].valid[i] = 1;
            cache[index].tag[i] = tag;
            address = address & (~0 << (block_size/2));
            for (int j = 0; j < block_size; j++) {
                cache[index].data[i * block_size + j] = address;
                address++;
            }
            return true;
        }
    }
    return false;
}

bool find_item(BLOCO *cache, int number_of_lines, int associativity, int block_size, long int address) {
    int index = define_index(number_of_lines, block_size, address);
    int tag = define_tag(number_of_lines, block_size, address);
    for (int i = 0; i < associativity; i++) {
        if (cache[index].valid[i] == 1 && cache[index].tag[i] == tag) {
            return true;
        }
    }
    return false;
}

void free_cache(BLOCO *cache, int number_of_lines, int associativity) {
    for (int i = 0; i < number_of_lines; i++) {
        free(cache[i].time);
        free(cache[i].valid);
        free(cache[i].tag);
        free(cache[i].data);
    }
    free(cache);
}