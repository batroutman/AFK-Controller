/*

Blake Troutman 2018

WindowsController.cpp

Implementation of WindowsController object. See WindowsController.h for details.

*/



#include "WindowsController.h"
#include "dik.h"



//default constructor
WindowsController::WindowsController(): Controller(), ip(), mip()
{
	
	this->initKey();
	this->initMouse();
	
}


//destructor
WindowsController::~WindowsController()
{
	//empty
}


//key variable initializer
void WindowsController::initKey()
{
	
	// Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = DIK_A; // hardware scan code for key (letter A)
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = 0; // virtual-key code
    ip.ki.dwFlags = KEYEVENTF_SCANCODE; //use the wSacan instead of wVk (for DirectX games)
	
}


//mouse variable initializer
void WindowsController::initMouse()
{
	
	mip.type = INPUT_MOUSE;
	mip.mi.dx = 0;
	mip.mi.dy = 0;
	mip.mi.mouseData = 0;
	mip.mi.dwFlags = MOUSEEVENTF_MOVE;
	mip.mi.time = 0;
	
}


//press a key down
void WindowsController::pressKey(int keyConst)
{
	
	this->ip.ki.wScan = keyConst;
	this->ip.ki.dwFlags = KEYEVENTF_SCANCODE;
	SendInput(1, &ip, sizeof(INPUT));
	
}


//lift a key up
void WindowsController::releaseKey(int keyConst)
{
	
	this->ip.ki.wScan = keyConst;
	this->ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
	
}


//move mouse (differential)
void WindowsController::moveMouse(long dx, long dy)
{
	
	this->mip.mi.dx = dx;
	this->mip.mi.dy = dy;
	this->mip.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &mip, sizeof(INPUT));
	
}


//move mouse to absolute location (0 to 65535)
void WindowsController::moveMouseTo(long x, long y)
{
	
	this->mip.mi.dx = x;
	this->mip.mi.dy = y;
	this->mip.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	SendInput(1, &mip, sizeof(INPUT));
	
}



