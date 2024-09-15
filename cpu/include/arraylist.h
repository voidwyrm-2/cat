#pragma once

#include <stdlib.h>

/*
A simple arraylist structure, which can be efficiently indexed into and looped
over
*/
typedef struct Arraylist {
    void** arr;
    int cap;
    int len;
    char truncOpti;
} Arraylist;

/*
Creates a new arraylist of the specified size
*/
Arraylist NewArraylist(const int size) {
    // allocate new underlying array
    void** a = NULL;
    if (size > 0) {
        a = (void**)malloc(sizeof(void*) * size);
    }
    Arraylist al = {.arr = a, .cap = size, .len = 0, .truncOpti = 0};
    return al;
}

/*
Frees all stored memory in the arraylist
*/
void FreeArraylist(Arraylist* al) {
    /*
    for (int i = 0; i < al->len; i++) {
        free(al->arr[i]);
    }
    */
    free(al->arr);  // free up memory used by the arraylist's underlying array
    // technically not needed, but signifies this arraylist is empty
    al->len = 0;
    al->cap = 0;  // ditto
}

/*
Removes an item from the head of the arraylist
*/
void* ALRemove(Arraylist* al) {
    if (al->len > 0 && al->cap > 0) {
        al->len--;                   // decrement the arraylist's length
        void* v = al->arr[al->len];  // copy item before we reset it
        al->arr[al->len] = 0;        // reset whatever data we had there
        // check if we can shave
        if (al->len > 0 && al->len <= (int)(al->cap / 2) && al->cap > 2 &&
            al->truncOpti) {
            al->cap /= 2;
            // allocate a new underlying array with the new cap
            void** newArr = (void**)malloc(sizeof(void*) * al->cap);
            // copy over previous data
            for (int i = 0; i < al->cap; i++) {
                newArr[i] = al->arr[i];
            }
            free(al->arr);     // free the previous underlying array
            al->arr = newArr;  // set the free'd pointer to the new array
        }
        return v;
    }
    return NULL;
}

/*
Adds an item to the head of the arraylist
*/
void ALAdd(Arraylist* al, void* value) {
    // check if this value is outside the range of the current cap
    if (al->len + 1 >= al->cap) {
        al->cap++;  // increment the arraylist's cap
        // allocate a new underlying array with the new cap
        void** newArr = (void**)malloc(sizeof(void*) * al->cap);
        // copy over previous data
        for (int i = 0; i < al->cap - 1; i++) {
            newArr[i] = al->arr[i];
        }
        free(al->arr);     // free the previous underlying array
        al->arr = newArr;  // set the free'd pointer to the new array
    }
    al->arr[al->len] = value;  // set latest empty index to the new item
    al->len++;                 // increment the arraylist's length
}

/*
Gets the item at the specified index
*/
void* ALGetIndex(Arraylist* al, const int index) { return al->arr[index]; }

/*
Sets the item at the specified index to the given value
*/
void ALSetIndex(Arraylist* al, void* value, const int index) {
    al->arr[index] = value;
}

/*
Gets the arraylist's length
*/
int ALLen(Arraylist* al) { return al->len; }

/*
Gets the arraylist's cap
*/
int ALCap(Arraylist* al) { return al->cap; }