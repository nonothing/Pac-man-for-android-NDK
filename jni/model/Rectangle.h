#ifndef Rectangle_H_
#define Rectangle_H_
class Rectangle {
private:
    int x;
    int y;
    int width;
    int height;

public:
    Rectangle(int x, int y, int width, int height);
    bool intersects(Rectangle r);
    int getY();
    int getX();

};
#endif /* Rectangle_H_ */
