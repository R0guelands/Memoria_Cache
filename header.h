#include<stdbool.h>

typedef struct bloco {
    int *time;
    int *valid;
    int *tag;
    int *data;
} BLOCO;

void print_cache(BLOCO *cache, int number_of_lines, int associativity, int block_size);\

int define_offset(int block_size, long int address);

int define_index(int number_of_lines, int block_size, long int address);

int define_tag(int number_of_lines, int block_size, long int address);

bool insert_item(BLOCO *cache, int number_of_lines, int associativity, int block_size, long int address, int cicle);

void fifo(BLOCO *cache, int number_of_lines, int associativity, int block_size, long int address, int cicle);

bool find_item(BLOCO *cache, int number_of_lines, int associativity, int block_size, long int address);
