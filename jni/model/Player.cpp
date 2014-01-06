#include "Player.h"

Player::Player(Point* position , int texture ,int width, int height) :WorldObjectMove(position,texture,width,height){
		life = 3;
	}

void Player::animate() {
        bool change =
                (getPosition()->getX() % 15 == 0 && (direction == LEFT || direction == RIGHT))
                || (getPosition()->getY() % 15 == 0 && (direction == UP || direction == DOWN));

        if(isOpen && change){
        	isOpen = false;
        }
        else if(!isOpen && change){
        	isOpen = true;
        }
        if (direction == LEFT) {
            if (isOpen) {
                setTexture(pacmanLeftOpen);
            } else {
                setTexture(pacmanLeftClose);
            }
        }
        if (direction == RIGHT) {
            if (isOpen) {
                setTexture(pacmanRightOpen);
            } else {
                setTexture(pacmanRightClose);
            }
        }
        if (direction == UP) {
            if (isOpen) {
                setTexture(pacmanUpOpen);
            } else {
                setTexture(pacmanUpClose);
            }
        }
        if (direction == DOWN) {
            if (isOpen) {
                setTexture(pacmanDownOpen);
            } else {
                setTexture(pacmanDownClose);
            }
        }
    }

    int Player::getLife() {
        return life;
    }

    void Player::setLife(int life) {
        this->life = life;
    }

