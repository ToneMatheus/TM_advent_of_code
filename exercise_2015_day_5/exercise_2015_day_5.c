#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
    Santa needs help figuring out which strings in his text file are naughty or nice.

    A nice string is one with all of the following properties:

        It contains at least three vowels (aeiou only), like aei, xazegov, or aeiouaeiouaeiou.
        It contains at least one letter that appears twice in a row, like xx, abcdde (dd), or aabbccdd (aa, bb, cc, or dd).
        It does not contain the strings ab, cd, pq, or xy, even if they are part of one of the other requirements.

    For example:

        ugknbfddgicrmopn is nice because it has at least three vowels (u...i...o...), a double letter (...dd...), and none of the disallowed substrings.
        aaa is nice because it has at least three vowels and a double letter, even though the letters used by different rules overlap.
        jchzalrnumimnmhp is naughty because it has no double letter.
        haegwjzuvuyypxyu is naughty because it contains the string xy.
        dvszwmarrgswjxmb is naughty because it contains only one vowel.

    How many strings are nice?
*/

void niceCheckPartOne(char, int *, char *, int *, int *, int *);
void niceCheckPartTwo(char, int*, char*, char*, char*, int*);

int main(void)
{
	FILE* fp;
    char str[64], FILENAME[32] = "input.txt", symbol, previous_char = ' ', nextChar = ' ', nextTChar = ' ';
    int i = 0, vowel_count = 0, goodStr_count = 0, multi_count = 0, bad_combi = 0, gg = 0;

    if ((fp = fopen(FILENAME, "r")) == NULL)
    {
        printf("Error opening file with name: %s", FILENAME);
        return 1;
    }

    while ((symbol = fgetc(fp)) != EOF)
    {
        if (symbol == '\n') 
        {    
            /*
            if (vowel_count >= 3 && multi_count >= 1 && bad_combi == 0)
            {
                goodStr_count++;
                gg = 1;
            }
            printf(" v:%d m:%d b:%d good? %d \n", vowel_count, multi_count, bad_combi, gg);
            */


            i = 0;
            vowel_count = 0;
            multi_count = 0;
            bad_combi = 0;
            gg = 0;
            previous_char = ' ';
            continue;
        }

        //niceCheckPartOne(symbol, &i, &previous_char, &multi_count, &bad_combi, &vowel_count);
        niceCheckPartTwo(symbol, &i, &previous_char, &nextChar, &nextTChar, &multi_count);
    }
    printf("\nThere are %d good strings. \n", goodStr_count);
    fclose(fp);
	return 0;
}

void niceCheckPartOne(char symbol, int* i, char* previous_char, int* multi_count, int* bad_combi, int* vowel_count)
{
    if (*i != 0)
    {
        if (symbol == *previous_char)
        {
            (*multi_count)++;
        }

        // ab, cd, pq, or xy
        if ((*previous_char == 'a' && symbol == 'b') ||
            (*previous_char == 'c' && symbol == 'd') ||
            (*previous_char == 'p' && symbol == 'q') ||
            (*previous_char == 'x' && symbol == 'y'))
        {
            (*bad_combi)++;
        }
    }

    *previous_char = symbol;
    printf("%c ", symbol);
    (*i)++;

    // aeiou
    if (symbol == 'a' || symbol == 'e' || symbol == 'i' ||
        symbol == 'o' || symbol == 'u')
    {
        (*vowel_count)++;
    }
}

void niceCheckPartTwo(char sym, int* i, char* prevChar, char* nextChar, char* nextTChar, int* combiCount)
{
    if (*i != 0)
    {
        if (sym == *prevChar)
        {
            *nextChar = sym;
            *nextTChar = &prevChar;
            // here you need to go over the full string for searching the combi and check also position because it isn't allowed to overlap
            // (*combiCount)++;
        }
    }
    *prevChar = sym;
  
    printf("%c ", sym);
    (*i)++;

}

/*
    PART II

    Realizing the error of his ways, Santa has switched to a better model of determining whether a string is naughty or nice. None of the old rules apply, as they are all clearly ridiculous.

    Now, a nice string is one with all of the following properties:

    It contains a pair of any two letters that appears at least twice in the string without overlapping, like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
    It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.

    For example:

        qjhvhtzxzqqjkmpb is nice because is has a pair that appears twice (qj) and a letter that repeats with exactly one letter between them (zxz).
        xxyxx is nice because it has a pair that appears twice and a letter that repeats with one between, even though the letters used by each rule overlap.
        uurcxstgmygtbstg is naughty because it has a pair (tg) but no repeat with a single letter between them.
        ieodomkazucvgmuy is naughty because it has a repeating letter with one between (odo), but no pair that appears twice.

    How many strings are nice under these new rules?
*/

void niceCheckPartTwo()
{

}