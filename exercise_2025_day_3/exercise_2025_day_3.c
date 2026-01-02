#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int find_largest_possible_joltage_part_1(char*);
long long find_largest_possible_joltage_part_2(char* s);

int main(int argc , char * argv[])
{
	FILE* fp;
	int char_count = 0, i = 0, part = 1; // default
	char* filename = "input.txt", chr, *str;
	long long int result = 0;
	size_t len;

	
	if (argc >= 2) 
	{
		part = atoi(argv[1]);
		if (part != 1 && part != 2) 
		{
			fprintf(stderr, "Usage: %s [1|2]\n", argv[0]);
			return 1;
		}
	}
	
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

		/*printf("test string: '%s'\n", str);*/
		if (part == 1) 
		{
			result = find_largest_possible_joltage_part_1(str) + result;      
		}
		else 
		{
			result = find_largest_possible_joltage_part_2(str) + result;
		}
		
	}


	printf("The sum of all data is: %lld", result);

	free(str);
	fclose(fp);
	return 0;
}

int find_largest_possible_joltage_part_1(char* str)
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

long long find_largest_possible_joltage_part_2(char* s) 
{
	int n = (int)strlen(s);
	int keep = 12;
	int k = n - keep;                 // digits to remove
	if (k < 0) return 0;              // check enough digits

	char* stack = (char*)malloc(n + 1);
	int top = 0;

	for (int i = 0; i < n; i++)
	{
		char c = s[i];
		while (k > 0 && top > 0 && stack[top - 1] < c)
		{
			top--;
			k--;
		}
		stack[top++] = c;
	}

	top -= k;

	/* build exactly 12 digits */
	char out[13];
	for (int i = 0; i < keep; i++) out[i] = stack[i];
	out[12] = '\0';

	free(stack);

	return strtoll(out, NULL, 10);
}