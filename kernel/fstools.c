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
			print(listing[i].name);
			print("|");
			print(listing[i].type);
			print_char('\n',-1,-1, 0);
			i++;
		}
	}
	fillLine('-');
}
	
int cat(char *filename){
	int length = getFileLength(filename);
	if(length==0){
		print("No such file: ");
		print(filename);
		println(".txt");
		return 2;
	}
	char buffer[length];
	getTextFile(filename, buffer);
	println(buffer);
	return 0;
}

