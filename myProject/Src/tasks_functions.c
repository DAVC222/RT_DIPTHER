
#include <cars_functions.h>
#include "queu_func.h"
#include "main_myproject.h"
#include "tasks_functions.h"
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// externs busy structs
extern busy_police_cars_t busy_police_cars;
extern busy_fire_cars_t busy_fire_cars;
extern busy_ambulance_cars_t busy_ambulance_cars;
extern busy_corona_cars_t busy_corona_cars;

// externstask handlers
extern QueueHandle_t xQueue_dspcher;
extern QueueHandle_t xQueue_police;
extern QueueHandle_t xQueue_fire;
extern QueueHandle_t xQueue_ambulance;
extern QueueHandle_t xQueue_corona;
// declare mutex semafor
extern SemaphoreHandle_t xMutex;
// por type str
char selected_call_type_str[15] = "";
//extern var
extern int call_id;

// Task dispther
void Task_dispcher(void *pvParameters)

{
     // call msg struct
     call_msg_t call_msg;
    // Pointer to store the chosen queue
    QueueHandle_t selected_queue = NULL;
    // to store call type
    uint8_t selected_call_type_num = 0;
   
    int call_type = 0;
    uint8_t available_car = NO_CAR_AVAILABLE;

    //  TaskHandle_t holder = xSemaphoreGetMutexHolder(xMutex);

    for (;;)
    {

        if (xSemaphoreTake(xMutex, TASKS_SMFR_DELAY) == pdTRUE)

        {
            printf("distcher\n");
            // check if there is call watting
            if (xQueuePeek(xQueue_dspcher, &call_msg, TASKS_RCVQUE_DELAY) == pdPASS)
            {
                printf(" disptcher %s", call_msg.call_desc);

                 strcpy(call_msg.call_desc, " ");

                printf(" after delete %s\n", call_msg.call_desc);
                call_type = call_msg.call_type;
                call_type = 0;
                printf(" call from task disptcher struct   %d\n", call_msg.call_type);  // debug only
                printf(" call id from task disptcher struct   %d\n", call_msg.call_id); // debug only
                // selected_queue = xQueue_police;
                switch (call_type)
                {
                case police:

                    available_car = check_police_cars_busy(&busy_police_cars);

                    if (available_car != NO_CAR_AVAILABLE)
                    {
                        selected_queue = xQueue_police;
                        strcpy(selected_call_type_str, "Police");
                        break;
                    }
                    else
                    {
                        available_car = check_ambulance_cars_busy(&busy_ambulance_cars);
                    }

                    if (available_car != NO_CAR_AVAILABLE)
                    {

                        selected_queue = xQueue_ambulance;
                        strcpy(selected_call_type_str, "Ambulance");
                        break;
                    }
                    else
                    {
                        available_car = check_corona_cars_busy(&busy_corona_cars);
                    }

                    if (available_car != NO_CAR_AVAILABLE)
                    {

                        selected_queue = xQueue_corona;
                        strcpy(selected_call_type_str, "Corona");
                        break;
                    }

                default:

                    printf("from case default %d \n", call_msg.call_type);
                }

                if (selected_queue != NULL)
                {

                    call_msg.call_id = call_id;
                    snprintf(call_msg.call_desc, sizeof(call_msg.call_desc), " >> Assign call number %d for %s  %d \n", call_msg.call_id, selected_call_type_str, available_car);
                    RED_TXT_CLR;
                    printf("Dispther recievd call number %d\n", call_msg.call_id);
                    RST_TXT_CLR;

                    if (xQueueSendToBack(selected_queue, &call_msg, TASKS_SNDQUE_DELAY) != pdPASS)
                    {
                        my_assert(false, "failed to send call to  queue\n");
                    }

                   
                    available_car = NO_CAR_AVAILABLE;
                    // clear the current queue
                    selected_queue = NULL;
                    // print dispacher messages
                    RED_TXT_CLR;
                    printf("%s", call_msg.call_desc);
                    //  write_call_time_to_log(LOG_FILE_NAME);
                   // write_call_details_to_log(LOG_FILE_NAME, call_msg.call_desc);
                    printf(" call_msg.call_desc\n"); // debug only
                    RST_TXT_CLR;
                    // Remove the call from dispatcher queue only if successfully assigned
                    if (xQueueReceive(xQueue_dspcher, &call_msg, 5) != pdPASS)
                    {
                        printf("Failed to remove last call from dispatcher queue\n");
                    }
                     printf("pass_2\n");
                    // break;
                }

                else
                {
                    printf(" queue is null");
                }
            }
        }
        else

        {

            printf("failed to get mutex for Disptcher\n"); // debug only
        }
        // Remove the call from dispatcher queue only if successfully assigned
        // if (xQueueReceive(xQueue_dspcher, &call_msg, TASKS_RCVQUE_DELAY) != pdPASS)
        // {
        //     printf("Failed to remove last call from dispatcher queue\n");
        // }
        // Release the mutex
        xSemaphoreGive(xMutex);
        //  delay
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/*---------------------------------------------------------Police Task-----------------------*/
// Task police
void Task_police(void *pvParameters)
{

    call_msg_t msg_police;
    for (;;)
    {

        printf("Task police  is using the shared resource\n"); // debug only
        if (xSemaphoreTake(xMutex, TASKS_SMFR_DELAY) == pdTRUE)
        {

            uint8_t available_car = check_police_cars_busy(&busy_police_cars);

            // if (available_car != NO_CAR_AVAILABLE)

            switch (available_car)
            {

            case NO_CAR_AVAILABLE:
                printf("all police cars occupied\n");

                printf("%d", call_id);
                // delay
                //  vTaskDelay(pdMS_TO_TICKS(100));
                break;

            case CAR_1:
            case CAR_2:
            case CAR_3:
                if (xQueueReceive(xQueue_police, &msg_police, TASKS_RCVQUE_DELAY) == pdPASS)
                {
                    const char *car_name = get_police_car_name(available_car);
                    set_reset_police_car_busy(&busy_police_cars, available_car, true);
                    BLUE_TXT_CLR;
                    printf("%s  handle call- %d\n", car_name, msg_police.call_id);
                    RST_TXT_CLR;
                    // break;
                }
                else
                {
                    printf("There are no calls for police\n"); // debug only
                    break;
                }
            }

            // Release the mutex
            xSemaphoreGive(xMutex);
        }
        else
        {

            RST_TXT_CLR;
            printf("failed to get mutex for Task_police\n"); // debug only
        }

        // delay
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/*-------------------------------------------------------------Fire Task----------------------*/
// Task fire
void Task_fire(void *pvParameters)
{

    call_msg_t msg_fire;
    for (;;)
    {
        //  printf("Task fire is using the shared resource mutex\n"); // debug only
        if (xSemaphoreTake(xMutex, TASKS_SMFR_DELAY) == pdTRUE)
        {
            printf("Task fire 1 is using mutex\n"); // debug only
            // check for calls

            if (xQueueReceive(xQueue_fire, &msg_fire, TASKS_RCVQUE_DELAY) != pdPASS)
            {
                // printf("There is no calls for fire\n");// debug only
            }
            else
            {
                // busy.fire_1 = true; // set busy flage
                YLW_TXT_CLR;
                printf("Fire 1 handle call - %d\n", msg_fire.call_id);
                RST_TXT_CLR;
            }

            // printf("release mutex fire 1\n");// debug only

            // Release the mutex
            xSemaphoreGive(xMutex);
            // some delay
            vTaskDelay(pdMS_TO_TICKS(TASKS_DELAY));
            // busy.fire_1 = false;
            // printf("fire 1 task\n");// debug only
        }
        else
        {

            printf("failed to get mutex for Task_fire_1\n"); // debug only
        }
    }
}

/* -----------------------------------------------------Ambulance Task------------------*/
// Task ambulance
void Task_ambulance(void *pvParameters)
{

    call_msg_t msg_ambulance;
    for (;;)
    {
        // printf("Task ambulance 1 is using the shared resource mutex\n");// debug only
        if (xSemaphoreTake(xMutex, TASKS_SMFR_DELAY) == pdTRUE)
        {
            printf("Task ambulance  is using mutex\n"); // debug only
            //  check for calls

            if (xQueueReceive(xQueue_ambulance, &msg_ambulance, TASKS_RCVQUE_DELAY) != pdPASS)
            {
                // printf("There is no calls for ambulance\n");// debug only
            }
            else
            {
                // busy.ambulance_1 = true; // set busy flage
                GRN_TXT_CLR;
                printf("Ambulance 1 handle call- %d\n", msg_ambulance.call_id);
                RST_TXT_CLR;
            }

            // printf("release mutex Ambulance 1\n");// debug only

            // Release the mutex
            xSemaphoreGive(xMutex);
            // some delay
            vTaskDelay(pdMS_TO_TICKS(TASKS_DELAY));
            // busy.ambulance_1 = false;
            //  printf("ambulance  1 task\n");// debug only
        }
        else
        {

            //  printf("failed to get mutex for Task_ambulance_1\n");// debug only
        }
    }
}
