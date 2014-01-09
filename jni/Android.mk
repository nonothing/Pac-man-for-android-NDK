LOCAL_PATH := $(call my-dir)
APP_PLATFORM := android-9
 
include $(CLEAR_VARS)
	
APP_STL := stlport_static
LOCAL_LDLIBS    := -llog -lGLESv2 -landroid -ldl -lOpenSLES
LOCAL_CFLAGS    := -Werror -DANDROID_NDK -DDISABLE_IMPORTGL
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
	pacmanlib.cpp \
	View/Art.cpp \
	View/WorldRenderer.cpp \
	Controller/WorldController.cpp \
 
include $(BUILD_SHARED_LIBRARY)