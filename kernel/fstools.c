#include "screen.h"
#include "filesystem.h"


void dir(){
	struct File *listing = getListing();
	//Print the header
	println("Main Directory Listing");
	fillLine('-');
	if(listing==0){
		println("Directory Emptey");
	}else{
		println("Filename | Type");
		int length=getLength();
		int i = 0;
		while(i!=length){
			print_char(listing[i].name,-1,-1,0);
			print("|");
			print(&(listing[i].type));
			print_char('\n',-1,-1, 0);
			i++;
		}
	}
	fillLine('-');
}
	
