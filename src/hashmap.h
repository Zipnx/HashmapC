#ifndef HASHMAP_H
#define HASHMAP_H

#include "hashmaputils.h"
#include "hashalgos.h"

#include "seperate_chaining.h"

/* Definitions for function pointers */

typedef uint64_t (*HashFunction)(void*);
typedef bool (*CompareFunction)(void*, void*); 

// Used to set the hash collision resolution

enum CollisionResType{
    SEPERATE_CHAINING = 0,
    OPEN_ADDRESSING   = 1
};

struct Hashmap{
    
    /* The bucket count of the hashmap */
    size_t capacity;
    size_t size; // unused, probably gonna use this

    /* Pointer to the list of buckets */
    struct HashEntry** buckets;

    enum CollisionResType type;
    
    /* Pointer to functions used to interact with the map */
    HashFunction hash;
    CompareFunction cmp;

    /* Data interaction pointers */
    bool  (*set)(struct Hashmap*, void*, void*);
    void* (*get)(struct Hashmap*, void*);
    bool  (*del)(struct Hashmap*, void*);
    bool  (*exists)(struct Hashmap*, void*);
    void  (*prune)(struct Hashmap*);
    void  (*clear)(struct Hashmap*);

};

struct HashEntry {
    
    struct HashEntry* next;

    void* key;
    void* value;
    uint64_t keyhash;
    
    uint8_t flags;

};

struct Hashmap* hashmap_init(enum CollisionResType maptype, size_t bucketcount);


struct HashEntry* _init_hashentry(void* key, void* value, uint64_t hash);
bool _base_compare(void* a, void* b);
bool is_entry_empty(struct HashEntry* entry);

#endif
