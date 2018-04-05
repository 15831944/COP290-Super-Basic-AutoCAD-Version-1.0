all:	
	g++ -std=c++11 -c my_display.cpp
	g++ -std=c++11 -c main.cpp
	set PATH=c:\GTK\bin;%PATH%
	set PATH=c:\MinGW\bin;%PATH%
	C:\MinGW\msys\1.0\bin\bash.exe -c "echo gcc -Wall -g gui2.c -o gui2 `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0` > compile.bat"
	compile.bat
	g++ -std=c++11 -c file_operators.cpp
	g++ -std=c++11  my_display.o main.o file_operators.o -o fun