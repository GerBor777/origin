#ifndef MY_LIST_H
#define MY_LIST_H

#include <stdexcept>

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

    bool Empty() const { return m_size == 0; }

    unsigned long Size() const { return m_size; }

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

#endif // MY_LIST_H