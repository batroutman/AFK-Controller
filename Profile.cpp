/*

Blake Troutman 2019

Profile.cpp

Implementation of Profile object methods. See Profile.h for details.

*/

#include "Profile.h"


// constructor
Profile::Profile(Controller * ctrl): stopped(false), paused(false)
{
	
	this->ctrl = ctrl;
	
}