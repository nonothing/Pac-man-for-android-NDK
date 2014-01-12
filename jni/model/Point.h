#ifndef Point_H_
#define Point_H_
#include "model/Rectangle.h"

class Point {
private:
     int x;
     int y;

public:
    Point(int x, int y);
    Point(int x, int y,  int width, int height);
    Point(Rectangle* rectangle);
    int getX();
    int getY();
    Point* multiply(int size);
};
#endif /* Point_H_ */
