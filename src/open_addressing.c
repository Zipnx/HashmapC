
#include "open_addressing.h"

bool hashmap_set_oa(struct Hashmap* map, void* key, void* value){

    DEBUG_PRNT("[hashmap_set_oa] [!] %s\n", "OA Set unimplemented");

    return false;
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



