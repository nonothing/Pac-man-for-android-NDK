package com.pacman.free;

import android.content.res.AssetManager;

public class PacmanLib {
	
	static{
		System.loadLibrary("pacman");
	}
	
	public static final String tag = "pacman";
	
	public static native void init(int width, int height, PngManager pngManager, AssetManager assetManager);
	public static native void step();
	
	public static native void attackSpirits();
	public static native void timeBonus();
	public static native void pacmanMove();
	
	public static native void actionUp(float x, float y);
    public static native void actionDown(float x, float y);
    public static native void actionMove(float x, float y);
	
	public static native void free();
}
