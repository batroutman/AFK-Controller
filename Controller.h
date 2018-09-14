/*

Blake Troutman 2018

Controller.h

Header for an interface of OS controller functions for controlling user input of the
operating system. Ideal for use with applications to automate computer processes (such as
video games)

*/

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

class Controller{
	
	public:
		
		//destructor
		virtual ~Controller(){};
		
		//experimental mouse methods
		virtual void moveMouse(long, long) = 0;
		virtual void moveMouseTo(long, long) = 0;
		virtual void clickMouse() = 0;
		virtual void releaseMouse() = 0;
		
		//sets the ip keycode to keyConst and presses it
		virtual void pressKey(int keyConst) = 0;
		
		//sets ip keycode to keyConst and releases
		virtual void releaseKey(int keyConst) = 0;
		
};

#endif