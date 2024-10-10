#include "port.h"


/* TODO: Implement Via Assembly */
extern TaskTCB_t pxCurrentTCB;
extern TickType_t xTick;

/**
 * @brief Variable to Continue Tracking Critical Section Nesting and not Enabling Interrupts unless there is no nesting left
 *          this allow calling vPortEnterCritical multiple times safely
 */
UBaseType_t uxCriticalSectionNesting = 0;

/**
 * @brief Void to Enter Critical Section and Keep Tracking of Nesting
 */
void vPortEnterCritical( void ){
    __disable_irq();
    uxCriticalSectionNesting++;

}

/**
 * @brief void to Exit Critical Section only when there is no Nesting Left
 */
void vPortExitCritical( void ){
    uxCriticalSectionNesting--;
    if (0 == uxCriticalSectionNesting ) {
        __enable_irq();
    }
}


/* FREE RTOS names this xPortPendSVHandler, although it doesn't return anything */
__attribute__((naked)) void vPortPendSVHandler( void ){

    /* Note: The CPU Already Saved R0-R3,R12,LR,PC,PSR before switching to interrupt handling */
    /* The Current PSP points to the Stack of the Current Working Task */
    /* Save Remaining Context R4-R11,PSP */
    __asm__ volatile(
            "CPSID    I                         \n" /* Disable Interrupts */
            "MRS        R0,PSP                  \n" /* Synchronization Barriers */
            "ISB                                \n"

            "STMDB       R0!,{R4-R11}           \n" /* Save Remaining General Purpose Registers */
            "LDR        R1,[%[TCB]]             \n" /* R1 Points to pxCurrentTCB */
            "STR        R0,[R1]                 \n" /* Loading SP directly to where R1 points, This is Only Available because the stack pointer is in the start of the TCB block */
            "PUSH        {LR}					\n" /* Calling prvTaskGetNext will change the LR so we need to save it first */
            "BL         vTaskSwitchContext		\n" /* Activating Next Task */
            "POP		{LR}				    \n" /* Restore LR After Calling Functions */

            ::[TCB] "r" (&pxCurrentTCB):"r1");

    /* Restore Context of The New Task */
    __asm__ volatile (
            "LDR        R1,[%[TCB]]             \n" /* R1 Points to pxCurrentTCB */
            "LDR        R0,[R1]                 \n" /* Load SP from the nextTaskTCB */
            "LDMIA      R0!,{R4-R11}            \n" /* Return Context */
            "MSR        PSP,R0                  \n" /* Return Context */
            "ISB                                \n" /* Synchronization Barriers */
            "CPSIE      I                       \n" /* Enable Interrupts */
            "BX         LR                      \n" /* Branch and the CPU will Restore What it saved R0-R3,R12,LR,PC,PSR */

			::[TCB] "r" (&pxCurrentTCB):"r1");

}


void vPortYield(){
    SCB->ICSR.PENDSVSET = STD_HIGH;
}


BaseType_t xPortStartScheduler(){

    /* Disable Interrupts */
    __disable_irq();
    /* Activate First Ready Task */
    vTaskSwitchContext();
    /* Disable and Clear SysTick Timer */
    pSTK->CTRL.REG = 0x00;
    /* Clear Current Value in SysTick */
    pSTK->VAL.REG  = 0x00;
    /* Configure SysTick to Required Time Slice Based on configTICK_RATE_HZ */
    pSTK->LOAD.REG = System_PeripheralsClock.CPU / configTICK_RATE_HZ -1;

    /* Configure SysTick Interrupt Priority to Be Lowest */
    SCB->SHPR3.PRI_15_H= 0xE;

    /* Start SysTick */
    pSTK->CTRL.REG = 0b111;

    /* Enable Interrupts */

    /* Activate First Task */
    __asm volatile (
            "MOV        R0,#0x02                \n" /* Activate PSP as Task SP*/
            "MSR        CONTROL,R0              \n"
            "LDR        R0,[%[TCB]]             \n" /* R0 Points to pxCurrentTCB */
            "LDR        R1,[R0]                 \n" /* R1 is pxCurrentTCB */
            "MOV        SP,R1                   \n" /* Load Stack Pointer from TCB */
            "POP        {R4-R11}                \n" /* Load Context */
            "POP        {R0-R3}                 \n"
            "POP        {R12}                   \n"
            "ADD        SP,SP,#4                \n" /* Neglect LR */
            "POP        {LR}                    \n" /* Load PC to LR */
            "ADD        SP,SP,#4				\n"
            "CPSIE      I                       \n" /* Enable Interrupts */
            "BX         LR                      \n"
            ::[TCB] "r"(&pxCurrentTCB)  );
}




/**
 * @brief ISR of PendSV for stm32f103c8t6
 */
__attribute__((naked)) void PendSV_Handler(void){

	__asm__("PUSH {LR}\n");
    vPortPendSVHandler();
    __asm__("POP {LR} \n"
    		"BX       LR         \n");

}




/**
 * @brief Handler That Handles Automatic Context Switching
 *         Note Calling Function vTaskActivateNext to Select The Next Task
 */
__attribute__((naked))
void SysTick_Handler(void){

	  xTick++;
	  SCB->ICSR.PENDSVSET = STD_HIGH;

	__asm__ ("BX LR");


}

