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
    int biggest_index = 0;
    for (int i = 0; i < associativity; i++) {
        if (cache[index].time[i] > biggest_index) {
            biggest_index = i;
        }
    }
    cache[index].time[biggest_index] = 0;
    cache[index].valid[biggest_index] = 0;
    cache[index].tag[biggest_index] = 0;
    for (int i = 0; i < block_size; i++) {
        cache[index].data[biggest_index * block_size + i] = 0;
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

void increment_time(BLOCO *cache, int number_of_lines, int associativity, int block_size, int cicle) {
    for (int i = 0; i < number_of_lines; i++) {
        for (int j = 0; j < associativity; j++) {
            if (cache[i].valid[j] == 1) {
                cache[i].time[j]++;
            }
        }
    }
}