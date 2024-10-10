

#include "list.h"



/***************************/
/*         Items APIs      */
/***************************/


void vListInitialiseItem(ListItem_t * const pxItem){
    pxItem->pxPrevious = NULL;
    pxItem->pxNext = NULL;
    pxItem->pvValue = NULL;
    pxItem->xItemValue = (TickType_t) portMAX_DELAY;
}



void vListRemoveItem(ListItem_t *const pxItem){

    /* Getting the Item Container */
    List_t * const pxList = pxItem->pxContainer;
    /* Handling One Item in the list */
    if (pxList->uxNumberOfItems == 1){
        pxList->pxIndexItem = NULL;
        pxList->pxEndItem = NULL;
        pxList->uxNumberOfItems = 0;
    } else {

        /* Removing Item */
        pxItem->pxNext->pxPrevious = pxItem->pxPrevious;
        pxItem->pxPrevious->pxNext=pxItem->pxNext;

        /* Index should point to valid item */
        if (pxList->pxIndexItem == pxItem) {
            pxList->pxIndexItem = pxList->pxIndexItem->pxPrevious;
        }
        /* de attach the container form the item */
        pxItem->pxContainer = NULL;
        pxList->uxNumberOfItems--;
    }



}

/***************************/
/*         List APIs       */
/***************************/

void vListInitialise(List_t * const pxList){
    /* The Function Will Not check for pxList if Null or Not to Provide Performance */
    pxList->pxEndItem = NULL;
    pxList->pxIndexItem = NULL;
    pxList->uxNumberOfItems = 0;
}

void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem){

    if (0 == listGET_LIST_LENGTH(pxList)) {
        /* Add First Element */

        /* Make The Element Point to ItSelf to Form Circular List */
        pxNewListItem->pxNext = pxNewListItem;
        pxNewListItem->pxPrevious = pxNewListItem;

        pxNewListItem->pxContainer = pxList;

        pxList->pxEndItem = pxNewListItem;
        pxList->pxIndexItem = pxNewListItem;


//        /* Adding Second Element */
//        case 1:
//
//            /* Setting Pointers Withing New Element to the Element in the List */
//            pxNewListItem->pxPrevious = pxList->pxEndItem;
//            pxNewListItem->pxNext = pxList->pxEndItem;
//
//            /* Setting Container of The Element */
//            pxNewListItem->pxContainer = pxList;
//
//            /* Setting Pointers of The Old Element in the list */
//            pxList->pxEndItem->pxNext = pxNewListItem;
//            pxList->pxEndItem->pxPrevious = pxNewListItem;
//
//            /* New Item Should be Placed at The End */
//            if (pxList->pxEndItem->xItemValue <= pxNewListItem->xItemValue){
//                /* Setting New End Element */
//                pxList->pxEndItem = pxNewListItem;
//            }
//            break;

    } else {


            ListItem_t *pxIndex = listGET_HEAD_ITEM(pxList);

            /* Finding The Item in the list where the new item should be placed before */
            if (portMAX_DELAY == pxNewListItem->xItemValue){
                /* The Item Should Be Inserted in The End */
                pxIndex = pxList->pxEndItem->pxNext;
                pxList->pxEndItem = pxNewListItem;
            } else {
                /* Loop Through All Elements in the list to find where it should be placed */
                while ((pxIndex->xItemValue <= pxNewListItem->xItemValue)
                        || (pxIndex != pxList->pxEndItem) ){
                    /* Reached End Item */
                    pxIndex = pxIndex->pxNext;
                }
                if ((pxIndex == pxList->pxEndItem) && (pxIndex->xItemValue < pxList->pxEndItem->xItemValue)){
                    /* The Item Should Placed in The End */
                    pxIndex = pxIndex->pxNext;
                    pxList->pxEndItem = pxNewListItem;
                }
            }


            /* Setting Pointers Withing New Element to the Element in the List */
            pxNewListItem->pxPrevious = pxIndex->pxPrevious;
            pxNewListItem->pxNext = pxIndex;

            /* Setting Container of The Element */
            pxNewListItem->pxContainer = pxList;

            /* Setting Pointers of The Old Element in the list */
            pxIndex->pxPrevious->pxNext = pxNewListItem;
            pxIndex->pxPrevious = pxNewListItem;

    }
    /* Increase Number of Elements */
    pxList->uxNumberOfItems++;
}
//void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem){
//
////    ListItem_t * const pxIndex = pxList->pxIndex;
////
////    pxNewListItem->pxNext = pxIndex;
////    pxNewListItem->pxPrevious = pxIndex->pxPrevious;
////
////    pxIndex->pxPrevious->pxNext
//}

