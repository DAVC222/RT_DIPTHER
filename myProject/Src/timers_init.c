
#include <FreeRTOS.h>
#include <timers.h>
#include <stdio.h>
//  Timer period in milliseconds (5000ms = 5 sec)
#define TIMER_PERIOD_MS 5000

extern void handle_call_dsptch(void);
// Timer handlers
TimerHandle_t xDspthCallTimer;
TimerHandle_t xPoliceTimer;
TimerHandle_t xFireTimer;
TimerHandle_t xAmbulance;
void create_timers(void);
void timers_callBackFunction(TimerHandle_t xTimer);

void create_timers(void)
{

    xDspthCallTimer = xTimerCreate("dspch_timer", pdMS_TO_TICKS(TIMER_PERIOD_MS), pdTRUE, (void *)0, timers_callBackFunction);

    xPoliceTimer = xTimerCreate("Police_timer", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, timers_callBackFunction);

    xFireTimer = xTimerCreate("Fire_timer", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, timers_callBackFunction);

    xAmbulance = xTimerCreate("Ambulancetimer", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, timers_callBackFunction);

    if ((xDspthCallTimer == NULL) || (xPoliceTimer == NULL) || (xFireTimer == NULL) || (xAmbulance == NULL))
    {
        printf("Failed to create timers\n");
        return; // Exit if timer creation fails
    }
    // Start the timers
    if ((xTimerStart(xDspthCallTimer, 0) != pdPASS) ||
        (xTimerStart(xPoliceTimer, 0) != pdPASS) ||
        (xTimerStart(xFireTimer, 0) != pdPASS) ||
        (xTimerStart(xAmbulance, 0) != pdPASS))

    {

        // Timer could not be started
        printf("Timer start failed!\n");
        for (;;)
            ;
    }
}

void timers_callBackFunction(TimerHandle_t xTimer)
{

    if (xTimer == xDspthCallTimer)
    {

        printf("xDspthTimer expired!\n");
        handle_call_dsptch();
    }
}