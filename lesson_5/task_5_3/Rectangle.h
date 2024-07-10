#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Quadrilateral.h"

class Rectangle : public Quadrilateral {
public:
    Rectangle(int a, int b);
    bool check() const override;
};

#endif // RECTANGLE_H
