#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arraylist.h"

typedef struct Substrings {
    char** substrings;
    int count;
} Substrings;

/*
Splits a string by the specified character at max the specfied amount of time
*/
Substrings SplitNString(const char* str, const char sep, const int amount) {
    char** substrs;

    int sepCount = 0;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == sep) sepCount++;
    }

    if (amount == 0 || sepCount == 0) {
        substrs = (char**)malloc(sizeof(char*));
        substrs[0] = (char*)str;
        Substrings out = {.substrings = substrs, .count = 1};
        return out;
    }

    int splits = 0;
    Arraylist acc = NewArraylist(1);  // arraylist to hold collected characters
    int slen = strlen(str);
    for (int i = 0; i < slen; i++) {
        if (splits == amount) {
            break;
        } else if (str[i] == sep) {
            // allocate new string array for the new string
            char** newss = (char**)malloc(sizeof(char*) * (splits + 1));
            for (int j = 0; j < splits; j++) {
                newss[j] = substrs[j];  // copy strings from the old array
            }

            // allocate memory for the substring we collected in the new array
            newss[splits] = (char*)malloc(sizeof(char) * acc.len);
            // copy chars from acc to the new array
            for (int k = 0; k < acc.len; k++) {
                newss[splits][k] = *(char*)acc.arr[k];
            }

            // if (splits > 1) free(substrs);
            substrs = newss;
            FreeArraylist(&acc);    // let go of the old acc's memory
            acc = NewArraylist(1);  // create new arraylist for acc
            splits++;
        } else {
            ALAdd(&acc, (void*)&str[i]);
        }
    }

    // check if we have a substring left over
    if (acc.len > 0) {
        char** final;

        // allocate new string array to hold the substrings we already have +
        // the left over one
        final = (char**)malloc(sizeof(char*) * (splits + 1));

        // copy substrings we already have
        for (int i = 0; i < splits; i++) {
            final[i] = (char*)malloc(sizeof(char) * strlen(substrs[i]));
            final[i] = substrs[i];
            // free(substrs[i]);
        }
        free(substrs);  // let go of substrs since we don't need it anymore

        // allocate memory for the left over substring in the new array
        final[splits] = (char*)malloc(sizeof(char) * acc.len);

        // copy chars from acc to the new array
        for (int i = 0; i < acc.len; i++) {
            final[splits][i] = *(char*)acc.arr[i];
        }
        // printf("final[%d] is: %s\n", splits, final[splits]);
        FreeArraylist(&acc);  // let go of acc since we don't need it anymore

        Substrings out = {.substrings = final,
                          .count = splits == 0 ? 1 : splits + 1};
        return out;
    } else {
        Substrings out = {.substrings = substrs,
                          .count = splits == 0 ? 1 : splits};
        return out;
    }
}

/*
Splits a string by the specified character
*/
Substrings SplitString(const char* str, const char sep) {
    return SplitNString(str, sep, -1);
}

/*
Converts a string to a base 10 integer
*/
int StringToInt(const char* str) {
    int sum = 0;
    int len = strlen(str);

    int place = 1;
    for (int i = len - 1; i > -1; i--) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        else if (str[i] == '-')
            return -sum;
        sum += (str[i] - 48) * place;
        place *= 10;
    }

    return sum;
}