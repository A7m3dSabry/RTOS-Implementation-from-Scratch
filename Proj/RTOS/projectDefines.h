

#ifndef PROJECTDEFINES_H
#define PROJECTDEFINES_H

/**************	Section: Includes ***************************/
#include "RTOSConfig.h"
#include "portmacro.h"
/**************	Section: Macro Definitions Declarations *****/

#define pdFALSE     ((BaseType_t) 0 )
#define pdTRUE      ((BaseType_t) 1 )

#define pdPASS          (pdTRUE)
#define pdFAIL          (pdFALSE)

/**************	Section: Macro Functions Declarations *******/
/**
 * @brief Convert MilliSeconds into Ticks
 */
#define pdMS_TO_TICKS(_MS_) ((uint64_t)_MS_ * (uint64_t)configTICK_RATE_HZ/((uint64_t)1000))

/**
 * @brief Convert Ticks to MilliSeconds
 */
#define pdTICKS_TO_MS(_TICKS_) ((uint64_t)_TICKS_ * 1000 /((uint64_t configTICK_RATE_HZ)))

/**************	Section: Data Types Declarations ************/


/**************	Section: Methods Declarations  **************/


#endif //PROJECTDEFINES_H
