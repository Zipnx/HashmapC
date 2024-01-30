
# Simple C Hashmap

Just an implementation for a hashmap in C.

I'll probably forget this

> [!IMPORTANT]
> This is not in any way a serious implementation for a hashmap.
> I wrote it in an afternoon to play around with, it's incomplete, and possibly insecure.
> The map can't even be free'd (yet) and this is an uncommented mess.

## TODO:
- [X] Seperate chaining functionality
- [ ] Make this somewhat usable
- [ ] Actual hashing ffs
- [ ] Pruning entries flagged as deleted
- [ ] Clearing the hashmap
- [ ] Open addressing hash collision resolution

## Usage:
To add to a project just copy over the source files manually except main.c

Maybe I'm gonna make it more less shit to work with (lies).

To build run "make". To build & run use "make bnr".
(you possibly have to change the compiler path in the Makefile)

### Initialize a map:
Specify SEPERATE_CHAINING (open addressing is unimplemented) and the bucket count of the map

```c
struct Hashmap* map = hashmap_init(SEPERATE_CHAINING, 32);
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


### Debugging
Debugging can be enabled/disabled by un/defining HASHMAP_DEBUG in hashmaputils.h

To display a map that uses seperate chaining you can use:

```c
_display_sc_hashmap(map);
```
