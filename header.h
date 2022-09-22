#include<stdbool.h>

// Struct to represent a cache block
typedef struct bloco {
    int *time; // Time (cicle) where the block was inserted
    int *valid; // 1 if the block is valid, 0 otherwise
    int *tag; // Tag of the block
    int *data; // Data of the block, represented by an array of integers
    int what_to_print;
} BLOCO;

// Pints the cache
void print_cache(BLOCO *cache, int number_of_lines, int associativity, int block_size);

// Defines the offset, by using the block size -1 as mask
int define_offset(int block_size, long int address);

// Defines the index, by using the number of lines -1 as mask and shifting the result to the right
int define_index(int number_of_lines, int block_size, long int address);

// Defines the tag, by shifting the address to the right
int define_tag(int number_of_lines, int block_size, long int address);

// Inserts and item based on the tag and index
bool insert_item(BLOCO *cache, int number_of_lines, int associativity, int block_size, long int address, int cicle);

// Replaces the item based on the FIFO algorithm
void fifo(BLOCO *cache, int number_of_lines, int associativity, int block_size, long int address, int cicle);

// Checks if the item is in the cache
bool find_item(BLOCO *cache, int number_of_lines, int associativity, int block_size, long int address);

// Free the cache
void free_cache(BLOCO *cache, int number_of_lines, int associativity);

void print_weird(BLOCO *cache, int number_of_lines, int associativity, int block_size);
