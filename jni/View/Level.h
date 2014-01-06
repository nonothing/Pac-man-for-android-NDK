#include <stdio.h>
struct Level{
	Texture* map;
	char* name;
	Level(): name(NULL), map(NULL){};
	Level(char* _name, Texture* _map):name(_name), map(_map){};
	~Level(){
		if(name){
			delete[] name;
			name = NULL;
		}
		if(map){
			delete map;
			map = NULL;
		}
	}
};
