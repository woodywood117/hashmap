#ifndef HASHMAP_LIBRARY_H
#define HASHMAP_LIBRARY_H

#define INITIAL_HASHMAP_SIZE 10

typedef struct Entry {
    char *key;
    void *value;
    int freeable;
    struct Entry *next;
} Entry;

typedef struct {
    int size;
    Entry **entries;
} Hashmap;

// Manage the hashmap itself
Hashmap *hashmap_create();
void hashmap_resize(Hashmap *map, int size);
void hashmap_destroy(Hashmap *map);

// Manage the entries within the hashmap
void hashmap_set(Hashmap *map, char *key, void *value, int freeable);
void *hashmap_get(Hashmap *map, char *key);
void hashmap_remove(Hashmap *map, char *key);

#endif //HASHMAP_LIBRARY_H
