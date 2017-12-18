/*

Blake Troutman 2017
AFK Controller


Simple application that sends seemingly dynamic key scans to DirectX games (in foreground).
This is intended to be used with Grand Theft Auto V (PC) to allow AFK farming to persist without
being easily detectable.

You can search for AFK farming playlists on reddit and build a profile for it here by taking
the following steps:

1) increment the constant NUM_MODES.
2) append the string name of your mode to the constant MODES[]
3) append your algorithm to the if-branch in the run function, under "ADD MODES HERE"

Configure to your desire.

DEVELOPER'S NOTE: A 180 degreemouse turn on the x axis is dx ~ 30,000

*/


#include <iostream>
#define WINVER 0x0500
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <thread>
#include <mutex>
#include <string>

//for the scan codes
#include "dik.h"


/////////////////////
////   GLOBALS   ////
/////////////////////

// This structure will be used to create the keyboard
// input event.
INPUT ip;
INPUT mip;
bool keepGoing = true; //KG for threads
bool programKG = true; //KG for application

std::mutex consoleMtx;

/////////////////////
////  CONSTANTS  ////
/////////////////////
const int NUM_MODES = 5;
std::string MODES[] = {"exit", "TIME_IS_MONEY", "TIME_IS_MONEY_LOSER", "BACK_FORTH", "DOODLE_JUMP"};


/////////////////////
////   HEADERS   ////
/////////////////////
void initKey();
void initMouse();
void menu();
void moveMouse(long, long);
void moveMouseTo(long, long);
void clickMouse();
void releaseMouse();
void press(int);
void release(int);
int getPressTime();
void run(int);
void terminator();
void rest(int, bool &);
void rest(int restTime, int precision, bool &);





////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////             MAIN FUNCTION            /////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
	
	/* initializers */
	//initialize for random numbers
	srand(time(NULL));
	//initialize the INPUT variables
	initKey();
	initMouse();
	
	//greeting
	std::cout << "Welcome to the AFK Controller v1.0!" << std::endl;
	
	while(programKG){
		menu();
	}

	return 0;
}//end main -------------------------------------------------------------------------------




//menu
void menu(){
	
	//initialize
	keepGoing = true;
	int mode = 0;
	
	//menu
	bool localKG = true;
	do{
		
		consoleMtx.lock();
		std::cout << "Type in the number associated with one of the following modes and press ENTER." << std::endl;
		std::cout << "---- TYPE IN INTEGERS ONLY ----" << std::endl << std::endl;
		
		//print modes
		for(int i = 0; i < NUM_MODES; i++){
			std::cout << i << ") " << MODES[i] << std::endl;
		}
		consoleMtx.unlock();
		
		std::cin >> mode;
		
		if(mode < NUM_MODES){
			localKG = false;
		}else{
			consoleMtx.lock();
			std::cout << "Invalid input." << std::endl;
			consoleMtx.unlock();
		}//end if
		
	}while(localKG);
	
	//if they aren't trying to exit the program:
	if(mode != 0){
		//start threads
		std::thread tTerminator (terminator);
		std::thread tRun (run, mode);
		tRun.join();
		tTerminator.join();
	}else if(mode == 0){
		programKG = false;
		
		consoleMtx.lock();
		std::cout << "Exiting program" << std::endl;
		consoleMtx.unlock();
	}//end if

	
}//end menu











////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////             RUN FUNCTION             /////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

//thread that will send keyboard input to the game
void run(int mode){
	
	//countdown
	int seconds = 10;
	consoleMtx.lock();
	std::cout << "Mode: " << mode << ". Waiting 10 seconds before procedure starts." << std::endl;
	std::cout << "Use this time to open your game." << std:: endl;
	consoleMtx.unlock();
	
	for(int i = seconds; i > 0; i--){
		consoleMtx.lock();
		std::cout << i << "\t";
		consoleMtx.unlock();
		Sleep(1000);
	}
	
	std::cout << std::endl;
	
	
	/////////////////////////
	///  ADD MODES HERE   ///
	/////////////////////////
	if(mode == 1){
		
		//TIME_IS_MONEY
		while(keepGoing){
			
			if(keepGoing){
				press(DIK_W);
				rest(60 * 1000, keepGoing);
				release(DIK_W);
			}
			
			if(keepGoing){
				rest(1000 + getPressTime(), keepGoing);
			}
			
			if(keepGoing){
				press(DIK_S);
				rest(100 + getPressTime(), keepGoing);
				release(DIK_S);
			}
			
			if(keepGoing){
				press(DIK_Z);
				rest(getPressTime(), keepGoing);
				release(DIK_Z);
			}
			
			
			
		}//end while
		
	}else if(mode == 2){
		
		//TIME_IS_MONEY_LOSER
		while(keepGoing){
			
			if(keepGoing){
				press(DIK_W);
				rest(60 * 1000, keepGoing);
				release(DIK_W);
			}
			
			if(keepGoing){
				rest(7000 + getPressTime(), keepGoing);
			}
			
			if(keepGoing){
				press(DIK_S);
				rest(100 + getPressTime(), keepGoing);
				release(DIK_S);
			}

			if(keepGoing){
				press(DIK_Z);
				rest(getPressTime(), keepGoing);
				release(DIK_Z);
			}

			
		}
		
	}else if(mode == 3){
		
		//BACK_FORTH
		while(keepGoing){
			
			if(keepGoing){
				press(DIK_W);
				rest(9 * 1000, keepGoing);
				release(DIK_W);
			}
			
			//pause
			if(keepGoing){
				rest(5 * 1000, keepGoing);
			}
			
			//turn
			if(keepGoing){
				moveMouse(30000, 0);
			}
			
			if(keepGoing){
				press(DIK_Z);
				rest(getPressTime(), keepGoing);
				release(DIK_Z);
			}
			
			

		}//end while
		
	}else if(mode == 4){
	
		//DOODLE_JUMP
		while(keepGoing){
			
			
			
			//feed
			if(keepGoing){
				moveMouseTo(1747, 205);
				clickMouse();
				releaseMouse();
				rest(7000, keepGoing);
			}
			
			//try to train n times
			for(int i = 0; i < 10; i++){
				
				//chat button
				if(keepGoing){
					moveMouseTo(95, 53);
					clickMouse();
					releaseMouse();
					rest(250, keepGoing);
				}
				
				//into menu
				if(keepGoing){
					moveMouseTo(180, 51);
					rest(500, keepGoing);
				}
				
				//pets
				if(keepGoing){
					moveMouseTo(190, 193);
					rest(500, keepGoing);
				}
				
				//tricks
				if(keepGoing){
					moveMouseTo(368, 192);
					rest(500, keepGoing);
				}
				
				//jump
				if(keepGoing){
					moveMouseTo(472, 194);
					rest(500, keepGoing);
					clickMouse();
					releaseMouse();
				}
				
				//rest before trying again
				rest(3000, keepGoing);
				
			}
			
			//rest to give buffer time to halt program
			rest(5000, keepGoing);
			
			
			
		}//end while
	
	}//end if
	

	
	
}//end run -------------------------------------------------------------------------------










////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////         TERMINATOR FUNCTION          /////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

//thread that gets user input from console and kills current run thread
void terminator(){
	
	consoleMtx.lock();
	std::cout << "To quit this application, type something into the console and press ENTER." << std::endl;
	consoleMtx.unlock();
	std::string in;
	
	do{
		
		std::cin >> in;
		
		if(in == "q" || in == "Q" || in == "quit" || true){
			keepGoing = false;
			consoleMtx.lock();
			std::cout << "Thread has been set for termination." << std::endl;
			std::cout << "Thank you for using AFK Controller!" << std::endl;
			consoleMtx.unlock();
		}else{
			consoleMtx.lock();
			std::cout << "unrecognized input" << std::endl;
			std::cout << "press 'q' and ENTER to quit application." << std::endl;
			consoleMtx.unlock();
		}
		
	}while(keepGoing);
	
	Sleep(1000);
	
}//end terminator  ------------------------------------------------------------------------


















////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////           UTILITY FUNCTIONS          /////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


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
	mip.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &mip, sizeof(INPUT));
	
}//end moveMouse

void moveMouseTo(long x, long y){
	
	long ndx = (x / 1920.0) * 65535;
	long ndy = (y / 1080.0) * 65535;
	mip.mi.dx = ndx;
	mip.mi.dy = ndy;
	mip.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	SendInput(1, &mip, sizeof(INPUT));
	
}//end moveMouse

void clickMouse(){
	mip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &mip, sizeof(INPUT));
}//end clickMouse

void releaseMouse(){
	mip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &mip, sizeof(INPUT));
}//end releaseMouse

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

//sleep, but check the value of condition at some interval
void rest(int restTime, bool & condition){
	
	int precision = 100; //in milliseconds
	while(condition && (restTime > 0)){
		Sleep(precision);
		restTime -= 100;
	}//end while
	
}//end rest(int, bool)

//sleep, but check the value of condition at GIVEN interval
void rest(int restTime, int precision, bool & condition){
	
	while(condition && (restTime > 0)){
		Sleep(precision);
		restTime -= 100;
	}//end while
	
}//end rest(int, bool)





