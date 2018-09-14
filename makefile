#
# Blake Troutman 2018
#
# makefile for AFK Controller
#

WindowsController.o: WindowsController.h WindowsController.cpp Controller.h
	g++ -c WindowsController.cpp -o WindowsController.o