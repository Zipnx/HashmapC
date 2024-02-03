#ifndef SEPERATE_CHAINING_H
#define SEPERATE_CHAINING_H

#include "hashmap.h"

#include <stdbool.h>
#include <stdint.h>

bool hashmap_set_sc(struct Hashmap* map, void* key, void* value);
void* hashmap_get_sc(struct Hashmap* map, void* key);
bool hashmap_del_sc(struct Hashmap* map, void* key);
bool hashmap_key_exists_sc(struct Hashmap* map, void* key);

void hashmap_prune_sc(struct Hashmap* map);
void hashmap_clear_sc(struct Hashmap* map);

struct HashEntry* hashmap_get_entry_sc(struct Hashmap* map, void* key);

struct HashEntry* _incr_free_empty_entries(struct HashEntry* start);
void _display_sc_hashmap(struct Hashmap* map);

#endif
