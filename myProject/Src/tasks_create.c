#include  "tasks_functions.h"
#include "main_myproject.h"
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <stdio.h>
#include <stdbool.h>


void create_tasks(void);
// handle errors function
extern void my_assert(bool condition, const char *error_message);



void create_tasks(void)
{
   //  Create dispcher tasks
    if (xTaskCreate(Task_dispcher, "Task dispcher", PTHREAD_STACK_MIN, NULL, TASK_DSPTCR_PRI , NULL) != pdPASS)
    {
        my_assert(false, "failed to create Task dispcher");
    }

    // Create polic tasks
    if (xTaskCreate(Task_police, "Task police", PTHREAD_STACK_MIN, NULL, TASK_PLC_PRI, NULL) != pdPASS)
    {
        my_assert(false, "failed to create Task police");
    }


  
    // Create fire task
    if (xTaskCreate(Task_fire, "Task fire", PTHREAD_STACK_MIN, NULL, TASK_FRE_PRI, NULL) != pdPASS)
    {
        my_assert(false, "failed to create Task fire ");
    }

   
   // Create ambulance task

    if (xTaskCreate(Task_ambulance, "Task ambulance", PTHREAD_STACK_MIN, NULL, TASK_AMBLNC_PRI , NULL) != pdPASS)
    {
        my_assert(false, "failed to create Task ambulance ");
    }

   
}