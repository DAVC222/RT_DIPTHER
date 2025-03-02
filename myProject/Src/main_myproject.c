#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <timers.h>
#include "tasks_functions.h"
#include "main_myproject.h"

char time_buffer[100];
char *time_buffer_p = &time_buffer[0];

extern void my_assert(bool condition, const char *error_message);
extern void create_tasks(void);
extern void create_queus(void);
// extern create_timers(void);
extern void timers_callBackFunction(TimerHandle_t xTimer);
// Declare a global mutex
SemaphoreHandle_t xMutex;

char formatted_message[100];
const char *log_filename = LOG_FILE_NAME;

int main_myproject(void)
{
    char formatted_message[100];
    printf("\033[2J\033[H"); // clear terminal
    // creat file if not exsist
    FILE *log_file = fopen(log_filename, "w"); // create and open file
    if (log_file == NULL)
    {

        my_assert(false, "failed opening log.txt");
    }

    // clear file if not empty
    writeToLog(log_file, " ");
    // close file
    if (fclose(log_file) != 0)
    {

        my_assert(false, "failed closing log.txt");
    }

    // open the file in appened mode
    log_file = fopen(log_filename, "a");
    if (log_file == NULL)
    {

        my_assert(false, "failed opening log.txt");
    }

    // store time in buffer and get pointer
    time_buffer_p = get_time(time_buffer);
    // write the header file >> date and time
    snprintf(formatted_message, sizeof(formatted_message), "Log file for 911 calls.created in :============ : %s============\n\n\n", time_buffer_p);
    writeToLog(log_file, formatted_message);
    fflush(log_file); //
    // set and start timers
    create_timers();  //
    // Create the mutex
    xMutex = xSemaphoreCreateMutex();

    if (xMutex == NULL)
    {
        my_assert(false, "failed to create mutex");
    }
    srand(time(NULL)); // init random function

    // create tasks
    create_tasks();
    // creates queus
     create_queus();
     // Start the scheduler

    TaskHandle_t holder = xSemaphoreGetMutexHolder(xMutex);
    if (holder == NULL)
    {
        printf("Mutex is currently free.\n");
    }
    vTaskStartScheduler();

    // If all went well, we should never reach here
    for (;;)
        ;
}

// file function

void writeToLog(FILE *filename, const char *message)
{
    fprintf(filename, "%s", message); // Write the message to the file
}

void write_call_time_to_log(const char *file_name)
{

    FILE *file = fopen(file_name, "a"); // Open the file in write mode

    // store time in buffer and get pointer
    time_buffer_p = get_time(time_buffer);
    // write the header file >> date and time

    // snprintf(formatted_message, sizeof(formatted_message), "Log file for 911 calls.created in :============ : %s============\n", time_buffer_p);
    writeToLog(file, time_buffer_p);
    fflush(file);
}

void write_call_details_to_log(const char *file_name, const char *desc)
{

    FILE *file = fopen(file_name, "a"); // Open the file in write mode

    // store time in buffer and get pointer
    //   time_buffer_p = get_time(time_buffer);
    // write the header file >> date and time

    // snprintf(formatted_message, sizeof(formatted_message), "Log file for 911 calls.created in :============ : %s============\n", time_buffer_p);
    writeToLog(file, desc);
    fflush(file);
}
//----------------------------------------------------------

char *get_time(char *time_buffer)
{

    time_t current_time;
    struct tm *local_time;
    char formatted_time[100]; // Buffer to store the formatted date/time string

    // Get current time
    current_time = time(NULL);
    if (current_time == (time_t)(-1))
    {
        my_assert(false, "failed to get time");
    }

    // Convert time_t to struct tm (local time)
    local_time = localtime(&current_time);

    // Format the time as a string
    strftime(time_buffer, sizeof(formatted_time), "%Y-%m-%d %H:%M:%S", local_time);

    // Print the formatted time
    // printf("Formatted local time: %s\n", formatted_time);

    return &time_buffer[0];
}
