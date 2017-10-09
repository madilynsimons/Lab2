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

int length;

int main()
{
	length = 0;

	char selection = '0';

	while(selection < '1' || selection > '3')
	{
		printf("Encrypt a file:\t1\n");
		printf("Decrypt a file:\t2\n");
		printf("Exit program:\t3\n");
		printf("Enter a choice: ");

		selection = getchar();
	}

	char clear_file[] = "clear_file.txt";
	char key_file[] = "key_file.txt";
	char cipher_file[] = "cipher_file.txt";
	
	switch(selection)
	{
		case '1':
			printf("Encrypting...\n");
			encrypt(clear_file, key_file, cipher_file);
			break;
		case '2':
			printf("Decrypting...\n");
			decrypt(key_file, cipher_file, clear_file);
			break;
		case '3':
			printf("Good-bye!\n");
			break;
	}

	return 0;
}

char* make_rand_key(int length, char* key)
{
	if(length > 0)
	{

		char* key = (char*) malloc(length+1);
		if(key == NULL)
		{
			printf("ERROR: Memory not allocated\n");
			exit(2);
		}

		int range = 78;
		int max = 48;
		char c = 'a';
		int i;

		srand(time(NULL));

		for(i = 0; i < length; i++)
		{
			c = rand() % range + max;
			key[i] = c;
		}

		return key;
	}
	else
	{
		printf("ERROR: key not generated");
		return NULL;
	}

}

void encrypt(char* clear_file, char* key_file, char* cipher_file)
{
	//  get clear file text
	char *clear_text = read_file(0, clear_file);

	//  get length of the clear text
	int length = 0;
	while(clear_text[length] != '\0') length++;

	char* key = make_rand_key(length, key);

	//  declare encrypted text
	char *encrypted = (char*) malloc(length+1);

	if(encrypted == NULL)
	{
		printf("ERROR: Memory not allocated\n");
		exit(2);
	}

	//  encrypt text
	int x;
	for(x = 0; x < length; x++)
	{
		encrypted[x] = clear_text[x] ^ key[x];
	}

	//  write files
	write_file(length, cipher_file, encrypted);
	write_file(length, key_file, key);

	// free memory
	free(encrypted);
	free(key);
	encrypted = NULL;
	key = NULL;

	printf("%s encrypted\n", clear_file);
}

void decrypt(char* key_file, char* cipher_file, char* clear_file)
{
	char *key = read_file(0, key_file);

	char *encrypted = (char*) malloc(length+1);
	encrypted = read_file(length, cipher_file);

	if(encrypted == NULL)
	{
		printf("ERROR: Memory not allocated\n");
		exit(2);
	}

	char *decypted = (char*) malloc(length+1);

	if(decypted == NULL)
	{
		printf("ERROR: Memory not allocated\n");
		exit(2);
	}

	int x;
	for(x = 0; x < length; x++)
	{
		decypted[x] = encrypted[x] ^ key[x];
	}

	write_file(length, clear_file, decypted);

	free(encrypted);
	free(decypted);
	encrypted = NULL;
	decypted = NULL;

	printf("%s decrypted\n", cipher_file);
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
	}
	length = len;

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

	length = len;

	fclose(fp);

	return;
}