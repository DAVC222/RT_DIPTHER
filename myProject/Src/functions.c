#include <FreeRTOS.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <queue.h>
#include <string.h>
#include <stdint.h>
#include <semphr.h>
#include "main_myproject.h"
#include "queu_func.h"
extern SemaphoreHandle_t xMutex;
extern void my_assert(bool condition, const char *error_message);
extern QueueHandle_t xQueue_dspcher;

int call_id;

int generate_call_type(int call_types_num);
#define CALL_TYPE_NUM 4

void handle_call_dsptch(void)
{
    // if (xSemaphoreTake(xMutex, 100) == pdTRUE)
    // {

    int call_type_num = generate_call_type(CALL_TYPE_NUM);

    call_msg_t call_msg;
    printf("call type from gen  in function %d\n", call_type_num); // debug only

    strcpy(call_msg.call_desc, " ");
    call_msg.call_id = call_id;
    call_msg.call_type = call_type_num
        snprintf(call_msg.call_desc, sizeof(call_msg.call_desc), " >> Send  call number %d to dspther queue\n", call_id++);
    RED_TXT_CLR;
    printf("call number %d been recived\n", call_msg.call_id);
    RST_TXT_CLR;
    if (xQueueSendToBack(xQueue_dspcher, &call_msg, TASKS_SNDQUE_DELAY) != pdPASS)
    {
        my_assert(false, "failed to send call to dispther queue\n");
    }
    // }
    // Release the mutex
    // xSemaphoreGive(xMutex);
}

int generate_call_type(int call_types_num)
{

    int call_type = rand() % call_types_num;
    
    return call_type;
}