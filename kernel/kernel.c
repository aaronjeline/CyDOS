#include "screen.h"
#include "keyboard.h"
#include "screen.h"
#include "util.h"
#include "shell.h"
#include "notepad.h"

void keyboardDBG();

void printMenu(){
	clear_screen();
	print("Welcome to CyDOS!\n");
	print("Please select a mode:\n");
	print("1: Load interactive shell\n");
	print("2: Enter keyboard debug mode\n");
	print("3: Halt machine\n");
}


void main(){
	//Initialize screen data structure
	int *videoPort;
	videoPort = 0x0463;
	setVideoPort(*videoPort);
	clear_screen();
	initialize();
	printMenu();
	while(true){
		switch(getChar(getScancode())){
			case '1': prompt();printMenu();break;
			case '2': keyboardDBG();printMenu();break;
			case '3': halt_acf();break;
			default:break;
		}
	}
}

void keyboardDBG(){
	int last = 0;
	int running = true;

	while(running){
		int new = getScancode();
		if(new!=last){
			char code[5];
			clear_screen();
			print("Keyboard DEBUG system, press Ctrl-C to exit\n");
			print(intToStr(new,code));
		}
		if(getCtrl()&&getChar(new)=='c'){
			running = false;
		}
		last = new;
	}
}
