#include <stdio.h>
#include "../src/hashmap.h"
#include <assert.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Create map
    Hashmap *map = hashmap_create();

    // Set values
    hashmap_set(map, "foo", "bar", 0);
    hashmap_set(map, "baz", "qux", 0);
    hashmap_set(map, "buz", "quux", 0);
    hashmap_set(map, "quuz", "corge", 0);
    hashmap_set(map, "quuz", "grault", 0);

    // Get values
    assert(strcmp(hashmap_get(map, "foo"), "bar") == 0);
    assert(strcmp(hashmap_get(map, "baz"), "qux") == 0);
    assert(strcmp(hashmap_get(map, "buz"), "quux") == 0);
    assert(strcmp(hashmap_get(map, "quuz"), "grault") == 0);
    assert(hashmap_get(map, "quux") == NULL);

    // Remove values and check
    hashmap_remove(map, "foo");
    assert(hashmap_get(map, "foo") == NULL);

    // Resize and check size
    hashmap_resize(map, 1);
    assert(map->size == 1);

    // Recheck values
    assert(strcmp(hashmap_get(map, "baz"), "qux") == 0);
    assert(strcmp(hashmap_get(map, "buz"), "quux") == 0);
    assert(strcmp(hashmap_get(map, "quuz"), "grault") == 0);
    assert(hashmap_get(map, "quux") == NULL);

    // Destroy map
    hashmap_destroy(map);
    map = NULL;

    printf("All tests passed!\n");

    return 0;
}
