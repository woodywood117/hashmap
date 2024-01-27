#include "hashmap.h"

#include <stdlib.h>
#include <string.h>

int hash(char *key, int size) {
    int hash = 0;
    for (int i = 0; i < strlen(key); i++) {
        hash += key[i];
    }
    return hash % size;
}

Hashmap *hashmap_create() {
    Hashmap *map = malloc(sizeof(Hashmap));
    map->size = INITIAL_HASHMAP_SIZE;
    map->entries = calloc(INITIAL_HASHMAP_SIZE, sizeof(Entry *));
    return map;
}

void hashmap_resize(Hashmap *map, int size) {
    Entry **entries = calloc(size, sizeof(Entry *));
    for (int i = 0; i < map->size; i++) {
        Entry *e = map->entries[i];
        while (e != NULL) {
            Entry *next = e->next;
            int index = hash(e->key, size);
            e->next = entries[index];
            entries[index] = e;
            e = next;
        }
    }
    free(map->entries);
    map->entries = entries;
    map->size = size;
}

void hashmap_destroy(Hashmap *map) {
    for (int i = 0; i < map->size; i++) {
        Entry *e = map->entries[i];
        while (e != NULL) {
            Entry *next = e->next;
            free(e->key);
            if (e->freeable) {
                free(e->value);
            }
            free(e);
            e = next;
        }
    }
    free(map->entries);
    free(map);
}

void hashmap_set(Hashmap *map, char *key, void *value, int freeable) {
    int index = hash(key, map->size);
    Entry *e = map->entries[index];
    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            if (e->freeable) {
                free(e->value);
            }

            e->value = malloc(strlen(value) + 1);
            strcpy(e->value, value);
            e->freeable = freeable;
            return;
        }
        e = e->next;
    }
    e = malloc(sizeof(Entry));
    e->key = malloc(strlen(key) + 1);
    strcpy(e->key, key);
    e->value = value;
    e->next = map->entries[index];
    e->freeable = freeable;
    map->entries[index] = e;
}

void *hashmap_get(Hashmap *map, char *key) {
    int index = hash(key, map->size);
    Entry *e = map->entries[index];
    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            return e->value;
        }
        e = e->next;
    }
    return NULL;
}

void hashmap_remove(Hashmap *map, char *key) {
    int index = hash(key, map->size);
    Entry *e = map->entries[index];
    Entry *prev = NULL;
    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            if (prev == NULL) {
                map->entries[index] = e->next;
            } else {
                prev->next = e->next;
            }
            free(e->key);
            if (e->freeable) {
                free(e->value);
            }
            free(e);
            return;
        }
        prev = e;
        e = e->next;
    }
}