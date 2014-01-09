#ifndef ETexture_H_
#define ETexture_H_
enum ETexture {
	TEXTURE_NONE,
	blinkyLeft,
	blinkyRight,
	blinkyUp,
	blinkyDown,
	TEXTURE_FONT_CONSOLAS,
	TEXTURE_BRUSHES,
	pacmanLeftOpen,
	pacmanLeftClose,
	pacmanRightOpen,
	pacmanRightClose,
	pacmanUpOpen,
	pacmanUpClose,
	pacmanDownOpen,
	pacmanDownClose,

	//map
	background,horizontal,vertical,point,
	angle_ld,angle_lv,angle_rd,angle_rv,
	arc_down,arc_left,arc_right,arc_up,
	arc2_down,arc2_left,arc2_right,arc2_up,

	TEXTURES_COUNT,

};
#endif /* ETexture_H_ */
