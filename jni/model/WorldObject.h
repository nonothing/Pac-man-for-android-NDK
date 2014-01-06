#include "model/Point.h"
#include "model/Rectangle.h"

class WorldObject {
private:
	int texture;
	int width;
	int height;

protected:
     Point* position;
     Rectangle* bounds;

public:
    WorldObject(Point* point, int texture, int width, int height);
    int getWidth();
    int getHeight();
    void setWidth(int width);
    void setHeight(int height);
    Point* getPosition();
    int getTexture() ;
    Rectangle* getBounds();
    void setBounds(int x, int y, int width, int height);
    void setTexture(int texture);
    void animate() {
        // do nothing
    }
    int inverse(int count);
};
