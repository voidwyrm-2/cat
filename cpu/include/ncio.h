#include <stdio.h>
#include <stdlib.h>

char *Readfile(char *fname) {
    char c;
    FILE *file;
    char *out;

    file = fopen(fname, "r");

    if (file) {
        out = (char *)malloc(sizeof(file));
        int i = 0;
        while ((c = (char)getc(file)) != EOF) {
            out[i] = c;
            i++;
        }
        fclose(file);
    } else {
        return 0;
    }

    return out;
}