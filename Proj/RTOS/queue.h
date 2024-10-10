
#ifndef QUEUE_H
#define QUEUE_H
/**************	Section: Includes ***************************/
#include "RTOSConfig.h"
#include "list.h"
#include "tasks.h"

/**************	Section: Macro Definitions Declarations *****/



/**************	Section: Macro Functions Declarations *******/

#define queueUNLOCKED             ( ( int8_t ) -1 )
#define queueLOCKED_UNMODIFIED    ( ( int8_t ) 0 )
#define queueINT8_MAX             ( ( int8_t ) 127 )

/**************	Section: Data Types Declarations ************/


typedef struct {
    int8_t *pcTail;
    int8_t *pcReadCursor;
}QueuePointers_t;

typedef struct SemaphoreData
{
    TaskHandle_t xMutexHolder;        /* Owner of the Mutex */
    UBaseType_t uxRecursiveCallCount; /* Track number of 'Take' Call Called */
} SemaphoreData_t;


typedef struct {
    int8_t *pcHead;             /* Points to the Head of the Queue (first byte in it) */
    int8_t *pcWriteCursor;      /* Points to where we start writing to the queue */
    union {
      QueuePointers_t xQueue;           /* Needed for Queue Read Operations */
      SemaphoreData_t xSemaphore;       /* Needed for Semaphores Operations */
    }u;
    List_t xTasksWaitingToSend;         /* Priority Ordered List  */
    List_t xTasksWaitingToReceive;

    volatile UBaseType_t uxMessagesWaiting;
    UBaseType_t uxLength;
    UBaseType_t uxItemSize;

    volatile int8_t cRxLock;
    volatile int8_t cTxLock;





}Queue_t;


typedef Queue_t * QueueHandle_t;

/**************	Section: Methods Declarations  **************/


BaseType_t xQueueGenericReset(QueueHandle_t xQueue, BaseType_t xNewQueue);

QueueHandle_t xQueueGenericCreate(const UBaseType_t uxQueueLength,
                                  const UBaseType_t uxItemSize,
                                  const uint8_t ucQueueType);




#endif //QUEUE_H
