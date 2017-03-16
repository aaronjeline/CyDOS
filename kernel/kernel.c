#include "screen.h"
#include "util.h"

void main(){
	//Initialize screen data structure
	int *videoPort;
	videoPort = 0x0463;
	setVideoPort(*videoPort);
	clear_screen();
	print("Hello World\nHello NewLine/n");
}
