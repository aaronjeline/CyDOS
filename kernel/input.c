#include "keyboard.h"
#include "screen.h"
#include "util.h"

void textField(char *message, char *buffer, int drawWindow){
        if(drawWindow){
                //Window stuff
        }
        if(message[0]!=0){
                print(message);
                print(": ");
        }
        int pos = 0;
        int gatheringLine = true;
        char last = getChar(getScancode());
        while(gatheringLine){
                char new = getChar(getScancode());
                if(new!=last){
                        if(new==16){
                        //DELETE
                        backspace();
                        pos--;
                        buffer[pos]=0;
                }else{ if(new=='\n'){ gatheringLine = false;
                                pos++;
                                buffer[pos] = '0';
                        }else if(new!=0){
                                print_char(new,-1,-1,0);
                                buffer[pos] = new;
                                pos++;
                        }
                }
                last = new;
        }}
}

int isNum(char c){
        char nums[] = {'1','2','3','4','5','6','7','8','9','0'};
        for(int i=0;i<11;i++){
                if(c==nums[i]){
                        return 1;
                }
        }
        return 0;
}

int numField(char *message, int bufferLen, int drawWindow){
        if(drawWindow){
                //Window
        }
        char buffer[bufferLen];
        print(message);
        print(": ");
        int pos = 0;
        int gatheringLine = true;
        char last = getChar(getScancode());
        while(gatheringLine){
                        char new = getChar(getScancode());
                        if(new!=last){
                                if(new==16){
                                        //Delete
                                        backspace();
                                        pos--;
                                        buffer[pos] = 0;
                                }else{
                                        if(new=='\n'){
                                                gatheringLine=false;
                                                pos++;
                                                buffer[pos]=0;
                                        }else if(new!=0 && isNum(new)){
                                                print_char(new,-1,-1,0);
                                                buffer[pos] = new;
                                                pos++;
                                }
                        }
                        last = new;
        }}
        return strToInt(buffer);
}

char charField(char *message, int drawWindow){
	if(drawWindow){
		//Window
	}
	print(message);
	print(": ");
	int gathering = true;
	char last = getChar(getScancode());
	char toReturn = 0;
	while(gathering){
		char new = getChar(getScancode());
		if(new!=last){
			if(new=='\n'){
				gathering = false;
			}else if(new!=0){
				print_char(new,-1,-1,0);
				backspace();
				toReturn = new;
			}
		}
		last = new;
	}
	return toReturn;
}

void textBuffer(char *line){
        int linePos = 0;
        int running = true;
        char last = getChar(getScancode());
        while(running){
                char new = getChar(getScancode());
		if(new!=last){
			if(new==16){
				//Delete key
				backspace();
				linePos--;
				line[linePos] = 0;
			}else{
				print_char(new,-1,-1,0);
				if(new!=0){
					line[linePos] = new;
					linePos++;
				}
			}
		}
		last = new;

                if(getCtrl()&&new=='c'){
                        running=false;
                }
        }
}

void preTextBuffer(char *text, char* buffer){
        println(text);
        textBuffer(buffer);
}

int yesNo(){
	print("(Y/N)?:");
	int done = false;
	int result;
	while(!done){
		switch(getChar(getScancode())){
			case 'Y':
			case 'y': result=true;done=true;break;
			case 'N':
			case 'n': result=false;done=true;break;
		}
	}
	return result;
}
	
void blockUntilKeypress(){
	char start = getChar(getScancode());
	while(getChar(getScancode())==start){
		//Nothing
	}
	while(getChar(getScancode())==0){
		//Nothing
	}	
}

int getSelected(char **options, int numOptions){
	/*
	for(int i=0;i<numOptions;i++){
		char option[4];
		print(intToStr(i,option));
		print(": ");
		print(options[i]);
		print("\n");
	}
	//Block until 0
	while(getScancode()!=0){
		//Block
	}
	int found = false;
	int result;
	while(!found){
		char new = getChar(getScancode());
		print(new);
		char str[1];
		str[0] = new;
		if(selection<=numOptions){
			found = true;
			result = selection;
		}
	}
	return found;
	*/
}



























