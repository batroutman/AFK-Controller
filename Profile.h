/*

Blake Troutman 2019

Profile.h

Header for the Profile interface. Utilizes a Controller to define and 
simulate keyboard and mouse input threads.

*/

#ifndef _PROFILE_H_
#define _PROFILE_H_

#include "Controller.h"

class Profile {
	
	public:
		
		// constructor
		Profile(Controller *);
		
		// destructor
		virtual ~Profile();
		
		// overwitable run function (implements the key presses)
		virtual void run() = 0;
		
		// listens to the console for key input to end the run thread
		void terminator();
		
		// getters and setters for pause/stop
		void pause();
		void resume();
		void stop();
		void reset();
		bool isPaused();
		bool isStopped();
		
	protected:
		
		// member variables
		Controller * ctrl;
		bool stopped;
		bool paused;
		
		// proxy functions for the controller
		// (these will manage calls to the controller functions 
		// with consideration to the profile's stopped/paused status)
		void moveMouse(long, long);
		void moveMouseTo(long, long);
		void clickMouse();
		void releaseMouse();
		void pressKey(int);
		void releaseKey(int);
	
}

#endif