
#include "hashalgos.h"

uint64_t hash_none(void* data){
    return (uint64_t)data;
}

uint64_t hash_djb2(void* data){
    
    unsigned char* str_data = (unsigned char*)data;

    uint64_t hash = 5381;
    int c;

    while ( (c = *str_data++) ){
        hash = ( (hash << 5) + hash ) + c;
    }

    return hash;
}
