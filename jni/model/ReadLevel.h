#include "model/Brick.h"
#include "model/Level.h"
class ReadLevel{
public:
	char* token;
	Level* level;
	AAssetManager* assetManager;

	ReadLevel(JNIEnv* env,  jobject javaAssetManager){
		assetManager = AAssetManager_fromJava(env, javaAssetManager);
		level = new Level();
	}
		int get_number() {
			int res = 0;

			while (*token == ' ')
				token++;

			while (*token >= '0' && *token <= '9') {
				res = res * 10 + (*token - '0');
				token++;
			}

			return res;
		}

		void loadLevels(){
				char *  name = new char[64];
				strcpy(name, "levels/111.txt");
				AAssetFile f = AAssetFile(assetManager, name);
				char buf[f.size()+1];
				int count = f.read(&buf,f.size(),1);
				buf[f.size()] = '\0';
				f.close();
				List<Brick*>* bricks = new List<Brick*>();
				token = buf;
				int x = 0;
				int y = 0;
				while (*token) {
					switch (get_number()) {
					            case 1:
					            	bricks->append(new Brick(new Point(x, y), point,30,30));
					                break;
					            case 2:
					            	bricks->append(new Brick(new Point(x, y), horizontal,30,30));
					                break;
					            case 3:
					            	bricks->append(new Brick(new Point(x, y), vertical,30,30));
					                break;
					            case 4:
					            	bricks->append(new Brick(new Point(x, y), angle_lv,30,30));
					                break;
					            case 5:
					            	bricks->append(new Brick(new Point(x, y), angle_rv,30,30));
					                break;
					            case 6:
					            	bricks->append(new Brick(new Point(x, y), angle_rd,30,30));
					                break;
					            case 7:
					            	bricks->append(new Brick(new Point(x, y), angle_ld,30,30));
					                break;
					            case 8:
					            	bricks->append(new Brick(new Point(x, y), arc_down,30,30));
					                break;
					            case 9:
					            	bricks->append(new Brick(new Point(x, y), arc_left,30,30));
					                break;
					            case 10:
					            	bricks->append(new Brick(new Point(x, y), arc_right,30,30));
					                break;
					            case 11:
					            	bricks->append(new Brick(new Point(x, y), arc_up,30,30));
					                break;
					            case 12:
					            	bricks->append(new Brick(new Point(x, y), arc2_down,30,30));
					                break;
					            case 13:
					            	bricks->append(new Brick(new Point(x, y), arc2_right,30,30));
					                break;
					            case 14:
					            	bricks->append(new Brick(new Point(x, y), arc2_left,30,30));
					                break;
					            case 15:
					            	bricks->append(new Brick(new Point(x, y), arc2_up,30,30));
					                break;
					            case 16:
					            	bricks->append(new Brick(new Point(x, y), bonus,30,30));
					                break;
					            case 90:
					            	level->pointBlinky = new Point(x, y);
					            	bricks->append(new Brick(new Point(x, y), none,30,30));
					                break;
					            case 91:
					            	level->pointPinky = new Point(x, y);
					            	bricks->append(new Brick(new Point(x, y), none,30,30));
					                break;
					            case 92:
					            	level->pointClyde = new Point(x, y);
					            	bricks->append(new Brick(new Point(x, y), none,30,30));
					                break;
					            case 93:
					            	level->pointInky = new Point(x, y);
					            	bricks->append(new Brick(new Point(x, y), none,30,30));
					                break;
					            case 99:
					            	bricks->append(new Brick(new Point(x, y), none,30,30));
					                break;
					            default:
					            	bricks->append(new Brick(new Point(x, y), background,30,30));
					                break;
					            }
									x++;
					            if (x == 25) {
					                x = 0;
					                y++;
					            }
					            if (y == 15) {
					                y = 0;
					            }
					}
				level->bricks = bricks;
		}

};
