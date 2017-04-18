#include "shell.h"
#include "util.h" 
#include "screen.h"
#include "notepad.h"
#include "brainfuck.h"
#include "fstools.h"

/* SHELL SIGNALLING
0 - no errors, continue
1 - exit prompt
* - report the error code
*/


int echo(char *text){
	println(text);
	return 0;
}

void help(){
	println("CyDOS Interactive Shell Help Page");
	println("Shell commands are comprised of two parts, the program and the arguments");
	println("Commands are issued as:");
	println("	<prgm> ?<args>");
	println("Programs are a max of five characters");
	println("Arguments are a max of 95 characters");
	println("To see a list of built in programs, type bltin");
}

void builtIn(){
	println("CyDOS built in programs:");
	println("	echo: echoes args");
	println("	cls: clear the terminal");
	println("	help: display help page");
	println("	bltin: display this list");
	println("	note: open system notepad");
	println("	inter: open system interpreter");
	println("	dir: directory listing");
	println("	cat: display contents of a text file");
	println("	exit: exit the shell");
}

int handle(char *command){
	int length;
	for(int i=0;command[i]!=0;i++){
		length++;
	}
	char prgm[5];
	int spacePos;
	int j =0;
	int seeking = true;
	while(seeking){
		if(command[j]==' '||j==5){
			seeking = false;
		}else{
			prgm[j]=command[j];
			j++;
		}
	}
	char args[20];
	for(int i=0;i<20;i++){
		args[i] = 0;
	}
	seeking = true;
	int i =0;
	j++;
	while(seeking){
		if(command[j]==0||j==95){
			seeking = false;
		}else{
			args[i]=command[j];
			i++;j++;
		}
	}
	j--;
	args[j] = 0;
	int code;
	//Check built in tools, then check FS
	if(strcmp(prgm,"echo")){
		code = echo(args);
	}else if(strcmp(prgm,"exit")){
		code = 1;
	}else if(strcmp(prgm,"cls")){
		clear_screen();
		code = 0;
	}else if(strcmp(prgm,"help")){
		help();
		code = 0;
	}else if(strcmp(prgm,"bltin")){
		builtIn();
		code = 0;
	}else if(strcmp(prgm,"note")){
		notepad();
		code = 0;
	}else if(strcmp(prgm,"inter")){
		brainfuck();
		code = 0;
	}else if(strcmp(prgm,"dir")){
		dir();
		code = 0;
	}else{
		print("No Such Program!\n");
		code = 0;
	}
	return code;
}

void reportError(int errorCode){
	print("Program Reproted Error! CODE: ");
	char code[5];
	print(intToStr(errorCode, code));
}

int specialCharHandling(char c){
	int toReturn;
	switch(c){
		case 16:backspace();toReturn=0;break;
		default: toReturn=1;break;
	}
	return toReturn;
}
	

void prompt(){
	clear_screen();
	print("CyDOS Interactive Shell v1.0\n");
	int shouldRun = true;
	while(shouldRun){
		unsetHeader();
		print_char('>',-1,-1,0);
		char last = getChar(getScancode());
		char line[100];
		//Clear the line
		for(int i=0;i<100;i++){
			line[i] = 0;
		}
		int linePos = 0;
		int gatheringLine = true;
		while(gatheringLine){
			//Arrow keys
			switch(getScancode()){
				case 75: nudgeCursor(-1);break;
				case 77: nudgeCursor(1);break;
			}
			//Check for screen clear
			if(getCtrl()&&getAlt()){
				clear_screen();
				gatheringLine = false;
				line[0] = 0;
			}
			char new = getChar(getScancode());
			if(new!=last){
				if(new==16){
					//Delete key pressed
					backspace();
					linePos--;
					line[linePos] = 0;
				}else{
					print_char(new,-1,-1,0);
					if(new=='\n'){
						gatheringLine = false;
					}else if(new!=0){
						line[linePos] = new;
						linePos++;
					}
				
				}
			}
			last = new;
		}
		if(line[0]!=0){
			int response = handle(line);
			switch(response){
			case 0:break;
			case 1:shouldRun = false;break;
			default:reportError(response);break;
			}
		}
	}
	print("\n Exiting Shell!");
}


