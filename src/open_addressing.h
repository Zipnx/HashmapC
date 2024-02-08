#ifndef OPEN_ADDRESSING_H
#define OPEN_ADDRESSING_H

#include <stdbool.h>
#include <stdint.h>

#include "hashmap.h"

bool hashmap_set_oa(struct Hashmap* map, void* key, void* value);
void* hashmap_get_oa(struct Hashmap* map, void* key);
bool hashmap_del_oa(struct Hashmap* map, void* key);
bool hashmap_key_exists_oa(struct Hashmap* map, void* key);

void hashmap_prune_oa(struct Hashmap*);
void hashmap_clear_oa(struct Hashmap*);

struct HashEntry* _find_entry(struct  Hashmap* map, void* key);
struct HashEntry* _get_entry_from_hash(struct Hashmap* map, uint64_t hash); 
bool _is_key_match(struct Hashmap* map, struct HashEntry* entry, void* key, uint64_t hashkey);

#endif
