// Подключаем Catch2
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <iostream>

// Код двусвязного списка (из задания)
struct ListNode
{
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

    int value;
    ListNode* prev;
    ListNode* next;
};

class List
{
public:
    List() : m_head(new ListNode(0)), m_size(0), m_tail(new ListNode(0, m_head)) {}

    ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

// Юнит-тесты

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
  
}