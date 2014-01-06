#include <stdio.h>
struct Texture{
	char* pixels; //should be allocated with new[width*height*4]; RGBA
	int width;
	int height;
	Texture(): pixels(NULL), width(0), height(0){}
	Texture(char* p, int w, int h): pixels(p), width(w), height(h){};
	~Texture(){
		if(pixels){
			delete[] pixels;
			pixels = NULL;
		}
	}
};


