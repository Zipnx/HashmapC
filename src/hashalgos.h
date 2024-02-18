#ifndef HASHALGOS_C
#define HASHALGOS_C

#include "hashmaputils.h"

uint64_t hash_none(void* data);
uint64_t hash_djb2(void* data);

#endif
