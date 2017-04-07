#include "low_level.h"
#include "screen.h"
#include "util.h"


char* scancode = 0xa000;
int lastCode = 0;
int shifted = 0;
int ctrl = 0;
int alt = 0;
int sup = 0;
int canUpdateShift = 0;

int keyboard_test(){
	//Echo the device
	port_byte_out(0x60, 0xEE);
	return port_byte_in(0x60) == 0xEE;
}

void init_scantable(){
	*scancode = 0; //Null character
	*(scancode + 2) = '1';
	*(scancode + 3) = '2';
	*(scancode + 4) = '3';
	*(scancode + 5) = '4';
	*(scancode + 6) = '5';
	*(scancode + 7) = '6';
	*(scancode + 8) = '7';
	*(scancode + 9) = '8';
	*(scancode + 10) = '9';
	*(scancode + 11) = '0';
	*(scancode + 12) = '-';
	*(scancode + 13) = '=';
	*(scancode + 14) = 16; //Delete key
	*(scancode + 15) = '	';
	*(scancode + 16) = 'q';
	*(scancode + 17) = 'w';
	*(scancode + 18) = 'e';
	*(scancode + 19) = 'r';
	*(scancode + 20) = 't';
	*(scancode + 21) = 'y';
	*(scancode + 22) = 'u';
	*(scancode + 23) = 'i';
	*(scancode + 24) = 'o';
	*(scancode + 25) = 'p';
	*(scancode + 26) = '[';
	*(scancode + 27) = ']';
	*(scancode + 28) = '\n';
	*(scancode + 29) = 0;
	*(scancode + 30) = 'a';
	*(scancode + 31) = 's';
	*(scancode + 32) = 'd';
	*(scancode + 33) = 'f';
	*(scancode + 34) = 'g';
	*(scancode + 35) = 'h';
	*(scancode + 36) = 'j';
	*(scancode + 37) = 'k';
	*(scancode + 38) = 'l';
	*(scancode + 39) = ';';
	*(scancode + 40) = '\'';
	*(scancode + 41) = '`';
	*(scancode + 43) = '\\';
	*(scancode + 44) = 'z';
	*(scancode + 45) = 'x';
	*(scancode + 46) = 'c';
	*(scancode + 47) = 'v';
	*(scancode + 48) = 'b';
	*(scancode + 49) = 'n';
	*(scancode + 50) = 'm';
	*(scancode + 51) = ',';
	*(scancode + 52) = '.';
	*(scancode + 53) = '/';
	*(scancode + 56) = 0;
	//59-68 are F-keys, map to 0
	for(int i=59;i<79;i++){
		*(scancode + i) = 0;
	}
	*(scancode + 57) = ' ';
	*(scancode + 72) = 0;
	*(scancode + 75) = 0;
	*(scancode + 77) = 0;
	*(scancode + 91) = 0;
	*(scancode + 80) = 0;
	//Release keys should map to nothing
	for(int i=130;i<189;i++){
		*(scancode + i) = 0;
	}
	
	
}


char shiftSpecialChars(char lower){
	char toReturn;
	//Handle special characters
	switch(lower){
	//Keep null chars null
	case 0: toReturn = 0;break;
	//Delete
	case 16: toReturn = 16;break;
	case '1': toReturn = '!';break;
	case '2': toReturn = '@';break;
	case '3': toReturn = '#';break;
	case '4': toReturn = '$';break;
	case '5': toReturn = '%';break;
	case '6': toReturn = '^';break;
	case '7': toReturn = '&';break;
	case '8': toReturn = '*';break;
	case '9': toReturn = '(';break;
	case '0': toReturn = ')';break;
	case '-': toReturn = '_';break;
	case '=': toReturn = '+';break;
	case '`': toReturn = '~';break;
	case '[': toReturn = '{';break;
	case ']': toReturn = '}';break;
	case '\\': toReturn = '|';break;
	case ';': toReturn = ':';break;
	case '\'': toReturn = '"';break;
	case ',': toReturn = '<';break;
	case '.': toReturn = '>';break;
	case '/': toReturn = '?';break;
	case '\n': toReturn = '\n';break;
	default: toReturn = lower -32;
	}
	return toReturn;
}


//Setup the keyboard driver
void initialize(){
	if(!keyboard_test()){
		println("Unable to contact keyboard");
		halt_acf();
	}	
	init_scantable();
	shifted = false;
	canUpdateShift = true;
}


char getChar(int code){
	char pressed = *(scancode + code);
	if(code==42||code==54||code==0){
		return 0;
	}
	if(shifted){
		pressed = shiftSpecialChars(pressed);
	}
	return pressed;
}

int getCtrl(){
	return ctrl;
}

int getAlt(){
	return alt;
}

int getSup(){
	return sup;
}

char getScancode()
{
int c=0;
do {
if(port_byte_in(0x60)!=c)
{
c=port_byte_in(0x60);
//Shift up
if(c==42||c==54){
	shifted = true;
}
//Shift down
if(c==170||c==182){
	shifted = false;
}

//CTRL up
if(c==29){
	ctrl = true;
}
if(c==199){
	ctrl = false;
}

//ALT
if(c==56){
	alt = true;
}
if(c==184){
	alt = false;
}

//SUPER
if(c==91){
	sup = true;
}
if(c==219){
	sup = false;
}

return c;
}
}while(1);
}
