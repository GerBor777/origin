#include "counter.h"

// Определения конструкторов
Counter::Counter() : value(0) {}
Counter::Counter(int initial_value) : value(initial_value) {}

// Определения методов
void Counter::increment() {
    value++;
}

void Counter::decrement() {
    value--;
}

int Counter::getValue() const {
    return value;
}
