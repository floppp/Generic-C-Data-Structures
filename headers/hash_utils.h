#ifndef HASH_UTILS_H_
#define HASH_UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define HT_PRIME_1 151
#define HT_PRIME_2 163

int hm_generic_hash(const char* s, const int a, const int m);
int hm_double_hash(const char*s, const int num_buckets, const int attemp);

#endif
