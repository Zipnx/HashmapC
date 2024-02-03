
#include "open_addressing.h"
#include "hashmap.h"
#include "seperate_chaining.h"
#include <stdint.h>

// This open addressing implementation is hardcoded to use linear probing

bool hashmap_set_oa(struct Hashmap* map, void* key, void* value){

    uint64_t hashed = map->hash(key); 
    
    DEBUG_PRNT("[hashmap_set_oa] [*] Call to set %p = %p\n", key, value);
 
    int iter = 0;
    struct HashEntry* current = _get_entry_from_hash(map, hashed);
   

    // this comparison sucks, _is_key_match runs the hash function every iter, should
    // just make another var (did this since hashed gets modified)
    // Also the match function should be in hashmap.h
    while ( current != NULL && !is_entry_empty(current) && !_is_key_match(map, current, key) ){
    
        current = _get_entry_from_hash(map, ++hashed);

        if (++iter >= map->capacity){
            
            DEBUG_PRNT("[hashmap_set_oa] [!] Map %p has no room left\n", map);
            return false;

        }

    }

    DEBUG_PRNT("[hashmap_set_oa] [*] Selected bucket for key: %ld\n", hashed % map->capacity);

    if (current == NULL){

        DEBUG_PRNT("[hashmap_set_oa] [+] Creating new bucket entry for key %p\n", key)  ;

        current = _init_hashentry(key, value, map->hash(key)); 
        
        if (current == NULL){
            return false;
        }

        map->buckets[hashed % map->capacity] = current; // remember to change this if i make hashed not get changed
        return true;

    } else if (is_entry_empty(current)){
        
        DEBUG_PRNT("[hashmap_set_oa] [+] Reutilizing empty entry %p\n", current);

        current->key = key;
        current->value = value;
        // hash is called so many fucking times, the moment im done with this junky
        // implementation this shits getting optimized
        current->keyhash = map->hash(key);
        current->flags &= 0xFE;
        
        return true;

    } else {

        DEBUG_PRNT("[hashmap_set_oa] [*] Replacing previous value %p = %p\n", current->key, current->value);
        
        current->value = value;
        current->keyhash = map->hash(key);

        return true;
    }

}

void* hashmap_get_oa(struct Hashmap* map, void* key){

    DEBUG_PRNT("[hashmap_get_oa] [!] %s\n", "OA Get unimplemented");

    return NULL;
}

bool hashmap_del_oa(struct Hashmap *map, void *key){

    DEBUG_PRNT("[hashmap_del_oa] [!] %s\n", "OA Del unimplemented");
    return false;

}

bool hashmap_key_exists_oa(struct Hashmap *map, void *key){

    DEBUG_PRNT("[hashmap_key_exists_oa] [!] %s\n", "OA Key exists unimplemented");
    return false;

}

void hashmap_prune_oa(struct Hashmap *map){
    
    DEBUG_PRNT("[hashmap_prune_oa] [!] %s\n", "OA Prune unimplemented");
    return;

}

void hashmap_clear_oa(struct Hashmap *map){

    DEBUG_PRNT("[hashmap_clear_oa] [!] %s\n", "OA Clear unimplemented");
    return;

}

struct HashEntry* _get_entry_from_hash(struct Hashmap* map, uint64_t hash){
    return map->buckets[hash % map->capacity];
}

bool _is_key_match(struct Hashmap* map, struct HashEntry* entry, void* key){

    if (entry->keyhash == map->hash(key) &&
        map->cmp(entry->key, key)){
        return true;
    }

    return false;
}





