#include "string.h"
#include "util.h"
#include "screen.h"

//Adds two strings
char* add(char* x, char* y, char* sum){
	int xLen = len(x);
	int yLen = len(y);

	int sPos = 0;
	for(int i=0;i<xLen;i++){
		sum[sPos] = x[i];
		sPos++;
	}
	for(int i=0;i<yLen;i++){
		sum[sPos] = y[i];
		sPos++;
	}
	//Null terminate
	sum[sPos] = '\0';

	return sum;
}

//Gets the length of a string
int len(char* str){
	int len = 0;
	while(str[len]){
		len++;
	}
	return len;
}
