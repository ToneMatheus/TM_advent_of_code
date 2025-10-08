#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*
	Santa is delivering presents to an infinite two - dimensional grid of houses.

	He begins by delivering a present to the house at his starting location, and then an elf at the North Pole calls him via radio and tells him where to move next.
	Moves are always exactly one house to the north(^), south(v), east(> ), or west(< ).After each move, he delivers another present to the house at his new location.

		However, the elf back at the north pole has had a little too much eggnog, and so his directions are a little off, and Santa ends up visiting some houses more than once.
		How many houses receive at least one present ?

		For example :

	> delivers presents to 2 houses: one at the starting location, and one to the east.
	^ > v < delivers presents to 4 houses in a square, including twice to the house at his starting / ending location.
	^ v ^ v ^ v ^ v ^ v delivers a bunch of presents to some very lucky children at only 2 houses.
*/


int main(void)
{
	FILE* fp;
	int rows = 0, cols = 0;
	char FILENAME[20] = "input.txt", line[BUFSIZ], *p, tmp;
	if ((fp = fopen(FILENAME, "r")) == NULL)
	{
		printf("Error opening file with name: %s", FILENAME);
		return 1;
	}

	while (fgets(line, sizeof line, fp))
	{
		if (*line == '\n' || *line == '\t') continue; // skipping the empty or tab-only lines
		rows++;
		if (cols == 0) // counting columns (for first line only)
		{
			p = line; // parsing the first line with a pointer
			while (sscanf(p, " %c", &tmp) == 1) // It tries to read one char from the string pointed by p skipping spaces (" %c")
			{ // if it is succesfull it reads 1
				cols++;
				while (*p && *p == ' ') p++; // skips spaces before the current token, as long as p != '\0' and p!= ' '
				if (*p) p++; // move the cursor to next char
				while (*p == ' ' || *p == '\t') p++; // this skips any whitespaces or tabs after the token
			}
		}
	}
	rewind(fp);
	printf("Matrix (%d x %d):\n", rows, cols);
	fclose(fp);
	return 0;
}

/*
	#include <stdio.h>
	#include <string.h>
	#include <ctype.h>

	int main(void)
	{
		FILE *fp = fopen("data.txt", "r");
		if (!fp) return 1;

		char line[1024];
		int rows = 0, cols = 0;

		while (fgets(line, sizeof line, fp))
		{
			// Skip empty or whitespace-only lines
			char *p = line;
			while (isspace((unsigned char)*p)) p++;
			if (*p == '\0') continue;

			rows++;

			if (cols == 0)
			{
				// Count tokens (space- or tab-separated)
				char *token = strtok(line, " \t\n");
				while (token)
				{
					cols++;
					token = strtok(NULL, " \t\n");
				}
			}
		}

		fclose(fp);
		printf("Rows: %d, Cols: %d\n", rows, cols);
		return 0;
	}
*/