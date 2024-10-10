
#include "core_functions.h"


#define CORE_FUNCTIONS_USE_C_IMPLEMENTATION

#ifdef CORE_FUNCTIONS_USE_C_IMPLEMENTATION


void __disable_irq(){
    __asm__ volatile ("CPSID i");
}

void __enable_irq(){
    __asm__ volatile ("CPSIE i");
}

#endif

uint32_t __get_BASEPRI(void) {
    uint32_t basepri;
    __asm__ volatile ("MRS %0, BASEPRI" : "=r" (basepri));
    return basepri;
}

static inline void __set_BASEPRI(uint32_t priority) {
    __asm__ volatile ("MSR BASEPRI, %0" : : "r" (priority));
}

uint32_t __get_PRIMASK(void) {
    uint32_t primask;
    __asm__ volatile ("MRS %0, PRIMASK" : "=r" (primask));
    return primask;
}

static inline void __set_PRIMASK(uint32_t priority) {
    __asm__ volatile ("MSR PRIMASK, %0" : : "r" (priority));
}



static inline void __set_CONTROL(uint32_t control) {
    __asm volatile ("MSR control, %0" : : "r" (control));
}


static inline void __activate_PSP() {
    __asm volatile (
            "PUSH {R0}            \n" /* Push R0 To Save it's value */
            "MRS R0, CONTROL      \n" /* Move CONTROL register to r0 */
            "MRS R0, CONTROL      \n" /* Move CONTROL register to r0 */
            "ORRS R0, R0, #0x02   \n" /* Set bit 1 to select PSP */
            "MSR CONTROL, R0      \n" /* Write back to CONTROL register */
            "POP {R0}            \n" /* Restore R0 */

            );
}


static inline void __activate_MSP() {
    __asm volatile (
            "PUSH {R0}            \n" /* Push R0 To Save it's value */
            "MRS R0, CONTROL      \n" /* Move CONTROL register to r0 */
            "MRS R0, CONTROL      \n" /* Move CONTROL register to r0 */
            "BIC R0, R0, #0x02    \n" /* Set bit 1 to select PSP */
            "MSR CONTROL, R0      \n" /* Write back to CONTROL register */
            "POP {R0}             \n" /* Restore R0 */
            );
}


static inline void __set_PSP(uint32_t psp) {
    __asm volatile ("MSR PSP, %0" : : "r" (psp));
}

static inline void __set_MSP(uint32_t msp) {
    __asm volatile ("MSR MSP, %0" : : "r" (msp));
}