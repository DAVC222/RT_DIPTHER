// #include "tasks_functions.h"
#include "main_myproject.h"
#include "queu_func.h"

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <stdio.h>
#include <queue.h>

#include <stdbool.h>
QueueHandle_t xQueue_dspcher;
QueueHandle_t xQueue_police;
QueueHandle_t xQueue_fire;
QueueHandle_t xQueue_ambulance;
QueueHandle_t xQueue_corona;


void create_queus(void)
{

    xQueue_dspcher = xQueueCreate(QUEUE_LENGTH, QUEUE_SIZE);

    if (xQueue_dspcher == NULL)
    {

        my_assert(false, "failed to create dispcher queue");
    }

    xQueue_police = xQueueCreate(QUEUE_LENGTH, QUEUE_SIZE);

    if (xQueue_police == NULL)
    {

        my_assert(false, "failed to create police queue");
    }

    xQueue_fire = xQueueCreate(QUEUE_LENGTH, QUEUE_SIZE);

    if (xQueue_police == NULL)
    {

        my_assert(false, "failed to create fire queue");
    }

    xQueue_ambulance = xQueueCreate(QUEUE_LENGTH, QUEUE_SIZE);

    if (xQueue_ambulance == NULL)
    {

        my_assert(false, "failed to create ambulance queue");
    }

    xQueue_corona = xQueueCreate(QUEUE_LENGTH, QUEUE_SIZE);

    if (xQueue_corona == NULL)
    {

        my_assert(false, "failed to create corona queue");
    }

    
}


