#include <stdio.h>
#include <stdlib.h>
#include "list.h"


void init_list(LinkedList*l) { l->head = NULL; };
int is_empty(LinkedList* l) { return l->head == NULL; };

Node* get_entry(int pos, LinkedList* l)
{
	Node* p = l->head;
	int i;
	for (i = 0; i < pos; i++, p = p->link)
		if (p == NULL)
			return NULL;
	return p;
}

int size(LinkedList* l)
{
	Node* p;
	int count = 0;
	for (p = l->head; p != NULL; p = p->link)
		count++;
	return count;
}

void replace(int pos, Element e, LinkedList* l)
{
	Node* node = get_entry(pos,l);
	if (node != NULL)
		node->data = e;
}

void insert_next(Node* before, Node* node)
{
	if (node != NULL)
	{
		node->link = before->link;
		before->link = node;
	}
}

void insert(int pos, Element e, LinkedList* l)
{
	Node* new_node, * prev;

	new_node = (Node*)malloc(sizeof(Node));
	new_node->data = e;
	new_node->link = NULL;

	if (pos == 0)
	{
		new_node->link = l->head;
		l->head = new_node;
	}
	else
	{
		prev = get_entry(pos - 1,l);
		if (prev != NULL)
			insert_next(prev, new_node);
		else
			free(new_node);
	}
}

Node* remove_next(Node* before)
{
	Node* removed = before->link;
	if (removed != NULL)
		before->link = removed->link;
	return removed;
}

Node delete(int pos, LinkedList* l)
{
	Node* prev, * removed;
	Node res;

	if (pos == 0 && is_empty(l) == 0)
	{
		removed = l->head;
		l->head = l->head->link;
		if (removed != NULL)
		{
			res.data = removed->data;
			res.link = removed->link;
		}
		free(removed);
	}
	else
	{
		prev = get_entry(pos - 1,l);
		if (prev != NULL)
		{
			removed = remove_next(prev);
			if (removed != NULL)
			{
				res.data = removed->data;
				res.link = removed->link;
			}
			free(removed);
		}
	}

	return res;
}

void clear_list(LinkedList* l)
{
	while (is_empty(l) == 0)
		delete(0,l);
}

void copy_node(Node* n1, Node* n2)
{
	n1->data = n2->data;
	n1->link = n2->link;
}

void sort_list(LinkedList* l)
{
	Node* node, * node2,tmp,tmp2;

	for (int i = 0; i < size(l)-1; i++)
	{
		node = get_entry(i, l);
		for (int j = i + 1; j < size(l); j++)
		{
			node2 = get_entry(j, l);
			if (node->data.count > node2->data.count)
			{
				copy_node(&tmp, node);
				copy_node(&tmp2, node2);

				delete(j, l);
				insert(j, tmp.data, l);

				delete(i, l);
				insert(i, tmp2.data, l);
			}
		}
	}
}

void print_list(LinkedList*l)
{
	Node* p;
	printf("리스트\n");
	for (p = l->head; p != NULL; p = p->link)
		printf("%c\t%d\n", p->data.ascii_value, p->data.count);
	printf("끝\n");
}