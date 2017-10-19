/*

Blake Troutman 2017
AFK Controller


Simple application that send key scans somewhat randomly every minute or so.
This is intended to be used with Grand Theft Auto V to allow SecuroServ associates to 
maintain their wage payments while being AFK.

Configure to your desire.

DEVELOPER'S NOTE: A 180 degreemouse turn on the x axis is dx = 30,000

*/


#include <iostream>
#define WINVER 0x0500
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <thread>
#include <string>

#include "dik.h"


//
// GLOBALS
//

// This structure will be used to create the keyboard
// input event.
INPUT ip;
INPUT mip;
bool keepGoing = true;

//
// CONSTANTS
//
const int NUM_MODES = 3;

std::string MODES[] = {"TIME_IS_MONEY", "TIME_IS_MONEY_LOSER", "BACK_FORTH"};


//
// HEADERS
//
void initKey();
void initMouse();
void moveMouse(long, long);
void press(int);
void release(int);
int getPressTime();
void run(int);
void terminator();





//
// MAIN FUNCTION
//
int main(int argc, char** argv) {
	
	/* initializers */
	//initialize for random numbers
	srand(time(NULL));
	//initialize the INPUT variables
	initKey();
	initMouse();
	int initialDelay = 10000;
	int mode = 0;
	
	//greeting
	std::cout << "Welcome to the AFK Controller v1.0!" << std::endl;
	
	//menu
	bool localKG = true;
	do{
		
		std::cout << "Type in the number associated with one of the following modes and press ENTER." << std::endl;
		std::cout << "----TYPE IN INTEGERS ONLY----" << std::endl << std::endl;
		
		//print modes
		for(int i = 0; i < NUM_MODES; i++){
			std::cout << i << ") " << MODES[i] << std::endl;
		}
		
		std::cin >> mode;
		
		if(mode < NUM_MODES){
			localKG = false;
		}else{
			std::cout << "Invalid input." << std::endl;
		}//end if
		
	}while(localKG);
	

	//start threads
	std::thread tTerminator (terminator);
	std::thread tRun (run, mode);
	
	
	tRun.join();
	tTerminator.join();
	
	std::cout << "Terminating program." << std::endl;
	
	
	return 0;
}//end main







//initializes the INPUT object
void initKey(){
	
	// Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = DIK_A; // hardware scan code for key (letter A)
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = 0; // virtual-key code
    ip.ki.dwFlags = KEYEVENTF_SCANCODE; //use the wSacan instead of wVk (for DirectX games)
	
}//end initKey

//initialize the mouse object
void initMouse(){
	
	mip.type = INPUT_MOUSE;
	mip.mi.dx = 0;
	mip.mi.dy = 0;
	mip.mi.mouseData = 0;
	mip.mi.dwFlags = MOUSEEVENTF_MOVE;
	mip.mi.time = 0;
	
}//end initMouse

void moveMouse(long x, long y){
	
	mip.mi.dx = x;
	mip.mi.dy = y;
	SendInput(1, &mip, sizeof(INPUT));
	
}//end moveMouse

//sets the ip keycod to keyConst and presses it
void press(int keyConst){
	
	ip.ki.wScan = keyConst;
	ip.ki.dwFlags = KEYEVENTF_SCANCODE;
	SendInput(1, &ip, sizeof(INPUT));
	
}//end press

//sets ip keycode and releases
void release(int keyConst){
	
	ip.ki.wScan = keyConst;
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
	
}//end release

int getPressTime(){
	return ((rand() % 200) + 1);
}//end getPressTime


//thread that will send keyboard input to the game
void run(int mode){
	
	//countdown
	int seconds = 10;
	std::cout << "Mode: " << mode << ". Waiting 10 seconds before procedure starts." << std::endl;
	std::cout << "Use this time to open your game." << std:: endl;
	
	for(int i = seconds; i > 0; i--){
		std::cout << i << "\t";
		Sleep(1000);
	}
	
	std::cout << std::endl;
	
	if(mode == 0){
		
		//TIME_IS_MONEY
		while(keepGoing){
			press(DIK_W);
			Sleep(60 * 1000);
			release(DIK_W);
			
			Sleep(1000 + getPressTime());
			press(DIK_S);
			Sleep(100 + getPressTime());
			release(DIK_S);
			
			
			press(DIK_Z);
			Sleep(getPressTime());
			release(DIK_Z);
		}//end while
		
	}else if(mode == 1){
		
		//TIME_IS_MONEY_LOSER
		while(keepGoing){
			press(DIK_W);
			Sleep(60 * 1000);
			release(DIK_W);
			
			Sleep(7000 + getPressTime());
			press(DIK_S);
			Sleep(100 + getPressTime());
			release(DIK_S);
			
			
			press(DIK_Z);
			Sleep(getPressTime());
			release(DIK_Z);
		}
		
	}else if(mode == 2){
		
		//BACK_FORTH
		while(keepGoing){
			
			press(DIK_W);
			Sleep(9 * 1000);
			release(DIK_W);
			
			//pause
			Sleep(5 * 1000);
			
			//turn
			moveMouse(30000, 0);
			
			press(DIK_Z);
			Sleep(getPressTime());
			release(DIK_Z);

		}//end while
		
	}//end if
	

	
	
}//end run /////////////////////////////////////////////

//thread that gets user input from console and acts as control for program
void terminator(){
	
	std::cout << "To quit this application, type 'q' and ENTER into this console." << std::endl;
	std::string in;
	
	do{
		
		std::cin >> in;
		
		if(in == "q" || in == "Q" || in == "quit" || true){
			keepGoing = false;
			std::cout << "Application has been set for termination." << std::endl;
			std::cout << "Please allow at most approx. 1 minute for the application to gracefully terminate the active thread." << std::endl;
			std::cout << "Thank you for using AFK Controller!" << std::endl;
		}else{
			std::cout << "unrecognized input" << std::endl;
			std::cout << "press 'q' and ENTER to quit application." << std::endl;
		}
		
	}while(keepGoing);
	
}//end terminator



