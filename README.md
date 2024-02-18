
# Simple C Hashmap

Just an implementation for a hashmap in C.

I'll probably forget this

> [!IMPORTANT]
> This is not in any way a serious implementation for a hashmap.
> I wrote it in an afternoon to play around with, it's incomplete, and possibly insecure.
> Also this is an uncommented mess

## TODO:
- [x] Seperate chaining functionality
- [ ] Make this somewhat usable
- [x] Actual hashing ffs
- [x] Pruning entries flagged as deleted
- [x] Clearing the hashmap
- [x] Open addressing hash collision resolution
- [ ] Check for bugs (that most likely exist)
- [ ] Open addressing prune, <s>clear</s>
- [ ] Resize function

## Usage:
To add to a project just copy over the source files manually except main.c

Maybe I'm gonna make it more less shit to work with (lies).

To build run "make". To build & run use "make bnr".
(you possibly have to change the compiler path in the Makefile)

### Initialize a map:
Specify SEPERATE_CHAINING or OPEN_ADDRESSING and the bucket count of the map

The hash function that is used needs to be set manually to one of the pre-existing ones,
or make a new one

```c
struct Hashmap* map = hashmap_init(SEPERATE_CHAINING, 32);
map->hash = hash_djb2;
```

### Manage data:
You can set/del/get data like this:

```cpp
map->set(map, KEY, VALUE);
map->get(map, KEY);
map->del(map, KEY);
```

Where KEY is a pointer to a key and VALUE likewise a pointer to a value.

As of now only direct interaction with generic pointers works, will probably
add a hash function for null-terminated strings (and a compare function)

There is also pruning, that deletes entries marked as entry in the hashmap and 
clearing, which as the name suggests wipes the map's stored data.

Pruning is unimplemented for OPEN_ADDRESSING as of now

```cpp
map->prune(map);
map->clear(map);
```

Will also add a resize function when i feel like it


### Debugging
Debugging can be enabled/disabled by un/defining HASHMAP_DEBUG in hashmaputils.h

To display a map that uses seperate chaining you can use:

(Also works for open addressing, not ideal but no need to fix what aint broke)

```c
_display_sc_hashmap(map);
```

## References:
- [Hash functions reference](http://www.cse.yorku.ca/~oz/hash.html)
