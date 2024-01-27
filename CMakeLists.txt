cmake_minimum_required(VERSION 3.27)
project(hashmap C)

set(CMAKE_C_STANDARD 17)

enable_testing()

add_library(hashmap STATIC src/hashmap.c
        src/hashmap.h)

add_executable(hashmap_test tests/tests.c)
target_link_libraries(hashmap_test hashmap)

add_test(NAME hashmap_test COMMAND hashmap_test)