#include "huffman.h"

typedef Ascii Element;

typedef struct LinkedNode {
	Element data;
	struct LinkedNode* link;
}Node;

typedef struct _list {
	Node* head;
}LinkedList;

Node delete(int pos, LinkedList* l);
void insert(int pos, Element e, LinkedList* l);
int size(LinkedList* l);
void init_list(LinkedList* l);
Node* get_entry(int pos, LinkedList* l);
void sort_list(LinkedList* l);
int is_empty(LinkedList* l);
void print_list(LinkedList* l);