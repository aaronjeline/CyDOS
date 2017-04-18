#include "filesystem.h"
#include "util.h"
int startingOffset = 0xb000;


struct Directory mainDir;



void initMainDirectoy(){
	mainDir.listing = 0;
	mainDir.length = 0;
}


void createTextFile(char *name, char* buffer, int size){
	//Create the file & fill out the fields
	struct File newFile;
	if(mainDir.length==0){
		//Directory is starting
		newFile.start = startingOffset;
		mainDir.listing = 0xa100;
	}else{
		newFile.start = mainDir.listing[mainDir.length].start + mainDir.listing[mainDir.length].length;
	}
	memory_copy(name, newFile.name, strlen(name));
	newFile.name[strlen(name)]=0;
	memory_copy("txt", newFile.type, 3);
	newFile.length = size;
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

int getFileLength(char *name){
	if(mainDir.listing==0){
		return 0;
	}
	int i = 0;
	while(i!=mainDir.length){
		if(strcmp(name,mainDir.listing[i].name)){
			return mainDir.listing[i].length;
		}
		i++;
	}
	return 0;
}

void getTextFile(char *name, char *buffer){
	if(mainDir.listing==0){
		return;
	}
	int i = 0;
	while(i!=mainDir.length){
		if(strcmp(name,mainDir.listing[i].name)){
			mainDir.listing[i].length;
			memory_copy(mainDir.listing[i].start, buffer, mainDir.listing[i].length);
			return;
		}
		i++;
	}
}
	

struct File* getListing(){
	return mainDir.listing;
}

int getLength(){
	return mainDir.length;
}
