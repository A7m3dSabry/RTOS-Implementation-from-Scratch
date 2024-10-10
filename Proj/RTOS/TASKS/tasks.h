

#ifndef TASKS_H
#define TASKS_H






/**************	Section: Includes ***************************/
#include "rcc.h"
#include "heap.h"
#include "std_types.h"
#include "core_functions.h"
#include "projectDefines.h"
#include "port.h"
#include "RTOSConfig.h"
#include "list.h"
/**************	Section: Macro Definitions Declarations *****/




/**************	Section: Macro Functions Declarations *******/
/**
 * @brief Task Yield to force Scheduler to Serve Next Task
 */
#define vTaskYieldScheduler() vPortYield()

/**************	Section: Data Types Declarations ************/




typedef void(*TaskFunction_t)(void*) ;
typedef uint32_t *TaskHandle_t;

typedef enum {
    TaskStatus_Suspended =  (0),
    TaskStatus_Blocked =    (1),
    TaskStatus_Ready =      (2),
    TaskStatus_Running =    (3),
}TaskStatus_t;


typedef struct {
    StackType_t *pxStackPointer;
    StackType_t *pxStackBase;
    uint32_t uiTaskId;
    uint32_t uiBasePriority;
    uint32_t uiCurrentPriority;
    TaskStatus_t xStatus;
    uint32_t uiPeriod;
    ListItem_t xStateListItem;
    ListItem_t xEventItemList;      /* Used to Link Between Events list and the TCB */
    char pcName[configMAX_NAME_LEN];
} TaskTCB_t;


/**************	Section: Methods Declarations  **************/



/**
 * @brief Create a new Task with all its dependencies
 * @param pvTaskCode pointer to the task code
 * @param pcName name of the task and used for debugging purposes
 * @param usStackSize size of the stack in words
 * @param uiPriority base priority of the task
 * @param pvParameters parameters passed when calling the task for the first time
 * @param puiTaskHandle task handle for calling other apis
 * @return - E_OK means task created successfully
 *         - E_NOT_OK Task Failed to Create
 */
Std_ReturnType xTasksCreate(TaskFunction_t pvTaskCode, const char *pcName, uint16_t usStackSize, uint32_t uiPriority, void *pvParameters, TaskHandle_t *pxTaskHandle);

/**
 * @brief void to start scheduling available tasks
 */
void vTaskStartScheduler(void);


/**
 * @brief a function to handle which task will be executed next. there must be at least one task in the ready tasks
 */
void vTaskSwitchContext(void);

/**
 * @brief Used to Remove Tasks From Waiting Specific Queue
 * @param pxEventList list of waiting tasks
 */
BaseType_t xTaskRemoveFromEventList( const List_t * const pxEventList );


/**
 * @brief Void Disables Scheduler. Supports Nesting.
 */
void vTaskSuspendAll(void);

/**
 * @brief void enables Scheduler. Supports Nesting.
 * @return
 */
UBaseType_t  xTaskResumeAll(void);

/**
 * @brief Get Ticks Counted by Scheduler Since it Started
 * @return Ticks Count
 */
TickType_t xTaskGetTickCount(void);


#endif //TASKS_H
