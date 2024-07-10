#ifndef SQUARE_H
#define SQUARE_H

#include "Rectangle.h"

class Square : public Rectangle {
public:
    Square(int side);
    bool check() const override;
};

#endif // SQUARE_H
