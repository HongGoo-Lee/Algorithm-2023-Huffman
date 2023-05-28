#pragma once
typedef struct _huffman {
	char* ascii_value;
	int* count;
	int size;
}Huffman;

typedef struct _node {
	char ascii_value;
	int count;
	struct _node* left;
	struct _node* right;
}TNode;

typedef struct _a {
	char ascii_value;
	int count;
	TNode* left;
	TNode* right;
}Ascii;

TNode* make_tree(char* fname);
int* get_count_ascii(char* str,int size);
Huffman* update_ascii(int* ascii);
void print_tree(TNode* root);