#ifndef FIGURE_H
#define FIGURE_H

class Figure {
public:
    Figure(int sides);
    virtual void printInfo() const;
    virtual bool check() const;

protected:
    int sides;
};

#endif // FIGURE_H
