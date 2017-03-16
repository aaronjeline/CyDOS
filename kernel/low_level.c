unsigned char port_byte_in(unsigned short port) {
	//C wrapper that the reads a byte from specified port
	unsigned char result;
	__asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
	return result;
}

void port_byte_out(unsigned short port, unsigned char data){
	//Writes specified data out to specified port
	__asm__("out %%al, %%dx" : :"a" (data), "d" (port));
}


unsigned char port_word_in(unsigned short port) {
	//C wrapper that the reads a word from specified port
	unsigned char result;
	__asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
	return result;
}


void port_word_out(unsigned short port, unsigned char data){
	//Writes specified data out to specified port
	__asm__("out %%ax, %%dx" : :"a" (data), "d" (port));
}

