#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

int main(void)
{
	FILE* fp;
	int i = 0, num = 0, zeroCount = 0, dialNumber = 50, test = 0, zeroCount_2 = 0;
	char FILENAME[25] = "input.txt", line[BUFSIZ], strNum[3], dir;

	if ((fp = fopen(FILENAME, "r")) == NULL)
	{
		printf("The file \"%s\" cannot be opened\n", FILENAME);
		exit(1);
	}
    printf("The dial starts by pointing at %d\n", dialNumber);

    while (fgets(line, BUFSIZ, fp))
    {
        if (sscanf(line, "%c%d", &dir, &num) != 2)
            continue;

        int clicks = num;  

        // click by click
        for (int step = 0; step < clicks; step++)
        {
            if (dir == 'L')
            {
                dialNumber--;
                if (dialNumber < 0)
                    dialNumber = 99;   
            }
            else  
            {
                dialNumber = (dialNumber + 1) % 100;
            }

            if (dialNumber == 0)
                zeroCount_2++;
        }

        printf("The dial is rotated %c%d to point at %d\n", dir, num, dialNumber);

        if (dialNumber == 0)
            zeroCount++;
    }

	printf("The passcode is = %d, Method 0x434C49434B passcode = %d", zeroCount, zeroCount_2);

	return 0;
}