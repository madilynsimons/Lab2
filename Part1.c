/**
 *   FILE:   Part1.c
 *   AUTHOR: Madilyn Simons
 */

#include <stdio.h>
#include <stdlib.h>

char* read_file(int len, char* file_name);
void write_file(int len, char *file_name, char *output);

int main()
{
	char *input = read_file(0, "message_file.txt");
	printf("input = \n|%s|\n", input);

	write_file(0, "output_file.txt", input);

	free(input);
	input = NULL;

	return 0;
}

char* read_file(int len, char *file_name)
{
	FILE *fp = fopen(file_name ,"r");

	if(fp == NULL)
	{
		printf("ERROR: File not opened\n");
		exit(1);
	}

	if(len == 0)
	{
		while(getc(fp) != EOF)
			len++;
		printf("len = %d\n", len);
		rewind(fp);
	}

	char *input = (char*) malloc(len+1);

	if(input == NULL)
	{
		printf("ERROR: Memory not allocated\n");
		exit(2);
	}

	int j = 0;

	for(j = 0; j < len; j++)
	{
		input[j] = getc(fp);
	}

	input[j] = '\0';

	fclose(fp);

	return input;
}

void write_file(int len, char *file_name, char *output)
{
	FILE *fp = fopen(file_name, "w");

	if(fp == NULL)
	{
		printf("ERROR: File not opened");
		exit(3);
	}

	int j = 0;
	if(len == 0)
	{
		while(output[j] != '\0')
		{
			putc(output[j++], fp);
		}
	}
	else
	{
		for(j = 0; j<len; j++)
		{
			putc(output[j], fp);
		}
	}

	fclose(fp);

	return;
}