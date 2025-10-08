#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int floor = 0;
	char chr;
	char s[8000];
	printf("Give me a string pls:\n");
	scanf("%s%*c", s);
	for (int i = 0; i < strlen(s); i++)
	{
		chr = s[i];
		do
		{
			/* part 2 */
			if (floor == -1)
			{
				printf("We hit the basement bruh: position is %d\n", i);
			}
			/* */
			if (chr == '(')
			{
				floor++;
				/*printf("floor %d, ", floor);*/
			}
			else
			{
				floor--;
				/*printf("floor %d", floor);*/
			}
			/*printf("%c\n", chr);*/
		} while (chr == ' ');
	}
	//do
	//{
	//	if (chr == '(')
	//	{

	//	}
	//}
	//while( EOF != '/0')
	//printf("this is the string: %s", s);
	printf("floor %d", floor);
	return 0;
}