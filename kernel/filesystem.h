struct File{
	char *start;
	int length;
	char name;
	char type;
};

struct Directory{
	struct File *listing;
	int length;
};


void createTextFile(char name, char *buffer, int size);
struct File* getListing();
int getLength();
