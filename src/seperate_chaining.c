
#include "seperate_chaining.h"

bool hashmap_key_exists_sc(struct Hashmap* map, void* key){

    return hashmap_get_entry_sc(map, key) != NULL;

}

bool hashmap_del_sc(struct Hashmap* map, void* key){
    
    struct HashEntry* entry = hashmap_get_entry_sc(map, key);
    
    if (entry == NULL) return false;
    
    DEBUG_PRNT("[hashmap_del_sc] [+] Entry %p (%p) marked as deleted.\n", key, entry);

    entry->flags |= 1;

    return true;

}

void* hashmap_get_sc(struct Hashmap* map, void* key){
    
    struct HashEntry* entry = hashmap_get_entry_sc(map, key);

    return (entry != NULL) ? entry->value : NULL;

}

struct HashEntry* hashmap_get_entry_sc(struct Hashmap* map, void* key){

    uint64_t hashed = map->hash(key);
    size_t bucketid = hashed % map->capacity;

    struct HashEntry* selected = map->buckets[bucketid];

    while (selected != NULL){

        if (!is_entry_empty(selected) &&
            selected->keyhash == hashed &&
            map->cmp(selected->key, key)){

            return selected;

        }

        selected = selected->next;
    }

    return NULL;

}




bool hashmap_set_sc(struct Hashmap* map, void* key, void* value){
    
    // these functions are not to be called directly, unless it's certain that the
    // hashmap is of the proper type (in order to avoid the switch statement for performance)

    DEBUG_PRNT("[hashmap_set_sc] [*] Call to set %p = %p\n", key, value);

    uint64_t hashed = map->hash(key);
    size_t bucketid = hashed % map->capacity;
    
    DEBUG_PRNT("[hashmap_set_sc] [*] Assigned to bucket #%ld\n", bucketid);

    struct HashEntry* selected = map->buckets[bucketid];

    // First check if the bucket exists
    if (selected == NULL){
        DEBUG_PRNT("[hashmap_set_sc] [*] Creating root entry for #%ld\n", bucketid);

        selected = _init_hashentry(key, value, hashed);
        map->buckets[bucketid] = selected;
        
        DEBUG_PRNT("[hashmap_set_sc] [+] Set op successful. Added new entry %p to new bucket\n",
                   selected);

        return true;
    }

    struct HashEntry* previous = NULL;
    struct HashEntry* empty = NULL;
    bool to_replace = false;

    while (selected != NULL){
        
        if (is_entry_empty(selected)) empty = selected;  
        
        if (selected->keyhash == hashed &&
            map->cmp(selected->key, key)) {

            to_replace = true;
            break;

        }

        previous = selected;
        selected = selected->next;
    }

    DEBUG_PRNT("[hashmap_set_sc] [*] %s\n", "Linked list iteration complete. Status:");
    DEBUG_PRNT("[hashmap_set_sc]     PREV=%p SELECTED=%p EMPTY=%p TOREPLACE=%d\n", 
               previous, selected, empty, (int)to_replace);
    
    // In case there exists already and entry and has to have it's value updated
    if (to_replace){
        selected->value = value;
        selected->flags &= 0xFE; // in case it had been previously marked as deleted

        DEBUG_PRNT("[hashmap_set_sc] [+] %s (%p)\n",
                   "Set op successful. Updated value of existing entry.", selected);

        return true;
    }

    // Afterwards we need to create a new entry, but first check if there is an empty entry lying around
    
    if (empty != NULL){

        empty->key = key;
        empty->value = value;
        empty->keyhash = hashed;

        empty->flags &= 0xFE; // toggle the lsb bit which indicated it is empty
        
        DEBUG_PRNT("[hashmap_set_sc] [+] Set op successful. Reutilized empty entry %p\n",
                   empty);

        return true;

    }

    // Finally create a new entry

    selected = _init_hashentry(key, value, hashed);
    
    if (selected == NULL) return false;

    previous->next = selected;
    
    DEBUG_PRNT("[hashmap_set_sc] [+] Set op successful. Created new entry %p\n", selected);

    return true;

}



void _display_sc_hashmap(struct Hashmap* map){

    printf("\n**********\n");
    printf("* MAP %p | BCKT=%p CAP=%ld SIZE=%ld HASH=%p CMP=%p\n",
           map, map->buckets, map->capacity, map->size, map->hash, map->cmp);

    for (size_t i = 0; i < map->capacity; i++){

        struct HashEntry* root = map->buckets[i];

        if (root == NULL) continue;

        printf("*\t+ [%ld]", i);

        while (root != NULL){
            
            printf(" -> [%p] %p = %p (FLG=%d HASH=%ld)",
                   root, root->key, root->value, root->flags, root->keyhash);

            root = root->next;
        }
        printf("\n");

    }
    printf("**********\n\n");
    

}
