
#include "hashmap.h"

struct Hashmap* hashmap_init(enum CollisionResType maptype, size_t bucketcount){

    struct Hashmap* map = (struct Hashmap*)malloc(sizeof (struct Hashmap));

    DEBUG_PRNT("[hashmap_init] [*] Initializing new hashmap. type=%d buckets=%ld\n", 
               (int)maptype, bucketcount);

    if (map == NULL){
        DEBUG_PRNT("[hashmap_init] [!] %s\n", "Error allocating memory for new hashmap");
        return NULL;
    }

    switch (maptype){

    case SEPERATE_CHAINING:
        map->set = hashmap_set_sc;
        map->get = hashmap_get_sc;
        map->del = hashmap_del_sc;
        map->exists = hashmap_key_exists_sc;
        map->prune = hashmap_prune_sc;
        map->clear = hashmap_clear_sc;

        break;

    case OPEN_ADDRESSING:
        DEBUG_PRNT("[hashmap_init] [!] %s\n", "Open addressing has not been implemented");
        free(map);
        return NULL;

    default:
        DEBUG_PRNT("[hashmap_init] [!] Invalid map type selected! (%d)\n", (int)maptype);
        free(map);
        return NULL;

    }

    map->capacity = bucketcount;
    map->size = 0;
    map->buckets = malloc(sizeof(void*) * bucketcount);

    if (map->buckets == NULL){
        DEBUG_PRNT("[hashmap_init] [!] %s\n", "Error allocating memory for buckets of new hashmap!");
        free(map);
        return NULL;
    }
    
    memset(map->buckets, 0, sizeof(void*) * bucketcount);

    map->type = maptype;

    map->hash = hash_none;
    map->cmp = _base_compare; 

    DEBUG_PRNT("[hashmap_init] [+] New map %p | TYPE=%d CAP=%ld BCKTS=%p HASH=%p CMP=%p\n",
               map, (int)map->type, map->capacity, map->buckets, map->hash, map->cmp);

    

    return map;
}

struct HashEntry* _init_hashentry(void* key, void* value, uint64_t hash){

    struct HashEntry* res = (struct HashEntry*)malloc(sizeof (struct HashEntry));

    if (res == NULL){
        DEBUG_PRNT("[_init_hashentry] [!] %s\n",
                   "Error allocating memory for new hashentry!");
        return NULL;
    }

    res->next = NULL;
    res->key = key;
    res->value = value;
    res->keyhash = hash;
    res->flags = 0;

    return res;

}

bool _base_compare(void* a, void* b){
    return (a == b); 
}

bool is_entry_empty(struct HashEntry* entry){

    return (entry->flags & 0x1) != 0;

}


