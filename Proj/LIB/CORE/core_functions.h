#ifndef CORE_FUNCTIONS_H
#define CORE_FUNCTIONS_H
/**************	Section: Includes ***************************/
#include "std_types.h"
/**************	Section: Macro Definitions Declarations *****/



/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/

#define CORE_FUNCTIONS_USE_C_IMPLEMENTATION


uint32_t __get_BASEPRI(void);
static inline void __set_BASEPRI(uint32_t priority);

uint32_t __get_PRIMASK(void);
static inline void __set_PRIMASK(uint32_t priority);

#ifdef CORE_FUNCTIONS_USE_C_IMPLEMENTATION
void __disable_irq();
void __enable_irq();



#else

#define __disable_irq() (__asm__ volatile ("CPSID i"))
#define __enable_irq() (__asm__ volatile ("CPSIE i"))

#endif //CORE_FUNCTIONS_USE_C_IMPLEMENTATION
/**************	Section: Methods Declarations  **************/
#endif //CORE_FUNCTIONS_H
