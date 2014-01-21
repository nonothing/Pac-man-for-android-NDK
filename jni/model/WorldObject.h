#ifndef WorldObject_H_
#define WorldObject_H_
#include "model/Point.h"
#include "model/Rectangle.h"
#include "log.h"

class WorldObject {
private:
	int texture;
	int width;
	int height;

protected:
     Point* position;
     Rectangle* bounds;

public:
    WorldObject(){};
    virtual ~WorldObject();
    WorldObject(Point* point, int texture, int width, int height);
    int getWidth();
    int getHeight();
    void setWidth(int width);
    void setHeight(int height);
    Point* getPosition();
    void setPositionPoint(Point* point);
    int getTexture() ;
    Rectangle* getBounds();
    void setBounds(int x, int y, int width, int height);
    void setTexture(int texture);
    virtual void animate() {
        // do nothing
    }
    int inverse(int count);
};
#endif /* WorldObject_H_ */
