#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "huffman.h"
#include "file_input_output.h"

int* get_count_ascii(char* str,int size)
{
	int tmp = 0;
	int* ascii = (int*)calloc(128, sizeof(int));
	for (int i = 0; i < size; i++)
	{
		if (str[i] >= 0 && str[i] < 128)
		{
			tmp = str[i];
			ascii[tmp]++;
		}
	}
	return ascii;
}

Huffman* update_ascii(int* ascii)
{
	int i = 0, j = 0;
	for (i = 0; i < 128; i++)
	{
		if (ascii[i] > 0)
		{
			j++;
		}
	}
	Huffman* res = (Huffman*)calloc(1, sizeof(Huffman));
	res->count = (int*)calloc(j, sizeof(int));
	res->ascii_value = (char*)calloc(j, sizeof(char));
	res->size = j;
	j = 0;
	for (i = 0; i < 128; i++)
	{
		if (ascii[i] > 0)
		{
			res->count[j] = ascii[i];
			res->ascii_value[j] = i;
			j++;
		}
	}
	return res;
}

TNode* make_node(char ascii_value, int count, TNode* left, TNode* right)
{
	TNode* node = (TNode*)calloc(1, sizeof(TNode));
	node->ascii_value = ascii_value;
	node->count = count;
	node->left = left;
	node->right = right;

	return node;
}

TNode* make_tree(char* fname)
{
	Huffman* data = get_sort_data(fname);
	int i = 0;
	LinkedList list;
	Node n1, n2;
	Ascii tmp;
	init_list(&list);
	for (i = 0; i < data->size; i++)
	{
		tmp.ascii_value = data->ascii_value[i];
		tmp.count = data->count[i];
		tmp.left = NULL;
		tmp.right = NULL;
		insert(0, tmp, &list);
	}
	sort_list(&list);

	TNode* node1, * node2, * node3 = NULL;
	for(i=0; i<data->size; i++)
	{
		sort_list(&list);
		print_list(&list);
		n1 = delete(0, &list);
		n2 = delete(1, &list);
		node1 = make_node(n1.data.ascii_value, n1.data.count, n1.data.left, n1.data.right);
		node2 = make_node(n2.data.ascii_value, n2.data.count, n2.data.left, n2.data.right);
		node3 = make_node(94, node1->count + node2->count, node1, node2);

		tmp.ascii_value = node3->ascii_value;
		tmp.count = node3->count;
		tmp.left = node3->left;
		tmp.right = node3->right;
		insert(0, tmp, &list);
	}

	return node3;
}

void print_tree(TNode* root)
{
	if (root != NULL)
	{
		printf("%c\t%d\n", root->ascii_value, root->count);
		print_tree(root->left);
		print_tree(root->right);
	}
}