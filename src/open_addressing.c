
#include "open_addressing.h"
#include "hashmap.h"

// This open addressing implementation is hardcoded to use linear probing

bool hashmap_set_oa(struct Hashmap* map, void* key, void* value){

    uint64_t hashed = map->hash(key); 
    
    DEBUG_PRNT("[hashmap_set_oa] [*] Call to set %p = %p\n", key, value);
 
    size_t iter = 0;
    struct HashEntry* current = _get_entry_from_hash(map, hashed);
   
    while ( current != NULL && 
            !is_entry_empty(current) && 
            !_is_key_match(map, current, key, hashed) ){
    
        current = _get_entry_from_hash(map, hashed + (++iter));

        if (iter >= map->capacity){
            
            DEBUG_PRNT("[hashmap_set_oa] [!] Map %p has no room left\n", map);
            return false;

        }

    }

    DEBUG_PRNT("[hashmap_set_oa] [*] Selected bucket for key: %ld\n", (hashed + iter) % map->capacity);

    if (current == NULL){

        DEBUG_PRNT("[hashmap_set_oa] [+] Creating new bucket entry for key %p\n", key)  ;

        current = _init_hashentry(key, value, hashed); 
        
        if (current == NULL){
            return false;
        }

        map->buckets[(hashed + iter) % map->capacity] = current;
        return true;

    } else if (is_entry_empty(current)){
        
        DEBUG_PRNT("[hashmap_set_oa] [+] Reutilizing empty entry %p\n", current);

        current->key = key;
        current->value = value;
        current->keyhash = hashed;
        current->flags &= 0xFE;
        
        return true;

    } else {

        DEBUG_PRNT("[hashmap_set_oa] [*] Replacing previous value %p = %p\n", current->key, current->value);
        
        current->value = value;
        current->keyhash = hashed;

        return true;
    }

}

void* hashmap_get_oa(struct Hashmap* map, void* key){

    struct HashEntry* entry = _find_entry(map, key);

    return (entry == NULL) ? NULL : entry->value;
}

bool hashmap_del_oa(struct Hashmap *map, void *key){

    DEBUG_PRNT("[hashmap_del_oa] [!] %s\n", "OA Del unimplemented");
    return false;

}

bool hashmap_key_exists_oa(struct Hashmap *map, void *key){

    DEBUG_PRNT("[hashmap_key_exists_oa] [*] Checking if key %p exists\n", key);

    return _find_entry(map, key) != NULL;

}

void hashmap_prune_oa(struct Hashmap *map){
    
    DEBUG_PRNT("[hashmap_prune_oa] [!] %s\n", "OA Prune unimplemented");
    return;

}

void hashmap_clear_oa(struct Hashmap *map){

    DEBUG_PRNT("[hashmap_clear_oa] [!] %s\n", "OA Clear unimplemented");
    return;

}

struct HashEntry* _find_entry(struct Hashmap *map, void *key){

    uint64_t hashed = map->hash(key);
    
    DEBUG_PRNT("[_find_entry] [*] Searching for entry %p\n", key) ;

    struct HashEntry* cur = _get_entry_from_hash(map, hashed);
    size_t iter = 0;

    while (cur != NULL &&
           (is_entry_empty(cur) ||
           !_is_key_match(map, cur, key, hashed))){
        
        
        cur = _get_entry_from_hash(map, hashed + (++iter));
        
        if (iter >= map->capacity) {
            DEBUG_PRNT("[_find_entry] [*] Search for %p exhausted\n", key);
            return NULL;
        }

    }

    if (cur == NULL) return NULL;

    DEBUG_PRNT("[_find_entry] [+] Found entry for key %p : %p\n", key, cur);

    return cur;

}

struct HashEntry* _get_entry_from_hash(struct Hashmap* map, uint64_t hash){
    return map->buckets[hash % map->capacity];
}

bool _is_key_match(struct Hashmap* map, struct HashEntry* entry, void* key, uint64_t hashkey){

    if (entry->keyhash == hashkey &&
        map->cmp(entry->key, key)){
        return true;
    }

    return false;
}





