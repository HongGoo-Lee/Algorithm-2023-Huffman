#pragma once
#include "huffman.h"

char* read_file_str(char* fname);
int get_file_size(char* fname);
int get_file_size_ascii(char* fname);
void write_ascii(char* fname, char* mode, char ascii, int count);
int get_file_line_count(char* fname);
Huffman* get_file_data(char* fname);
Huffman* get_sort_data(char* fname);