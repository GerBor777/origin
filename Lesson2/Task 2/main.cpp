#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "my_list.h"

TEST_CASE("PushBack adds elements to the back of the list", "[PushBack]") {
    List list;
    list.PushBack(10);
    list.PushBack(20);
    REQUIRE(list.Size() == 2);
    REQUIRE(list.PopBack() == 20);
    REQUIRE(list.PopBack() == 10);
}

TEST_CASE("PushFront adds elements to the front of the list", "[PushFront]") {
    List list;
    list.PushFront(10);
    list.PushFront(20);
    REQUIRE(list.Size() == 2);
    REQUIRE(list.PopFront() == 20);
    REQUIRE(list.PopFront() == 10);
}

TEST_CASE("PopBack on an empty list throws an error", "[PopBack]") {
    List list;
    REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);
}

TEST_CASE("PopFront on an empty list throws an error", "[PopFront]") {
    List list;
    REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
}

TEST_CASE("Complex scenario with multiple Push and Pop operations", "[Complex]") {
    List list;
    list.PushBack(1);
    list.PushFront(2);
    list.PushBack(3);
    list.PushFront(4);
    
    REQUIRE(list.Size() == 4);
    REQUIRE(list.PopFront() == 4);
    REQUIRE(list.PopBack() == 3);
    REQUIRE(list.PopFront() == 2);
    REQUIRE(list.PopBack() == 1);
    REQUIRE(list.Empty() == true);
}
