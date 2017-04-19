struct File{
	char *start;
	int length;
	char name[10];
	char type[10];
};

struct Directory{
	struct File *listing;
	int length;
};


int createTextFile(char *name, char *buffer, int size);
struct File* getListing();
int getLength();
int getFileLength(char *name);
void getTextFile(char *name, char *buffer);
int deleteFile(char *name);
