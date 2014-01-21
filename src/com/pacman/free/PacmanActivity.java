package com.pacman.free;

import java.util.Timer;
import java.util.TimerTask;

import android.os.Bundle;
import android.app.Activity;
import android.view.KeyEvent;

public class PacmanActivity extends Activity{
	Timer mainTimer;
	PacmanView pacmanView;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
       super.onCreate(savedInstanceState);
      
       pacmanView = new PacmanView(getApplication());
       mainTimer = new Timer();
       mainTimer.schedule(attackSpirits, 1, 60);
       mainTimer.schedule(pacmanMove, 1, 50);
       mainTimer.schedule(timeBonus, 1, 1000);
       setContentView(pacmanView);   
    }

    TimerTask attackSpirits = new TimerTask() {
		@Override
		public void run() {
			PacmanLib.attackSpirits();			
		}
	};
	
	TimerTask pacmanMove = new TimerTask() {
		@Override
		public void run() {
			PacmanLib.pacmanMove();		
		}
	};
	
	TimerTask timeBonus = new TimerTask() {
		@Override
		public void run() {
			PacmanLib.timeBonus();		
		}
	};
    
    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
    }
    
    @Override
    protected void onStop() {
        super.onStop();
        PacmanLib.free();
        finish();
    }
    
    @Override
    protected void onDestroy(){	
    	super.onDestroy();
    }
    public boolean onKeyDown(int keyCode, KeyEvent event) {
	        if (keyCode == KeyEvent.KEYCODE_BACK) {
	        			finish();
	                return true;
	        }
	    return super.onKeyDown(keyCode, event);
	}
}
