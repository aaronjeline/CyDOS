#include "util.h"
//http://bos.asmhackers.net/docs/floppy/docs/floppy_tutorial.txt


#define DISK_PARAMETER_ADDRESS 0x000fefc7

typedef struct{
	unsigned char steprate_headunload;
	unsigned char headload_ndma;
	unsigned char motor_delay_off;//Specified in clock ticks
	unsigned char bytes_per_sector;
	unsigned char sectors_per_track;
	unsigned char gap_length;
	unsigned char data_length;//Used only when bytes per sector == 0
	unsigned char format_gat_length;
	unsigned char filler;
	unsigned char head_settle_time;//milliseconds
	unsigned char motor_start_time;//1/8 seconds
}__attribute__((packed)) floppy_parameters;


#define FLOPPY_PRIMARY_BASE 0x03f0
#define FLOPPY_SECONDARY_BASE 0x0370

#define STATUS_REG_A 0x0000 //PS2
#define STATUS_REG_B 0x0001 //PS2
#define DIGITAL_OUTPUT_REG 0x0002
#define MAIN_STATUS_REG 0x0003
#define DATA_RATE_SELECT_REG 0x0004 //PS2
#define DATA_REG 0x0005
#define DIGITAL_INPUT_REG 0x0006 //AT
#define CONFIG_CONTROL_REG 0x0007 //AT
#define PRIMARY_RESULT_STATUS 0x0000
#define STATUS_REG_A 0x0000


/*Controller Commands*/
#define FIX_DRIVE_DATA 0x03
#define CHECK_DRIVE_STATUS 0x03
#define CALIBRATE_DRIVE 0x03
#define CHECK_INTERRUPT_STATUS 0x03
#define FORMAT_TRACK 0x03
#define READ_SECTOR 0x03
#define READ_DELETE_SECTOR 0x03
#define FIX_DRIVE_DATA 0x03
#define FIX_DRIVE_DATA 0x03
#define FIX_DRIVE_DATA 0x03
#define FIX_DRIVE_DATA 0x03
#define FIX_DRIVE_DATA 0x03
