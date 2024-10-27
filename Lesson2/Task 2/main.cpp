// Подключаем Catch2
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <iostream>

// Код двусвязного списка
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

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
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

// Тесты

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