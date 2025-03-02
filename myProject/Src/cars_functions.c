#include <cars_functions.h>
#include <stdbool.h>

// create busy strcuts
busy_police_cars_t    busy_police_cars = {0};
busy_fire_cars_t      busy_fire_cars = {0};
busy_ambulance_cars_t busy_ambulance_cars = {0};
busy_corona_cars_t    busy_corona_cars = {0};

/*=============================================================================================*/
// Police

uint8_t check_police_cars_busy(busy_police_cars_t *cars)
{

    if (cars->police_1 == AVAILABLE)
        return 0;

    if (cars->police_2 == AVAILABLE)
        return 1;

    if (cars->police_3 == AVAILABLE)
        return 2;

    return NO_CAR_AVAILABLE;
}

// Function
void set_reset_police_car_busy(busy_police_cars_t *cars, uint8_t car_num, bool state)
{

    switch (car_num)
    {

    case 0:
        cars->police_1 = state;
        break;

    case 1:
        cars->police_2 = state;
        break;

    case 2:
        cars->police_3 = state;
        break;
    }
}

const char *get_police_car_name(uint8_t car_num)

{

    switch (car_num)
    {

    case 0:
        return "Police 1";

    case 1:
        return "Police 2";

    case 2:
        return "Police 3";
    }
}

/*=============================================================================================*/
// Ambulance
uint8_t check_ambulance_cars_busy(busy_ambulance_cars_t *cars)
{

    if (cars->ambulance_1 == AVAILABLE)
        return 0;

    if (cars->ambulance_2 == AVAILABLE)
        return 1;

    if (cars->ambulance_3 == AVAILABLE)
        return 2;

    if (cars->ambulance_4 == AVAILABLE)
        return 2;

    return NO_CAR_AVAILABLE;
}


void set_reset_ambulance_car_busy(busy_ambulance_cars_t *cars, uint8_t car_num, bool state)
{

    switch (car_num)
    {

    case 0:
        cars->ambulance_1 = state;
        break;

    case 1:
        cars->ambulance_2 = state;
        break;

    case 2:
        cars->ambulance_3 = state;
        break;

    case 3:
        cars->ambulance_4 = state;
        break;
    }
}

const char *get_ambulance_car_name(int car_num)

{

    switch (car_num)
    {

    case 0:
        return "Ambulance 1";

    case 1:
        return "Ambulance 2";

    case 2:
        return "Ambulance 3";

    case 3:
        return "Ambulance 4";
    }
}

/*========================================================================= */
// Fire
uint8_t check_fire_cars_busy(busy_fire_cars_t *cars)
{

    if (cars->fire_1 == AVAILABLE)

        return 0;

    if (cars->fire_2 == AVAILABLE)

        return 1;

    return NO_CAR_AVAILABLE;
}

void set_reset_fire_car_busy(busy_fire_cars_t *cars, uint8_t car_num, bool state)
{

    switch (car_num)
    {

    case 0:
        cars->fire_1 = state;

        break;

    case 1:
        cars->fire_2 = state;

        break;
    }
}

const char *get_fire_car_name(uint8_t car_num)

{

    switch (car_num)
    {

    case 0:
        return "Fire 1";

    case 1:
        return "Fire 2";
    }
}


/*= == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == */
//Corona
uint8_t check_corona_cars_busy(busy_corona_cars_t *cars)
{

    if (cars->corona_1 == AVAILABLE)
        return 0;

    if (cars->corona_2 == AVAILABLE)
        return 1;

    if (cars->corona_3 == AVAILABLE)
        return 2;

    if (cars->corona_4 == AVAILABLE)
        return 3;

    return NO_CAR_AVAILABLE;
}


void set_reset_corona_car_busy(busy_corona_cars_t *cars, uint8_t car_num, bool state)
{

    switch (car_num)
    {

    case 0:
        cars->corona_1 = state;
        break;

    case 1:
        cars->corona_2 = state;
        break;

    case 2:
        cars->corona_3 = state;
        break;

    case 3:
        cars->corona_4 = state;
        break;
    }
}

const char *get_corona_car_name(uint8_t car_num)

{

    switch (car_num)
    {

    case 0:
        return "Corona 1";

    case 1:
        return "Corona 2";

    case 2:
        return "Corona 3";

    case 3:
        return "Corona 4";
    }
}