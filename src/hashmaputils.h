
#ifndef HASHMAPUTILS_H
#define HASHMAPUTILS_H

#define HASHMAP_DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#endif

#ifdef HASHMAP_DEBUG
#define DEBUG_PRNT(fmt, ...) printf(fmt, __VA_ARGS__)
#else
#define DEBUG_PRNT(fmt, ...) do {} while (0)
#endif
    
