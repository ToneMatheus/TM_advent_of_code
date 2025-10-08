#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

/*
    PART 1
    ------
    The elves are running low on wrapping paper, and so they need to submit an order for more. 
    They have a list of the dimensions (length l, width w, and height h) of each present, and only want to order exactly as much as they need.

    Fortunately, every present is a box (a perfect right rectangular prism), which makes calculating the required wrapping paper for each gift a little easier: 
    find the surface area of the box, which is 2*l*w + 2*w*h + 2*h*l. The elves also need a little extra paper for each present: the area of the smallest side.

    For example:

        A present with dimensions 2x3x4 requires 2*6 + 2*12 + 2*8 = 52 square feet of wrapping paper plus 6 square feet of slack, for a total of 58 square feet.
        A present with dimensions 1x1x10 requires 2*1 + 2*10 + 2*10 = 42 square feet of wrapping paper plus 1 square foot of slack, for a total of 43 square feet.

    All numbers in the elves' list are in feet. How many total square feet of wrapping paper should they order?

    PART 2
    ------
    The elves are also running low on ribbon. Ribbon is all the same width, so they only have to worry about the length they need to order, which they would again like to be exact.

    The ribbon required to wrap a present is the shortest distance around its sides, or the smallest perimeter of any one face. Each present also requires a bow made out of ribbon as well; 
    the feet of ribbon required for the perfect bow is equal to the cubic feet of volume of the present. Don't ask how they tie the bow, though; they'll never tell.

    For example:

    A present with dimensions 2x3x4 requires 2+2+3+3 = 10 feet of ribbon to wrap the present plus 2*3*4 = 24 feet of ribbon for the bow, for a total of 34 feet.
    A present with dimensions 1x1x10 requires 1+1+1+1 = 4 feet of ribbon to wrap the present plus 1*1*10 = 10 feet of ribbon for the bow, for a total of 14 feet.

    How many total feet of ribbon should they order?
*/

int main(void)
{
    FILE* fp;
    int i = 0, counter = 0, total = 0, num = 0, num_2 = 0, num_3 = 0, sqr = 0, sqr_2 = 0, sqr_3 = 0, small_, new_total, new_total_all = 0, total_wrap = 0, total_wrap_2 = 0, total_wrap_3 = 0, new_total_all_wrap = 0, num_4 = 0, num_5 = 0;
    char FILENAME[BUFSIZ] = "input.txt", line[BUFSIZ], chr, strNum[4];
    char* token;
    char* token_2;
    char* token_3;

    if ((fp = fopen(FILENAME, "r")) == NULL)
    {
        printf("The file %s cannont be opened\n", FILENAME);
        return 1;
    }

    while (fgets(line, BUFSIZ, fp) != NULL)
    {
        token = strtok(line, "x");
        token_2 = strtok(NULL, "x");
        token_3 = strtok(NULL, "x");
        num = atoi(token);
        num_2 = atoi(token_2);
        num_3 = atoi(token_3);
        total = 2 * num * num_2 + 2 * num_2 * num_3 + 2 * num_3 * num;
        /*printf("2*%s*%d + 2*%s*%d + 2*%s*%d = %d\n", token, num_2, token_2, num_3, token_3, num, total);*/
        sqr = num * num_2;
        sqr_2 = num_2 * num_3;
        sqr_3 = num_3 * num;
        /*printf("2*%d + 2*%d + 2*%d = %d\n", sqr, sqr_2, sqr_3, total);*/
        for (i = 0; i < 3; i++)
        {
            if (sqr < sqr_2)
            {
                small_ = sqr;
            }
            else
            {
                small_ = sqr_2;
            }
            if (small_ > sqr_3)
            {
                small_ = sqr_3;
            }
        }
        /*printf("smallest num = %d\n", small_);*/
        new_total = small_ + total;
        /*printf("new total = %d\n", new_total);*/
        new_total_all += new_total;
       /* printf("the grand total is: %d\n", new_total_all);*/

        // FIND 2 smallest numbers out of 3
        for (i = 0; i < 3; i++)
        {
            // num = a, num_2 = b, num_3 = c
            if (num < num_2)
            {
                if (num < num_3)
                {
                    num_4 = num;
                    if (num_2 < num_3)
                    {
                        num_5 = num_2;
                    }
                    else
                    {
                        num_5 = num_3;
                    }
                }
                else
                {
                    num_5 = num;
                    if (num_2 < num_3)
                    {
                        num_4 = num_2;
                    }
                    else
                    {
                        num_4 = num_3;
                    }
                }
            }
            else
            {
                if (num_2 < num_3)
                {
                    num_4 = num_2;
                    if (num < num_3)
                    {
                        num_5 = num;
                    }
                    else
                    {
                        num_5 = num_3;
                    }
                }
                else
                {
                    num_5 = num_2;
                    if (num < num_3)
                    {
                        num_4 = num;
                    }
                    else
                    {
                        num_4 = num_3;
                    }
                }
            }
            
        }
        printf("smallest 2 num are: %d and %d\n", num_4, num_5);
        total_wrap = num_4 + num_4 + num_5 + num_5;
        printf("P2: %d + %d + %d + %d = %d\n", num_4, num_4, num_5, num_5, total_wrap);
        total_wrap_2 = num * num_2 * num_3;
        printf("P2: %d * %d * %d = %d\n", num, num_2, num_3, total_wrap_2);
        total_wrap_3 = total_wrap + total_wrap_2;
        printf("P2: %d + %d = %d\n", total_wrap, total_wrap_2, total_wrap_3);
        new_total_all_wrap += total_wrap_3;
        printf("P2: Total of wrap: %d\n", new_total_all_wrap);


        
       /* while (token != NULL)
        {
            printf("%s\n", token);
            token = strtok(NULL, " ");

        }*/
        /*printf("%s", line);*/
       /* for (i = 0; i < strlen(line); i++)
        {
            chr = line[i];

            printf("%d %c\n", counter, chr);
        }*/
    } 

	return 0;
}