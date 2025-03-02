#ifndef QUEU_FUNC_H
#define QUEU_FUNC_H

#include <stdbool.h>



#define QUEUE_SIZE     sizeof(call_msg_t)




typedef struct
{

    int call_id;
    int call_type;
    char call_desc[100];

} call_msg_t;




//void respond_to_call(int call_id, call_types_e type_call, (void *pvParameters);

void create_queus(void);
extern void my_assert(bool condition, const char *error_message);












#endif

