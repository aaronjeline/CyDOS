#include "util.h"
#include "keyboard.h"
#include "screen.h"
#include "shell.h"
#include "input.h"

void brainfuck(){
	clear_screen();
	printHeader("Intepreter");
	char* options[3];
	options[0] = "Execute File";
	options[1] = "View File";
	options[2] = "Create new file";
	int i = getSelected(options,3);
}
