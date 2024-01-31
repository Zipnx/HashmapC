
#include <stdio.h>

#include "hashmap.h"

int main(void){

    struct Hashmap* map = hashmap_init(SEPERATE_CHAINING, 8); 
    
    
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
    
    map->del(map, (void*)0x30);
    map->del(map, (void*)0);
    map->del(map, (void*)0x1f);

    _display_sc_hashmap(map);

    map->prune(map);

    _display_sc_hashmap(map);

    map->clear(map);

    _display_sc_hashmap(map);

    return 0;
}
