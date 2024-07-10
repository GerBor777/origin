#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Parallelogram.h"

class Rhombus : public Parallelogram {
public:
    Rhombus(int side, int A, int B);
    bool check() const override;
};

#endif // RHOMBUS_H
