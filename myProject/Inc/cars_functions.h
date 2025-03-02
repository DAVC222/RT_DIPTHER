#ifndef CARS_FUNCTIONS_H
#define CARS_FUNCTIONS_H

//#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//#define NO_CAR_AVALBL   (int)99
#define BUSY 1
#define AVAILABLE 0
#define NO_CAR_AVAILABLE 99


#define CAR_1    0
#define CAR_2    1
#define CAR_3    2
#define CAR_4    3

typedef struct
{
   uint8_t police_1;
   uint8_t police_2;
   uint8_t police_3;
} busy_police_cars_t;

typedef struct
{
   uint8_t fire_1;
   uint8_t fire_2;

} busy_fire_cars_t;

typedef struct

{

   uint8_t ambulance_1;
   uint8_t ambulance_2;
   uint8_t ambulance_3;
   uint8_t ambulance_4;

} busy_ambulance_cars_t;


typedef struct

{

   uint8_t corona_1;
   uint8_t corona_2;
   uint8_t corona_3;
   uint8_t corona_4;

} busy_corona_cars_t;



// Police
uint8_t check_police_cars_busy(busy_police_cars_t *cars);
const char *get_police_car_name(uint8_t car_num);
void set_reset_police_car_busy(busy_police_cars_t *cars, uint8_t car_num, bool state);
// Ambulance
uint8_t check_ambulance_cars_busy(busy_ambulance_cars_t *cars);
const char *get_ambulance_car_name(int car_num);
void set_reset_ambulance_car_busy(busy_ambulance_cars_t *cars, uint8_t car_num, bool state);
// Fire
uint8_t check_fire_cars_busy(busy_fire_cars_t *cars);
void set_reset_fire_car_busy(busy_fire_cars_t *cars, uint8_t car_num, bool state);
const char *get_fire_car_name(uint8_t car_num);
// Corona
uint8_t check_corona_cars_busy(busy_corona_cars_t *cars);
void set_reset_corona_car_busy(busy_corona_cars_t *cars, uint8_t car_num, bool state);
const char *get_corona_car_name(uint8_t car_num);













#endif