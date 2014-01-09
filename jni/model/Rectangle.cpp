#include "Rectangle.h"

Rectangle::Rectangle(int x, int y, int width, int height){
	 this->x = x;
	 this->y = y;
	 this->width = width;
	 this->height = height;
}
int Rectangle::getY() {
        return y;
}

int Rectangle::getX() {
        return x;
}

int Rectangle::getHeight(){
	return height;
}

int Rectangle::getWidht(){
	return width;
}

bool Rectangle::intersects(Rectangle* r) {
        int tw = this->width;
        int th = this->height;
        int rw = r->width;
        int rh = r->height;
        if (rw <= 0 || rh <= 0 || tw <= 0 || th <= 0) {
            return false;
        }
        int tx = this->x;
        int ty = this->y;
        int rx = r->x;
        int ry = r->y;
        rw += rx;
        rh += ry;
        tw += tx;
        th += ty;
        //      overflow || intersect
        return ((rw < rx || rw > tx) &&
                (rh < ry || rh > ty) &&
                (tw < tx || tw > rx) &&
                (th < ty || th > ry));
    }
