#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int find_largest_possible_joltage(char*);

int main(int argc , char * argv[])
{
	FILE* fp;
	int char_count = 0, i = 0;
	char* filename = "input.txt", chr, *str;
	long long int result = 0;
	size_t len;
	
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("Something went wrong opening the file %s\n", filename);
		exit (1);
	}

	while ((chr = fgetc(fp)) != '\n') char_count++;

	//include the new line '\n'
	char_count++;
	
	printf("Char count= %d\n", char_count);
	rewind(fp);

	str = (char*)malloc(char_count);

	while (fgets(str, char_count, fp) != NULL)
	{

		len = strlen(str);

		if (len > 0 && str[len - 1] == '\n') 
		{
			str[len - 1] = '\0';
			len--; 
		}
		if (len == 0) continue;

		printf("test string: '%s'\n", str);
		result = find_largest_possible_joltage(str) + result;
	}


	printf("The sum of all data is: %lld", result);

	free(str);
	return 0;
}

int find_largest_possible_joltage(char* str)
{
	int i, j, first, second, val, result = 0, len = strlen(str);

	for (i = 0; i < len - 1; i++) {
		first = str[i] - '0';
		for (j = i + 1; j < len; j++) {
			second = str[j] - '0';
			val = first * 10 + second;
			if (val > result) result = val;
		}
	}
	printf("first: %d, second:%d, number: %d\n", first, second, val);
	return result;
}