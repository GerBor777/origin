#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

#include "Figure.h"

class Quadrilateral : public Figure {
public:
    Quadrilateral(int a, int b, int c, int d, int A, int B, int C, int D);
    void printInfo() const override;
    bool check() const override;

protected:
    int a, b, c, d;
    int A, B, C, D;
};

#endif // QUADRILATERAL_H
