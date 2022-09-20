#include <stdbool.h>

void print_cache(int size_of_cache, int size_of_block, int associatividade, int cache[size_of_cache][1 + (1 + size_of_block) * associatividade]);

int define_line(int size_of_cache, int size_of_block, long int address);

int define_block(int size_of_block, long int address);

bool is_hit(int size_of_cache, int size_of_block, int associatividade, int cache[size_of_cache][1 + (1 + size_of_block) * associatividade], int line, int block long int address);

void add_to_cache(int size_of_cache, int size_of_block, int associatividade, int cache[size_of_cache][1 + (1 + size_of_block) * associatividade], int line, long int address);