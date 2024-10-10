
#ifndef LIST_H
#define LIST_H







/**************	Section: Includes ***************************/
#include "RTOSConfig.h"
#include "std_types.h"
#include "portmacro.h"
#include "projectDefines.h"






/**************	Section: Data Types Declarations ************/
struct xList;

typedef struct xElement{
    volatile TickType_t xItemValue; /* works as a priority withing same priority items */
    struct xElement *pxNext;        /* Pointer tp Next item in The List */
    struct xElement *pxPrevious;    /* Pointer to Previous Item in The List */
    void * pvValue;                 /* Pointer to The Object this Element Holds */
    struct xList *pxContainer;            /* Making the Removing of the item from list Easy */ /* TODO: Add #if to remove it if the remove functionality not used */
} ListItem_t;

typedef struct xList{
    volatile UBaseType_t uxNumberOfItems;
    ListItem_t *pxIndexItem;
    ListItem_t *pxEndItem;
} List_t;
/**************	Section: Macro Definitions Declarations *****/

#define listGET_LIST_ITEM_VALUE(_pxListItem_)             ((_pxListItem_)->xItemValue)
#define listSET_LIST_ITEM_VALUE(_pxListItem_,_xValue_)     ((_pxListItem_)->xItemValue = (_xValue_))

#define listGET_NEXT(_pxListItem_)                        ((_pxListItem_)->pxNext)
#define listGET_PREV(_pxListItem_)                        ((_pxListItem_)->pxPrevious)

#define listIS_ITEM_IN_LIST(_pxList_, _pxListItem_)  (((_pxListItem_)->pxContainer == (_pxList_)) ? (pdTRUE) : (pdFALSE))

/// list

#define listGET_ITEM_VALUE_OF_HEAD_ENTRY(_pxList_)       (((_pxList_)->pxEndItem)->pxNext->xItemValue)

#define listGET_ITEM_OBJECT_OF_HEAD_ENTRY(_pxList_)       (((_pxList_)->pxEndItem)->pxNext->pvValue)

/* Return Head Item in The List */
#define listGET_HEAD_ITEM(_pxList_)                     (((_pxList_)->pxEndItem)->pxNext)

/* Set and Get End Item in The List */
/* Note This is not used to Insert Item to The End */
#define listGET_LIST_END_ITEM(_pxList_)                    ((_pxList_)->pxEndItem)
#define listSET_LIST_END_ITEM(_pxList_,_pxListItem_)         ((_pxList_)->pxEndItem = (_pxListItem_))

/* Get Curren Active Item */
#define listGET_ACTIVE_ELEMENT(_pxList_)                    ((_pxList_)->pxIndex)

/* Check if List has no items */
#define listIS_LIST_EMPTY(_pxList_)                       (((_pxList_)->uxNumberOfItems == (UBaseType_t) 0) ? pdTRUE : pdFALSE)
/* Return Length of List (number of items in it) */
#define listGET_LIST_LENGTH(_pxList_)                     ((_pxList_)->uxNumberOfItems)


#define listGET_LIST_FIRST_ITEM(_pxList_) ((_pxList_)->pxFirstItem)
#define listSET_LIST_FIRST_ITEM(_pxList_,_xElement_) ((_pxList_)->pxFirstItem = (_xElement_))

#define listGET_LIST_LAST_RETURNED_ITEM(_pxList_) ((_pxList_)->pxLastReturnedItem)
#define listGET_LIST_NUMBER_OF_ITEMS(_pxList_) ((_pxList_)->uxNumberOfItems)





/**************	Section: Macro Functions Declarations *******/

/**************	Section: Methods Declarations  **************/


/**
 * @brief function used to Initialize List Item
 * @param pxItem
 */
void vListInitialiseItem(ListItem_t * const pxItem);

/**
 * @brief function used to Initialize a List
 * @param pxList
 */
void vListInitialise(List_t * const pxList);
/**
 * @brief function used to insert new item based on the xItemValue (to make the list in order)
 * @param pxList        : list where the item will be inserted
 * @param pxNewListItem : the item to be inserted
 */
void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem);
/**
 * @brief function to remove item from it's list
 * @param pxItem : item to be removed
 */
void vListRemoveItem(ListItem_t *const pxItem);





#endif //LIST_H
