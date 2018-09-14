/*

Blake Troutman 2018

WindowsController.h

Header for derived class of Controller, intended for use with Windows OS.

*/


#ifndef _WINDOWS_CONTROLLER_H_
#define _WINDOWS_CONTROLLER_H_

#include "Controller.h"

#include <windows.h>

class WindowsController: public Controller{

	public:
		
		//default contructor
		WindowsController();
		
		//destructor
		~WindowsController();
		
		//presses a key based on the DIK code keyConst
		virtual void pressKey(int keyConst);
		
		//releases a key based on the DIK code keyConst
		virtual void releaseKey(int keyConst);
		
		//experimental mouse methods
		virtual void moveMouse(long, long);
		virtual void moveMouseTo(long, long);
		virtual void clickMouse();
		virtual void releaseMouse();
		
	protected:
		
		//initializer for keyboard variable
		void initKey();
		
		//initializer for mouse variable
		void initMouse();
		
		//  --  member variables  --  //
		
		//keyboard input variable
		INPUT ip;
		
		//mouse input variable
		INPUT mip;

};

#endif