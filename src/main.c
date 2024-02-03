
#include "hashmap.h"

int main(void){

    struct Hashmap* map = hashmap_init(OPEN_ADDRESSING, 8); 
    
    map->set(map, 0x1, 0x69);

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
