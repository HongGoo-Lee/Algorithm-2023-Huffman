#include <stdio.h>
#include "file_input_output.h"
#include "huffman.h"

void test()
{
	char* str;
	str = read_file_str("input.txt");
	int size = get_file_size_ascii("input.txt");
	int* count_ascii;
	count_ascii = get_count_ascii(str,size);
	Huffman* ascii;
	ascii = update_ascii(count_ascii);
	for (int i = 0; i < ascii->size; i++)
	{
		if (i == 0)
		{
			write_ascii("stats.txt", "w", ascii->ascii_value[i], ascii->count[i]);
		}
		else
		{
			write_ascii("stats.txt", "a", ascii->ascii_value[i], ascii->count[i]);
		}
	}
	TNode* root = make_tree("stats.txt");
	print_tree(root);
}