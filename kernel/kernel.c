#include "screen.h"
#include "util.h"

void main(){
	//Initialize screen data structure
	int *videoPort;
	videoPort = 0x0463;
	setVideoPort(*videoPort);
	clear_screen();
	int i =0;
	while(i<100){
		char str[2];
		intToStr(i,str);
		print(str);
		print("\n");
		i++;
	}
	print("Done!");
}
