#include "main.h"


uint32_t counter1 = 0;
uint32_t counter2 = 0;
uint32_t counter3 = 1000000000;

void vTaskA(void *pvParameters){
    uint32_t *counter = (uint32_t*)pvParameters;
    while(1){
        for (uint32_t i = 0 ; i < 200 ; i++){}
        (*counter)++;
        vTaskYieldScheduler();
    }
}

void vTaskB(void *pvParameters){
    uint32_t *counter = (uint32_t*)pvParameters;
    while(1){
        for (uint32_t i = 0 ; i < 200 ; i++){}
        (*counter)++;
    }
}

//void vTaskC(void *pvParameters){
//    uint32_t *counter = (uint32_t*)pvParameters;
//    while(1){
//        for (uint32_t i = 0 ; i < 200 ; i++){}
//        (*counter)++;
//    }
//}

int main(){
    HAL_RCC_Init_DefaultConfigured();

    xTasksCreate(vTaskA,"Task1",100,15,&counter1,NULL);
    xTasksCreate(vTaskB,"Task2",100,15,&counter2,NULL);
    xTasksCreate(vTaskB,"Task3",100,15,&counter3,NULL);

    vTaskStartScheduler();

    while(1){}
}
