
#ifndef PORTMACRO_H
#define PORTMACRO_H

/**************	Section: Includes ***************************/
#include "std_types.h"



/**************	Section: Macro Definitions Declarations *****/
#define portSTACK_TYPE uint32_t
#define portBASE_TYPE  short

/* The SYSTICK is 24 bit Counter */
#define portMAX_DELAY (TickType_t) ((1<<25)-1UL)


extern void vTaskEnterCritical( void );
extern void vTaskExitCritical( void );
#define taskENTER_CRITICL()         vPortEnterCritical()     /* can be changed by raising BASEPRI register value */
#define taskEXIT_CRITICAL()         vPortExitCritical()
/**************	Section: Macro Functions Declarations *******/



/**************	Section: Data Types Declarations ************/
typedef uint32_t TickType_t;
typedef portSTACK_TYPE StackType_t;
typedef portBASE_TYPE BaseType_t;
typedef unsigned portBASE_TYPE UBaseType_t;


/**************	Section: Methods Declarations  **************/




#endif //PORTMACRO_H
