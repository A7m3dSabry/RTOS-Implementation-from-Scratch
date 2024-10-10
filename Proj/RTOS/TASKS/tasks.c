#include "tasks.h"



/**
 * @brief Lists That Holds the Ready Tasks. Each Priority Has its own list
 */
static List_t pxReadyLists[configMAX_PRIORITIES] = {0};


/**
 * @brief Holds The Current Running Task
 */
TaskTCB_t *pxCurrentTCB = NULL;

/**
 * @brief Responsible for Suspending The Scheduler or enabling it, also it supports nesting
 */
static volatile UBaseType_t uxSchedulerSuspended = ( UBaseType_t ) 0U;

/**
 * @brief Holds How Many Ticks Happend Since the start of the Scheduller
 */
StackType_t xTick ;




/**
 * @brief a function to handle which task will be executed next. there must be at least one task in the ready tasks
 */

void vTaskSwitchContext(void){

    if (uxSchedulerSuspended != 0) {
        /* Scheduler is Disabled */
        return;
    } else {

        /* Find Highest Ready Task */
        for (int32_t priority = configMAX_PRIORITIES -1; priority >= 0 ; priority--){
                if (listGET_LIST_LENGTH(&pxReadyLists[priority]) != 0){
                    pxCurrentTCB = (TaskTCB_t *)pxReadyLists[priority].pxIndexItem->pvValue;

                    pxReadyLists[priority].pxIndexItem = pxReadyLists[priority].pxIndexItem->pxNext;
                    break;
                }
        }

    }

}

/**
 * @brief Responsible for Managing How to Add The New Task
 * @param handle : handle of the new task
 */
static void vTaskAddNewTask(TaskHandle_t handle){
		vListInsert(&pxReadyLists[((TaskTCB_t *)handle)->uiBasePriority], &((TaskTCB_t *)handle)->xStateListItem);
}

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
Std_ReturnType xTasksCreate(TaskFunction_t pvTaskCode,
                           const char *pcName,
                           uint16_t usStackSize,
                           uint32_t uiPriority,
                           void *pvParameters,
                           TaskHandle_t *pxTaskHandle){



    Std_ReturnType ret = E_OK;
    /* Disable Interrupt Since This is Critical Section */
    taskENTER_CRITICL();
    TaskTCB_t *pxTCB = NULL;


    /* Allocate Memory for TCB */
    pxTCB = pvPortMalloc(sizeof(TaskTCB_t));

    if (NULL == pxTCB){
        ret = E_NOT_OK;
    } else {

        /* Initialize TCB */
        for (uint32_t uiI = 0 ; uiI < sizeof(TaskTCB_t) ; uiI++){
            *(((uint8_t*)pxTCB) + uiI) = 0x00;
        }
        /* Allocate Stack */
        pxTCB->pxStackBase = pvPortMalloc(sizeof(StackType_t) * usStackSize);

        /* Check if Stack is Allocated */
        if (NULL == pxTCB->pxStackBase){
            /* Free allocated Memory Since Couldn't Allocate for Stack */
            vPortFree(pxTCB);
            pxTaskHandle = NULL;
            ret = E_NOT_OK;

        } else {
            /* Init xStateListItem */
            vListInitialiseItem(&pxTCB->xStateListItem);
            pxTCB->xStateListItem.pvValue = (void *) pxTCB;

            /* Initialize TCB Items */
            pxTCB->uiBasePriority = uiPriority;
            pxTCB->uiCurrentPriority = uiPriority;
            for ( int i = 0 ; i < usStackSize ; i++){
            	pxTCB->pxStackBase[i] = 0;
            }
            /* Initialize StackPointer */
            /* the -16 is due to the first saved status of the task. in other words we created the first save of the
             * task where it only contains the PC and the PSR of The Task */
            pxTCB->pxStackPointer = pxTCB->pxStackBase + usStackSize - 16;

            /* Configuring PSR to be default and in Thump State */
            *(pxTCB->pxStackBase + usStackSize -1) = (StackType_t)(1<<24);

            /* Configuring PC of the stack to Point to the given function code */
            *(pxTCB->pxStackBase + usStackSize -2) = (StackType_t) pvTaskCode;

            /* Passing Parameters to The function */
            *(pxTCB->pxStackBase + usStackSize -8) = (StackType_t) pvParameters;

            if (NULL != pxTaskHandle){
                *pxTaskHandle = (TaskHandle_t) pxTCB;
            }


            for (uint32_t i = 0 ; i < configMAX_NAME_LEN ; i++){
            	pxTCB->pcName[i] = pcName[i];
            	if(0 == pcName[i]){
            		break;
            	}
            }
            pxTCB->pcName[configMAX_NAME_LEN -1] = 0;

            vTaskAddNewTask((TaskHandle_t) pxTCB);


        }


    }


    taskEXIT_CRITICAL();
    return ret;


}


/**
 * @brief This function release the CPU and allow other tasks to work until the delay end
 *          the task will enter the blocked state
 * @param xTicksCount number of ticks to be waited
 */
void vTaskDelay(TickType_t xTicksCount){

}



/**
 * @brief void to start scheduling available tasks
 */
void vTaskStartScheduler(void){

    /* TODO: Add Idle Task Implementation */

    /* Initialize Ticks Value */
    xTick = ( TickType_t ) configINITIAL_TICK_COUNT;
    /* Start Scheduler */
    xPortStartScheduler();


}




static void prvAddTaskToReadyList(TaskHandle_t handle){
    /* TODO: FreeRTOS implementation used listInsertToEnd to make the task is the last one in its priority lists what is the differences than inserting it to it's correct place ? since they should be ordered in priority based */

    vListInsert(&pxReadyLists[((TaskTCB_t*) handle)->uiBasePriority], &(((TaskTCB_t *)handle)->xStateListItem));
}



/**
 * @brief Used to Remove Tasks From Waiting Specific Queue
 * @param pxEventList list of waiting tasks
 */
BaseType_t xTaskRemoveFromEventList( const List_t * const pxEventList ) {

    BaseType_t xReturn = pdPASS;

    /* The Event List is Ordered by Priority so the first item is The Highest Priority */
    TaskTCB_t * pxUnblockedTCB = listGET_ITEM_OBJECT_OF_HEAD_ENTRY(pxEventList);

    vListRemoveItem(&(pxUnblockedTCB->xEventItemList));

    if (pdFALSE == uxSchedulerSuspended) {
        /* Remove from Blocked List */
        vListRemoveItem(&(pxUnblockedTCB->xStateListItem));
        /* Add to Ready Lists */
        prvAddTaskToReadyList((TaskHandle_t )pxUnblockedTCB);

    } else {
        /* TODO: Handle When Scheduler is Disabled using PendingReadyList */
    }

    /* Preempt if Unblocked Task Has Higher Priority Than The Current Running One */
    if (pxUnblockedTCB->uiCurrentPriority > pxCurrentTCB->uiCurrentPriority){
        /* TODO: Handle not Yielding Directly but raise a flag instead to handle being called from ISR*/
        vTaskYieldScheduler();
    }



    return xReturn;

}

TickType_t xTaskGetTickCount(){
    return xTick;
}


void vTaskSuspendAll(){
    uxSchedulerSuspended++;
}

UBaseType_t xTaskResumeAll(){
    uxSchedulerSuspended--;
    return pdFALSE;
}
