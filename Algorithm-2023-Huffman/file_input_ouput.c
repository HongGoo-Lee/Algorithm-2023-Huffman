#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

static int check_file(char* fname)
{
	FILE* fp = NULL;
	fp = fopen(fname, "r");
	if (fp == NULL)
		return -1;//파일이 없음
	fclose(fp);
	return 0;//파일이 있음
}

char* read_file_str(char* fname)
{
	FILE* fp = NULL;
	if (check_file(fname) < 0)
	{
		printf("파일이 없습니다.\n");
		exit(1);
	}
	fp = fopen(fname, "r");
	int i = 0;
	char c = 0;
	while (!feof(fp))
	{
		c = fgetc(fp);
		if (c >= 0 && c < 128)
		{
			i++;
		}
	}
	char* str = (char*)calloc(19,sizeof(char));

	fseek(fp, 0, SEEK_SET);
	i = 0;
	while (!feof(fp))
	{
		c = fgetc(fp);
		if (c >= 0 && c < 128)
		{
			str[i] = c;
			i++;
		}
	}
	fclose(fp);

	return str;
}

int get_file_size(char* fname)
{
	int i = 0;
	FILE* fp = fopen(fname, "r");
	while (!feof(fp))
	{
		fgetc(fp);
		i++;
	}
	fclose(fp);
	return i;
}

int get_file_size_ascii(char* fname)
{
	int i = 0;
	char c = 0;
	FILE* fp = fopen(fname, "r");
	while (!feof(fp))
	{
		c = fgetc(fp);
		if (c >= 0 && c < 128)
			i++;
	}
	fclose(fp);
	return i;
}

int get_file_line_count(char* fname)
{
	FILE* fp = fopen(fname,"r");
	char c = 0;
	int d = 0, i = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%c\t%d\n", &c, &d);
		i++;
	}
	fclose(fp);
	return i;
}

void write_ascii(char* fname, char* mode, char ascii, int count)
{
	FILE* fp = NULL;
	fp = fopen(fname, mode);
	fprintf(fp, "%c\t%d\n", ascii, count);
	fclose(fp);
}

Huffman* get_file_data(char* fname)
{
	Huffman* r = (Huffman*)calloc(1, sizeof(Huffman));
	int size = get_file_line_count(fname);
	r->size = size;
	r->ascii_value = (char*)calloc(size, sizeof(char));
	r->count = (int*)calloc(size, sizeof(int));
	FILE* fp = fopen(fname, "r");
	int count;
	char c;
	for (int i = 0; i < size; i++)
	{
		fscanf(fp, "%c\t%d\n", &c, &count);
		r->ascii_value[i] = c;
		r->count[i] = count;
	}
	fclose(fp);
	return r;
}

Huffman* get_sort_data(char* fname)
{
	Huffman* r;
	r = get_file_data(fname);
	int tmpi = 0;
	char tmpc = 0;
	for (int i = 0; i < r->size; i++)
	{
		for (int j = i + 1; j < r->size; j++)
		{
			if (r->count[i] > r->count[j])
			{
				tmpc = r->ascii_value[i];
				tmpi = r->count[i];

				r->ascii_value[i] = r->ascii_value[j];
				r->count[i] = r->count[j];

				r->ascii_value[j] = tmpc;
				r->count[j] = tmpi;
			}
		}
	}

	return r;
}