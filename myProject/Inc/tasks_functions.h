#ifndef TASKS_FUNCTIONS_H
#define TASKS_FUNCTIONS_H

#include "main_myproject.h"


//void dispcher(TimerHandle_t xTimer);

void Task_dispcher(void *pvParameters);
void Task_police(void *pvParameters);
void Task_fire(void *pvParameters);
void Task_ambulance(void *pvParameters);

#define CALL_INTRVL_DELAY 5000
#define CALL_TYPE_NUM 4


#endif