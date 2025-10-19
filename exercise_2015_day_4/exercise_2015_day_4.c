#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

/*
    Santa needs help mining some AdventCoins (very similar to bitcoins) to use as gifts for all the economically forward-thinking little girls and boys.

    To do this, he needs to find MD5 hashes which, in hexadecimal, start with at least five zeroes.
    The input to the MD5 hash is some secret key (your puzzle input, given below) followed by a number in decimal.
    To mine AdventCoins, you must find Santa the lowest positive number (no leading zeroes: 1, 2, 3, ...) that produces such a hash.

    For example:

    If your secret key is abcdef, the answer is 609043, because the MD5 hash of abcdef609043 starts with five zeroes (000001dbbfa...),
    and it is the lowest such number to do so.
    If your secret key is pqrstuv, the lowest number it combines with to make an MD5 hash starting with five zeroes is 1048970; that is,
    the MD5 hash of pqrstuv1048970 looks like 000006136ef....
*/

char* str2md5(const char* str, int length);

int main(int argc, char** argv) {
    char* output, *new_str;
    int count = 1;
    char str1[BUFSIZ] = "bgvyzdsv", str2[BUFSIZ];
    do
    {
        sprintf(str2, "%d", count);
        if ((new_str = malloc(strlen(str1) + strlen(str2) + 1)) != NULL) {
            new_str[0] = '\0';   // ensures the memory is an empty string
            strcat(new_str, str1);
            strcat(new_str, str2);
        }
        else {
            printf("malloc failed!\n");
            return 1;
        }
        output = str2md5(new_str, strlen(new_str));
        printf("input: %s count %d: %s\n", new_str, count, output);
        count++;
        /* PART 1: } while (!(output[0] == '0' && output[1] == '0' &&
        output[2] == '0' && output[3] == '0' &&
        output[4] == '0'));*/
    } while (!(output[0] == '0' && output[1] == '0' && output[2] == '0' && output[3] == '0' && output[4] == '0' && output[5] == '0'));

    free(output);
    return 0;
}

char* str2md5(const char* str, int length) {
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char* out = (char*)malloc(33);

    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        }
        else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n * 2]), 16 * 2, "%02x", (unsigned int)digest[n]);
    }

    return out;
}