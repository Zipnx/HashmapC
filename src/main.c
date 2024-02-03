
#include "hashmap.h"
#include "seperate_chaining.h"

int main(void){

    struct Hashmap* map = hashmap_init(OPEN_ADDRESSING, 4); 
    
    map->set(map, (void*)0x1, (void*)0x69);
    map->set(map, (void*)0x5, (void*)0x420);
    map->set(map, (void*)0x9, (void*)0x8008);

    _display_sc_hashmap(map);

    map->set(map, (void*)0x5, (void*)0x1337);

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
