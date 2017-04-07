#include "util.h"
#include "keyboard.h"
#include "screen.h"
#include "shell.h"
#include "input.h"


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
		print("\n Saving file...");
		blockUntilKeypress();
	}
	unsetHeader();
	clear_screen();
}
