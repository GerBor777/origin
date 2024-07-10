#ifndef COUNTER_H
#define COUNTER_H

class Counter {
private:
    int value;

public:
    // Конструкторы
    Counter();
    Counter(int initial_value);

    // Методы для работы со счетчиком
    void increment();
    void decrement();
    int getValue() const;
};

#endif // COUNTER_H
