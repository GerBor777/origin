#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Figure.h"

class Triangle : public Figure {
public:
    Triangle(int a, int b, int c, int A, int B, int C);
    void printInfo() const override;
    bool check() const override;

protected:
    int a, b, c;
    int A, B, C;
};

#endif // TRIANGLE_H
