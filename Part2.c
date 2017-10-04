/**
 *   FILE:   Part2.c
 *   AUTHOR: Madilyn Simons
 */

#include <stdio.h>
#include <stdlib.h>

//  to generate a random number
#include <time.h>

char* make_rand_key(int length, char* key);
void encrypt(char* clear_file, char* key_file, char* cipher_file);
void decrypt(char* key_file, char* cipher_file, char* clear_file);
char* read_file(int len, char *file_name);
void write_file(int len, char *file_name, char *output);


int main()
{
	
	char selection = '0';

	while(selection < '1' || selection > '3')
	{
		printf("Encrypt a file:\t1\n");
		printf("Decrypt a file:\t2\n");
		printf("Exit:\t3\n");
		printf("Enter a choice: ");

		selection = getchar();
	}
	
	switch(selection)
	{
		case '1':
			printf("You've selected 1 to encrypt a file\n");
			break;
		case '2':
			printf("You've selected 2 to decrypt a file\n");
			break;
		case '3':
			printf("You've selected 3 to exit\n");
			printf("Good-bye!\n");
			break;
	}

	// char arr[10];
	// char* point = &arr[0];
	// point = make_rand_key(10, point);

	// int i = 0;
	// for(; i < 10; i++) {
	// 	printf("%c", point);
	// 	point++;
	// }

	char clear_file[] = "message_file.txt";
	char* clear = clear_file;
	encrypt(clear, clear, "output_file.txt");

	return 0;
}

char* make_rand_key(int length, char* key)
{
	if(length > 0)
	{
		char arr[length];

		int range = 78;
		int max = 48;
		char c = 'a';
		int i;

		srand(time(NULL));

		for(i = 0; i < length; i++)
		{
			c = rand() % range + max;
			arr[i] = c;
		}

		key = &arr[0];

		return key;
	}
	else
	{
		printf("ERROR: make_rand_key invalid input");
		return NULL;
	}

}

void encrypt(char* clear_file, char* key_file, char* cipher_file)
{

	clear_file = read_file(0, clear_file);

	int length = 0;
	while(clear_file[length] != '\0') length++;

	key_file = make_rand_key(length, key_file);

	char *encrypted = (char*) malloc(length+1);

	int x;
	for(x = 0; x < length; x++)
	{
		encrypted[x] = clear_file[x] ^ key_file[x];
	}

	//  content is a char pointer
	write_file(length, cipher_file, encrypted);

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