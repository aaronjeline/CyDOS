#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
//Attribute byte for out default color scheme
#define WHITE_ON_BLACK 0x0f
#define WHITE_ON_BLACK_BLINK 0xf1

//Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5


void print_char(char character, int col, int row, char attribute_byte);

int get_screen_offset(int col, int row);

int get_cursor();

void set_cursor(int offset);

void update_cursor();

void print_at(char* message, int col, int row);

void print(char* message);

void println(char *message);

void clear_screen();

int handle_scrolling(int cursor_offset);

void setVideoPort(int port);

void backspace();

void nudgeCursor(int amnt);

void printHeader(char *text);
void unsetHeader();
void fillLine(char c);
