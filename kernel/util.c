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
