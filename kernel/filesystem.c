#include "filesystem.h"
int startingOffset = 0xb000;


struct Directory mainDir;



void initMainDirectoy(){
	mainDir.listing = 0;
	mainDir.length = 0;
}


void createTextFile(char name, char* buffer, int size){
	//Create the file & fill out the fields
	struct File newFile;
	if(mainDir.length==0){
		//Directory is starting
		newFile.start = startingOffset;
		mainDir.listing = 0xa100;
	}else{
		newFile.start = mainDir.listing[mainDir.length].start + mainDir.listing[mainDir.length].length;
	}
	newFile.length = size;
	newFile.name = name;
	//Copy the passed buffer into memory
	int i = 0;
	while(buffer[i]!=0){
		*(newFile.start + i) = buffer[i];
		i++;
	}
	//Update the directories info
	mainDir.listing[mainDir.length] = newFile;
	mainDir.length++;
}

struct File* getListing(){
	return mainDir.listing;
}

int getLength(){
	return mainDir.length;
}
