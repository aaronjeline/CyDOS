#include "screen.h"
#include "util.h"
#include "low_level.h"
int cursor = 0;
int basePort;
int dataPort;

void setVideoPort(int port){
	basePort = port;
	dataPort = basePort + 1;
}


/* Print a char on the screen at col, row, or at cursor position */
void print_char(char character, int col, int row, char attribute_byte) {
	/* Create a byte (char) pointer to the start of video memory */
	unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;

	/* If attribute is 0, assume default style */
	if (!attribute_byte) {
		attribute_byte = WHITE_ON_BLACK;
	}

	//Get video memory offset for screen location
	int offset;
	//If col & row are non-negative use them for offset
	//Otherwise use the cursor
	if(col >= 0 && row >= 0){
		offset = get_screen_offset(col, row);
	}else{
		offset = cursor;
	}

	/* If we see a newline character, set the offset to the end
	of the current row, so it will be advanced to the first col
	of the next row. Otherwise, write the character and its 
	attribute byte to video memory at our calculated offset. */ 

	if(character == '\n') {
		int rows = offset / (2*MAX_COLS);
		offset = get_screen_offset(79,rows);
	}else{
	vidmem[offset] = character;
	vidmem[offset+1] = attribute_byte;
	}

	/* Update the offset to the next character cell, which is
	two bytes ahead of the current cell */
	offset += 2;
	//Adjust for scrolling
	offset = handle_scrolling(offset);
	//Update cursor position on the screen device
	cursor = offset;
}

int get_screen_offset(int col, int row){
	return ((row * 80) + col)* 2;
}

int get_cursor(){
	port_byte_out(REG_SCREEN_CTRL, 14);
	int offset = port_byte_in(REG_SCREEN_DATA) << 8;
	port_byte_out(REG_SCREEN_CTRL, 15);
	offset += port_byte_in(REG_SCREEN_DATA);
	return offset*2;
}

void set_cursor(int offset){
	unsigned short position = offset/2;

	//cursor LOW prot to vga INDEX register
	port_byte_out(basePort, 0x0F);
	port_byte_out(dataPort, (unsigned char)(position&0xFF));
	port_byte_out(basePort, 0x0E);
	port_byte_out(dataPort, (unsigned char)((position>>8)&0xFF));
}
	

void update_cursor(){
	print_char(' ',-1,-1,WHITE_ON_BLACK_BLINK);
}


//Print a String @ specified coordinates
void print_at(char* message, int col, int row){
	//Update the cursor if col&row not negative
	if (col>=0 && row >= 0){
		cursor = ((row*80)+col)*2;
	}
	//Loop throught each char of the message
	int i = 0;
	while(message[i] != 0){
		print_char(message[i], col, row, WHITE_ON_BLACK);
		i++;
	}
}

//Print a String @ the cursor
void print(char* message){
	print_at(message, -1,-1);
	set_cursor(cursor);
}

void clear_screen(){
	int row = 0;
	int col = 0;

	/*Loop through video memory & write blank characters */
	for (row=0; row<MAX_ROWS; row++){
		for(col=0;col<MAX_COLS;col++){
			print_char(' ', col, row, WHITE_ON_BLACK);
		}
	}

	//Move the cursor to the top left
	cursor = 0;
}

int handle_scrolling(int cursor_offset) {

	//If we're within the screen, return
	if (cursor_offset < MAX_ROWS*MAX_COLS*2) {
		return cursor_offset;
	}

	/*Shuffle rows back*/
	int i;
	for(i=1;i<MAX_ROWS;i++){
		memory_copy(get_screen_offset(0,i) + VIDEO_ADDRESS, get_screen_offset(0,i-1) + VIDEO_ADDRESS, MAX_COLS * 2);
	}

	//Blank the last line
	char* last_line = get_screen_offset(0,MAX_ROWS-1) + VIDEO_ADDRESS;
	for(i=0;i<MAX_COLS*2;i++){
		last_line[i] = 0;
	}

	//Move the offset back one row
	cursor_offset -= 2*MAX_COLS;

	return cursor_offset;
}



