#pragma once

#include <stdlib.h>

typedef struct Result {
    const void* res;
    const char* err;
} Result;

Result NewResult(const void* r, const char* e) {
    Result result = {.res = r, .err = e};
    return result;
}

Result NewErrResult(const char* e) { return NewResult(NULL, e); }

Result NewSuccessResult(const void* r) { return NewResult(r, NULL); }