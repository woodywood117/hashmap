#include <stdio.h>
#include "../src/hashmap.h"
#include <assert.h>
#include <string.h>

void check_empty() {
    Hashmap *map = hashmap_create();
    assert(hashmap_get(map, "foo") == NULL);
    hashmap_destroy(map);
    map = NULL;
}

void check_set_get() {
    Hashmap *map = hashmap_create();
    hashmap_set(map, "foo", "bar", 0);
    assert(strcmp(hashmap_get(map, "foo"), "bar") == 0);
    hashmap_destroy(map);
    map = NULL;
}

void check_override_value() {
    Hashmap *map = hashmap_create();
    hashmap_set(map, "foo", "bar", 0);
    hashmap_set(map, "foo", "baz", 0);
    assert(strcmp(hashmap_get(map, "foo"), "baz") == 0);
    hashmap_destroy(map);
    map = NULL;
}

void check_length() {
    Hashmap *map = hashmap_create();
    hashmap_set(map, "foo", "bar", 0);
    assert(hashmap_length(map) == 1);
    hashmap_set(map, "foo", "baz", 0);
    assert(hashmap_length(map) == 1);
    hashmap_set(map, "bar", "baz", 0);
    assert(hashmap_length(map) == 2);
    hashmap_destroy(map);
    map = NULL;
}

void check_remove_to_empty() {
    Hashmap *map = hashmap_create();
    hashmap_set(map, "foo", "bar", 0);
    hashmap_remove(map, "foo");
    assert(hashmap_get(map, "foo") == NULL);
    assert(hashmap_length(map) == 0);
    hashmap_destroy(map);
    map = NULL;
}

void check_resize() {
    Hashmap *map = hashmap_create();
    assert(hashmap_size(map) == INITIAL_HASHMAP_SIZE);
    hashmap_resize(map, 1);
    assert(hashmap_size(map) == 1);
    hashmap_destroy(map);
    map = NULL;
}

void check_resize_reindex() {
    Hashmap *map = hashmap_create();
    assert(hashmap_size(map) == INITIAL_HASHMAP_SIZE);
    hashmap_set(map, "foo", "bar", 0);
    hashmap_set(map, "bar", "baz", 0);
    hashmap_set(map, "baz", "qux", 0);
    hashmap_resize(map, 1);
    assert(hashmap_size(map) == 1);
    assert(hashmap_length(map) == 3);
    hashmap_destroy(map);
    map = NULL;
}

void check_clear() {
    Hashmap *map = hashmap_create();
    hashmap_set(map, "foo", "bar", 0);
    hashmap_set(map, "bar", "baz", 0);
    hashmap_set(map, "baz", "qux", 0);
    hashmap_clear(map);
    assert(hashmap_length(map) == 0);
    hashmap_destroy(map);
    map = NULL;
}

int main(void) {
    check_empty();
    check_set_get();
    check_override_value();
    check_length();
    check_remove_to_empty();
    check_resize();
    check_resize_reindex();
    check_clear();
    printf("All tests passed!\n");
    return 0;
}