
#include "hashmap.h"
#include "seperate_chaining.h"

int main(void){
    
    /*
    uint64_t test = hash_djb2((char*)"This is sme text data");
    
    printf("%ld\n", test);

    return 0;

    */

    struct Hashmap* map = hashmap_init(OPEN_ADDRESSING, 4); 
    map->hash = hash_djb2;

    map->set(map, (void*)"Key a", (void*)0x69);
    map->set(map, (void*)"No idea", (void*)0x420);
    map->set(map, (void*)"something", (void*)0x8008);

    _display_sc_hashmap(map);

    map->set(map, (void*)"else", (void*)0x1337);
    map->set(map, (void*)"idk", (void*)0x360);

    _display_sc_hashmap(map);
     
    map->del(map, (void*)"Key a");

    printf("Exists: %d\n", map->exists(map, (void*)"Key a"));
    _display_sc_hashmap(map);
    
    map->set(map, (void*)"Another", (void*)0x6969);
    
    printf("%p\n", map->get(map, (void*)"else"));

    _display_sc_hashmap(map); 
    
    map->clear(map);

    _display_sc_hashmap(map);

    /*    
    srand(1);

    int i;
    for (i = 0; i < 50; i++){

        switch (rand() % 2){

        case 0:
            map->set(map, (void*)(rand() % 50), (void*)((rand() % 1000)+50));
            break;

        case 1:
            map->del(map, (void*)(rand() % 50));

        }

    }
    printf("Ran %d map accesses.\n", i);
    */


    return 0;
}
