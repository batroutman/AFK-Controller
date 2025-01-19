#
# Blake Troutman 2018
#
# makefile for AFK Controller
#
main.exe: main.cpp
	g++ --std=c++11 main.cpp -o main.exe

testbed.exe: testbed.cpp WindowsController.o 
	g++ WindowsController.o testbed.cpp -o testbed.exe

WindowsController.o: WindowsController.h WindowsController.cpp Controller.h
	g++ -c WindowsController.cpp -o WindowsController.o

clean:
	rm testbed.exe
	rm *.o

runtest: testbed.exe
	./testbed.exe

run: main.exe
	./main.exe