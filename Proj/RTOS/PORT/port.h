
#ifndef PORT_H
#define PORT_H


/**************	Section: Includes ***************************/
#include "portmacro.h"
#include "tasks.h"
#include "stm32f103c8t.h"
/**************	Section: Macro Definitions Declarations *****/



/**************	Section: Macro Functions Declarations *******/


/**************	Section: Data Types Declarations ************/



/**************	Section: Methods Declarations  **************/
/**
 * @brief Void to Enter Critical Section and Keep Tracking of Nesting
 */
void vPortEnterCritical( void );


/**
 * @brief void to Exit Critical Section only when there is no Nesting Left
 */
void vPortExitCritical( void );

/**
 * @brief Setup Systick and Start First Task;
 */
//void xPortStartScheduler();
BaseType_t xPortStartScheduler(void);
/**
 * @brief void to yield tasks by triggering PendSV Interrupt
 */
void vPortYield();



#endif //PORT_H
