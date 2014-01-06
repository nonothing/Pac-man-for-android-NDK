package com.pacman.free;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

public class PacmanView extends GLSurfaceView {

	private static AssetManager assetManager;

	public PacmanView(Context context) {
		super(context);
		assetManager = context.getAssets();
		setEGLContextClientVersion(2);

		setRenderer(new PacmanRenderer());
	};

	private static class PacmanRenderer implements GLSurfaceView.Renderer {
		public void onSurfaceCreated(GL10 unused, EGLConfig config) {
		}

		public void onDrawFrame(GL10 unused) {
			PacmanLib.step();
		}

		public void onSurfaceChanged(GL10 unused, int width, int height) {
			PacmanLib.init(width, height, new PngManager(assetManager),
					assetManager);
		}
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		int Action = event.getAction();
		switch (Action) {
		case MotionEvent.ACTION_DOWN:
			PacmanLib.actionDown(event.getX(), event.getY());
			break;
		case MotionEvent.ACTION_MOVE:
			PacmanLib.actionMove(event.getX(), event.getY());
			break;
		case MotionEvent.ACTION_UP:
			PacmanLib.actionUp(event.getX(), event.getY());
			break;
		}
		return true;
	}

}
