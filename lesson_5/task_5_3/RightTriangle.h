#ifndef RIGHT_TRIANGLE_H
#define RIGHT_TRIANGLE_H

#include "Triangle.h"

class RightTriangle : public Triangle {
public:
    RightTriangle(int a, int b, int c, int A, int B);
    bool check() const override;
};

#endif // RIGHT_TRIANGLE_H
