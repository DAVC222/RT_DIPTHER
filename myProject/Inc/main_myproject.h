



#ifndef MAIN_MYPROJECT_H
#define MAIN_MYPROJECT_H
#include <stdio.h>

#define LOG_FILE_NAME "log_file.txt" // Define the log file name

typedef enum
{
    police,
    ambulance,
    fire,
    corona
} call_types_e;


void write_call_time_to_log(const char *file_name);


extern const char *log_filename;
typedef unsigned char  uint8_t;
 char *get_time(char *time_buffer);

void writeToLog(FILE *filename, const char *message);
//extern const char formatted_message;
void write_call_details_to_log(const char * file_name,const char *desc);
#define  LOG_FIL_NAME       log.txt

#define TASKS_SMFR_DELAY 1000
#define TASKS_RCVQUE_DELAY 100
#define TASKS_SNDQUE_DELAY 100
#define TASKS_DELAY 3000

#define QUEUE_LENGTH  100

#define TASK_DSPTCR_PRI    2
#define TASK_PLC_PRI       1
#define TASK_FRE_PRI       1
#define TASK_AMBLNC_PRI    1

#define CALL_TYPE_NUM 4

#define RED_TXT_CLR printf("\033[1;31m") // Red text
#define BLUE_TXT_CLR printf("\033[1;34m") // Blue text
#define YLW_TXT_CLR printf("\033[1;33m") // yellow text
#define GRN_TXT_CLR printf("\033[1;32m") // green text


#define RST_TXT_CLR printf("\033[0m") // RESET COLOR TO DEFALT



#endif