
#ifndef MAIN_H_
#define MAIN_H_

/**************	Section: Includes ***************************/
#include "stm32f103c8t.h"
#include "mcal_layer.h"
#include "std_types.h"
#include "delay.h"
//#include "esp8266.h"


#include "list.h"
#include "rtos.h"
/**************	Section: Includes ***************************/
/**************	Section: Macro Definitions Declarations *****/



/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/



/**************	Section: Methods Declarations  **************/




//void flash(){
//
//    int ret = 0;
//
//    initClock();
//
//    uint8_t data[] = "DEADDDA";
//    uint32_t size = sizeof(data);
//    HAL_FLASH_Unlock();
//
//    HAL_FLASH_ErasePageNumber(20,1);
//    /* Clean the error context */
//    HAL_FLASH_WriteProgram(0x8005000,data,9);
//    HAL_FLASH_Lock();
//}


#endif /* MAIN_H_ */




