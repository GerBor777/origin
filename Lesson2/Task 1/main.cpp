#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "my_list.h"

TEST_CASE("List is initially empty", "[Empty]") {
    List list;
    REQUIRE(list.Empty() == true);  // Проверка, что новый список пуст
}

TEST_CASE("List size increases after adding elements", "[Size]") {
    List list;
    list.PushFront(10);
    list.PushBack(20);
    REQUIRE(list.Size() == 2);  // Проверка, что размер списка равен 2 после добавления 2 элементов
}

TEST_CASE("List is empty after clearing", "[Clear]") {
    List list;
    list.PushFront(10);
    list.PushBack(20);
    REQUIRE(list.Size() == 2);  // Проверка, что размер списка равен 2 после добавления 2 элементов
    list.Clear();
    REQUIRE(list.Empty() == true);  // Проверка, что список пуст после очистки
    REQUIRE(list.Size() == 0);      // Проверка, что размер списка равен 0 после очистки
}
