
#include "queue.h"




QueueHandle_t xQueueGenericCreate(const UBaseType_t uxQueueLength,
                                  const UBaseType_t uxItemSize,
                                  const uint8_t ucQueueType)
{


    /* Pointer to Hold the New Queue Reference */
    Queue_t *pxNewQueue = NULL;
    uint32_t xQueueSizeInBytes;

    if ((uxQueueLength > 0)){
        /* TODO: Checks for Size of The Queue Should not overflow the uint32_t */
        xQueueSizeInBytes = uxQueueLength * uxItemSize;

        /* Allocate Memory for Queue Struct and The Queue Data */
        pxNewQueue = (Queue_t *) pvPortMalloc(sizeof(Queue_t) + xQueueSizeInBytes);

        /* Check if Allocation Succeeded */
        if (NULL != pxNewQueue){
            pxNewQueue->uxItemSize = uxItemSize;
            pxNewQueue->uxLength = uxQueueLength;

            /* When Item Size is 0 the Pointer of the head should point to the start of the struct */
            /* And cann't be Null. Because NULL is used to Differentiate Queue From Mutex */
            if (0 == uxItemSize){
                /* Queue with item size 0 */
                pxNewQueue->pcHead = (int8_t *) pxNewQueue;
            } else {
                /* pcHead Should point to the first byte in the array after the queue since it's used to hold the data */
                pxNewQueue->pcHead = (int8_t *) (pxNewQueue + 1);
            }
            xQueueGenericReset(pxNewQueue,pdTRUE);
        }
    }

    return pxNewQueue;
}



BaseType_t xQueueGenericReset( QueueHandle_t xQueue,
                               BaseType_t xNewQueue ) {


    BaseType_t xReturn = pdPASS;
    Queue_t  * const pxQueue = (Queue_t *)xQueue;

    if (NULL == pxQueue){
        xReturn = pdFAIL;
    } else {

        /* WriterCursors Should point to the first entry of the data */
        pxQueue->pcWriteCursor = pxQueue->pcHead;

        /* Tail of The Queue Should Point to The End of The Queue Data */
        pxQueue->u.xQueue.pcTail = pxQueue->pcHead + pxQueue->uxItemSize * pxQueue->uxLength;

        /* Even if It's semaphore the item size will be 0 */
        pxQueue->u.xQueue.pcReadCursor = pxQueue->u.xQueue.pcTail - pxQueue->uxItemSize;

        pxQueue->cRxLock = queueUNLOCKED;
        pxQueue->cTxLock = queueUNLOCKED;


        /* Init Other Params */
        pxQueue->uxMessagesWaiting = 0;

        if (pdFALSE == xNewQueue){
            if (xTaskRemoveFromEventList(&(pxQueue->xTasksWaitingToSend))) {
                /* TODO: Free RTOS Used Yield Here but we already yielded in the xTaskRemoveFromEventList */

            }
        } else {
            /* Init the Lists */
            vListInitialise(&(pxQueue->xTasksWaitingToSend));
            vListInitialise(&(pxQueue->xTasksWaitingToReceive));
        }

    }

    return xReturn;
}