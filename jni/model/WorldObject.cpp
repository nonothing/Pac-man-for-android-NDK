#include "WorldObject.h"
    WorldObject::WorldObject(Point* point, int texture, int width, int height) {
    	this->width = width;
    	this->height = height;
        position = new Point(point->getX(), point->getY(), width, height);
        bounds = new Rectangle(position->getX(), position->getY(), width, height);

        this->texture = texture;
    }

    int WorldObject::getWidth() {
        return width;
    }
    int WorldObject::getHeight() {
        return height;
    }

    void WorldObject::setWidth(int width){
    	this->width = width;
    }
    void WorldObject::setHeight(int height){
    	this->height = height;
    }

    Point* WorldObject::getPosition() {
        return position;
    }

    int WorldObject::getTexture() {
        return texture;
    }

    Rectangle* WorldObject::getBounds() {
        return bounds;
    }

    void WorldObject::setBounds(int x, int y,  int width, int height){
        bounds = new Rectangle(x, y, width, height);
    }

    void WorldObject::setTexture(int texture) {
        this->texture = texture;
    }

    int WorldObject::inverse(int count) {
        return (-1) * count;
    }
