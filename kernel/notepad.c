#include "util.h"
#include "keyboard.h"
#include "screen.h"
#include "shell.h"
#include "input.h"
#include "filesystem.h"


void notepad(){
	clear_screen();
	printHeader("NOTEPAD!");
	int bufferSize = numField("Buffer Size",5,false);
	char buffer[bufferSize];
	clear_screen();
	textBuffer(buffer);
	clear_screen();
	print("Save file");
	if(yesNo()){
		int done = false;
		while(!done){
			print_char('\n',-1,-1,0);
			char fileName[10];
			textField("File Name", fileName, false);
			int status = createTextFile(fileName,buffer,bufferSize);
			if(status==0){
				print("\n Saving file...");
				blockUntilKeypress();
				done = true;
			}else{
				println("File already exists.");
				println("r: rename file and try again");
				println("f: force save and overwrite previous file");
				println("q: quick without saving");
				switch(charField("")){
					case 'q':done = true;
				}
			}
	}
	}
	unsetHeader();
	clear_screen();
}
