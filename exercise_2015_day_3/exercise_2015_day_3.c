#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
	PART ONE
	--------
	Santa is delivering presents to an infinite two - dimensional grid of houses.

	He begins by delivering a present to the house at his starting location, and then an elf at the North Pole calls him via radio and tells him where to move next.
	Moves are always exactly one house to the north(^), south(v), east(> ), or west(< ).After each move, he delivers another present to the house at his new location.

		However, the elf back at the north pole has had a little too much eggnog, and so his directions are a little off, and Santa ends up visiting some houses more than once.
		How many houses receive at least one present ?

		For example :

	> delivers presents to 2 houses: one at the starting location, and one to the east.
	^ > v < delivers presents to 4 houses in a square, including twice to the house at his starting / ending location.
	^ v ^ v ^ v ^ v ^ v delivers a bunch of presents to some very lucky children at only 2 houses.

	PART TWO
	--------
	The next year, to speed up the process, Santa creates a robot version of himself, Robo-Santa, to deliver presents with him.

	Santa and Robo-Santa start at the same location (delivering two presents to the same starting house), then take turns moving based on instructions from the elf, 
	who is eggnoggedly reading from the same script as the previous year.

	This year, how many houses receive at least one present?

	For example:

	^v delivers presents to 3 houses, because Santa goes north, and then Robo-Santa goes south.
	^>v< now delivers presents to 3 houses, and Santa and Robo-Santa end up back where they started.
	^v^v^v^v^v now delivers presents to 11 houses, with Santa going one direction and Robo-Santa going the other.

*/

bool checkArr(char[8192][10], char[10], int);

int main(void)
{
	FILE* fp;

	int rows = 0, cols = 0, i = 0, j = 0, symbol, x = 0, y = 0, x_robot = 0, y_robot = 0, step = 0;
	/*double cord = 0.0;*/
	char FILENAME[32] = "input_exercise_2015_day_3.txt", line[BUFSIZ], * p, tmp[BUFSIZ], arr[8193][10] = {"0.0"};
	if ((fp = fopen(FILENAME, "r")) == NULL)
	{
		printf("Error opening file with name: %s", FILENAME);
		return 1;
	}

	printf("0.0 ");
	i = 0;
	
	while ((symbol = fgetc(fp)) != EOF)
	{
		if (step % 2 == 0)
		{
			printf("%d Santa: %c ", i, symbol);
			switch (symbol)
			{
			case '>': x += 1; break;
			case '<': x -= 1; break;
			case '^': y += 1; break;
			case 'v': y -= 1; break;
			default:  continue;
			}
			/*printf("%d.%d ", x, y);*/
			sprintf(tmp, "%d.%d", x, y);
			/*printf("%s ", tmp);*/
			if (!checkArr(arr, tmp, i)) {

				// Copy safely and ensure null-termination
				strncpy(arr[i], tmp, 10 - 1);
				arr[i][10 - 1] = '\0';
				i++;
			}

			
		}
		else
		{
			printf("%d Robot: %c ", i, symbol);
			switch (symbol)
			{
			case '>': x_robot += 1; break;
			case '<': x_robot -= 1; break;
			case '^': y_robot += 1; break;
			case 'v': y_robot -= 1; break;
			default:  continue;
			}
			/*printf("%d.%d ", x, y);*/
			sprintf(tmp, "%d.%d", x_robot, y_robot);
			/*printf("%s ", tmp);*/
			if (!checkArr(arr, tmp, i)) {

				// Copy safely and ensure null-termination
				strncpy(arr[i], tmp, 10 - 1);
				arr[i][10 - 1] = '\0';
				i++;
			}
			
		}
	
		step++;
		
	}
	
	printf("\n Part 2: houses that receive at least one present = %d\n", i);
	printf("\n\n");
	for (i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
	{
		printf("%d: %s ", i, arr[i]);
	}


	
	fclose(fp);
	return 0;
}

bool checkArr(char arr[8192][10] , char str[10], int count)
{
	int i = 0;

	for (i; i < count; i++)
	{
		if (strcmp(arr[i], str) == 0)
			return true;
	}
	return false;
}

