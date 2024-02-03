#ifndef OPEN_ADDRESSING_H
#define OPEN_ADDRESSING_H

#include "hashmap.h"

struct Hashmap;
struct HashEntry;

bool hashmap_set_oa(struct Hashmap* map, void* key, void* value);
void* hashmap_get_oa(struct Hashmap* map, void* key);
bool hashmap_del_oa(struct Hashmap* map, void* key);
bool hashmap_key_exists_oa(struct Hashmap* map, void* key);

void hashmap_prune_oa(struct Hashmap*);
void hashmap_clear_oa(struct Hashmap*);

struct HashEntry* hashmap_get_entry_oa(struct Hashmap* map, void* key);


#endif
