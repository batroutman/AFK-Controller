/*

testbed.cpp

Blake Troutman 2018

Driver for testing controller architecture.

*/


#include <iostream>


#include "WindowsController.h"
#include "dik.h"



//key press tests
void testKeyPress() {
	
	std::cout << "Starting testKeyPress." << std::endl;
	
	Controller * ctrl = new WindowsController();
	Sleep(2000);
	ctrl->pressKey(DIK_H);
	ctrl->pressKey(DIK_E);
	ctrl->pressKey(DIK_L);
	ctrl->pressKey(DIK_L);
	ctrl->pressKey(DIK_O);
	ctrl->pressKey(DIK_SPACE);
	ctrl->pressKey(DIK_T);
	ctrl->pressKey(DIK_H);
	ctrl->pressKey(DIK_E);
	ctrl->pressKey(DIK_R);
	ctrl->pressKey(DIK_E);
	Sleep(2000);
	ctrl->releaseKey(DIK_H);
	ctrl->releaseKey(DIK_E);
	ctrl->releaseKey(DIK_L);
	ctrl->releaseKey(DIK_L);
	ctrl->releaseKey(DIK_O);
	ctrl->releaseKey(DIK_SPACE);
	ctrl->releaseKey(DIK_T);
	ctrl->releaseKey(DIK_H);
	ctrl->releaseKey(DIK_E);
	ctrl->releaseKey(DIK_R);
	ctrl->releaseKey(DIK_E);
	delete ctrl;
	
	std::cout << "testKeyPress complete." << std::endl;
	
}

//test mouse functionality
void testMouseMove() {
	
	std::cout << "Starting testMouseMove." << std::endl;
	
	Controller * ctrl = new WindowsController();
	Sleep(2000);
	ctrl->moveMouse(400, 100);
	Sleep(2000);
	ctrl->moveMouseTo(5000, 5000);
	delete ctrl;
	
	std::cout << "testMouseMove complete." << std::endl;
	
}

//test mouse clicking
void testMouseClick() {

	std::cout << "Starting testMouseClick." << std::endl;
	
	Controller * ctrl = new WindowsController();
	
	int numClicks = 10;
	Sleep(2000);
	
	for(int i = 0; i < numClicks; i++) {
		ctrl->clickMouse();
		Sleep(10);
		ctrl->releaseMouse();
		Sleep(20);
	}
		
	delete ctrl;
	
	std::cout << "testMouseClick complete." << std::endl;
	
}

int main(int argc, char ** argv) {
	
	std::cout << "Starting main scope." << std::endl;
	//testKeyPress();
	//testMouseMove();
	//testMouseClick();
	std::cout << "Ending main scope." << std::endl;
	
}