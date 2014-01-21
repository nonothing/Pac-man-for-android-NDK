LOCAL_PATH := $(call my-dir)
APP_PLATFORM := android-10
 
include $(CLEAR_VARS)
	
APP_STL := stlport_static
LOCAL_LDLIBS    := -llog -lGLESv2 -landroid -ldl -lOpenSLES
LOCAL_CFLAGS    := -Werror -DANDROID_NDK -DDISABLE_IMPORTGL -Wno-write-strings
LOCAL_MODULE    := pacman

	
LOCAL_SRC_FILES := \
	model/AAssetFile.cpp\
	model/Rectangle.cpp\
	model/Point.cpp\
	model/WorldObject.cpp\
	model/WorldObjectMove.cpp\
	model/World.cpp\
	model/Player.cpp\
	model/Brick.cpp\
	model/Spirit/Spirit.cpp\
	model/Spirit/Blinky.cpp\
	model/Spirit/Clyde.cpp\
	model/Spirit/Inky.cpp\
	model/Spirit/Pinky.cpp\
	pacmanlib.cpp \
	View/Art.cpp \
	View/WorldRenderer.cpp \
	Controller/WorldController.cpp \
	Controller/SoundController.cpp \
	Sound/OSLContext.cpp \
	Sound/OSLSound.cpp \
	Sound/OSLPlayer.cpp \

 
include $(BUILD_SHARED_LIBRARY)