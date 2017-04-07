#include "screen.h"
#include "util.h"
isSetup = false;
/* Copy bytes from one place to another */
void memory_copy(char* source, char* dest, int no_bytes){
	int i;
	for(i=0; i<no_bytes;i++){
		*(dest + i) = *(source + i);
	}
}

/* Cast integer to string */
char* intToStr(int i, char b[]){
	char const digit[] = "0123456789";
	char* p = b;
	if(i<0){
		*p++ = "-";
		i *= -1;
	}
	int shifter = i;
	do{ //Move to where representation ends
		++p;
		shifter = shifter/10;
	}while(shifter);
	*p = '\0';
	do{
		*--p = digit[i%10];
		i = i/10;
	}while(i);
	return b;
}

/* Exponential function, raise base to exp-power */
int pow(int base, int exp){
	int total = 1;
	for(int i=0;i<exp;i++){
		total = total*base;
	}
	return total;
}


/* Cast string to integer */
int strToInt(char* s){
	int mul = 1;
	//Check if negative
	if(s[0]=='-'){
		mul = -1;
		s++;
	}
	char bak[strlen(s)];
	reverseString(s,bak);
	int total = 0;
	for(int i=0;i<strlen(s);i++){
		int x;
		switch(bak[i]){
			case '1': x=1;break;
			case '2': x=2;break;
			case '3': x=3;break;
			case '4': x=4;break;
			case '5': x=5;break;
			case '6': x=6;break;
			case '7': x=7;break;
			case '8': x=8;break;
			case '9': x=9;break;
			default:break;
		}
		total += pow(10,i) * x;
		char dig[5];
	}
	return total;
}

void reverseString(char *in, char* out){
	int t = strlen(in)-1;
	int bot = 0;
	while(t>-1){
		out[bot] = in[t];
		t--;
		bot++;
	}
	out[bot] = 0;
}


//Halt and catch fire
void halt_acf(){
	print("Halted! Unable to Recover! Reset Needed");
	while(true){
		asm("nop");
	}
}

//Return whether 2 strings are equal
int strcmp(char *a, char *b){
	for(int i=0;a[i]!=0&&b[i]!=0;i++){
		if(!(a[i]==b[i])){
			return false;
		}
	}
	return true;
}

int strlen(char *str){
	int i =0;
	while(str[i]!=0){
		i++;
	}
	return i;
}
