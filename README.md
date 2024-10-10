
# Introduction

This project is a c implementation of RTOS (Real Time Operating System) based on [FreeRTOS](https://www.freertos.org/). The Architecture and API methods names made like FreeRTOS. it's fully implemented from scratch. you will find a lot of similarities in the code with the FreeRTOS code and a lot of changes also (based on my understanding and how should i create the API).

The Project is based on STM32 BlueBill(stm32f103c8t6) Chip.


# Ideas of RTOS

## 1. Context Switching

The Idea of Context Switching is to take a snapshot of the current running task with it's all states. this on processor means to copy all GPRs(General Purpose Registers) with some special and save them somewhere (Stack of the Task) and then when restoring the context write the snapshot back to the registers.

### 1.1 Context Saving

![[assets/CoreRegisters.png]]
reference: [CortexM3 Programming Manual @ Page 14](https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.st.com/resource/en/programming_manual/pm0056-stm32f10xxx20xxx21xxxl1xxxx-cortexm3-programming-manual-stmicroelectronics.pdf&ved=2ahUKEwiV44j9yIOJAxXQ9bsIHchnI8kQFnoECCIQAQ&usg=AOvVaw0BM1fJ-D5EHLBl8x8n6Nvo)

The required registers to be saved to save the context of the task are (R0-R12), SP, PC, PSR.
The Context Switching is done in `PendSV` Interrupt. and since it's done in interrupt this means that the cpu will do part of the work to us automatically, it will save (R0-R3), R12, LR, PC, PSR. and this process is called  `Stacking`.

![[assets/stacking.png]]

In the `PendSV` Interrupt Handling we save the remaining Registers (R4-R11) by pushing it to the stack of the task. This is done in assembly code.

### 1.2 Context Restoring
When restoring the context of a task we POP the saved registers in the same order. (only R4-R11 and the CPU will restore the rest for us).


## 2. Scheduler Algorithm

### 2.1 Round Robin Algorithm

The Round Robin (RR) algorithm is a widely used scheduling algorithm in operating systems, particularly for time-sharing environments. It is designed to ensure that all processes (Tasks) receive an equal opportunity to use the CPU, making it fair and efficient for multi-tasking. The time sharing is done by **Time Slicing** by providing a slice of the time (Quantum) for each task.

Although it seems perfect for multi tasking. but it doesn't meet all embedded system requirements. Some of the tasks in embedded systems has to be served immediately when get ready. but in round robin fashion it has to wait until all the tasks before it to be served. 

### 2.2 Prioritized Pre-emptive Scheduling with Time Slicing

Also Known As (Priority Round Robin)
It uses priority for each task and the task with the higher priority must be served first. Also Preempting makes it we don't have to wait the current running low priority task to finish its time slice to release the CPU. The Context Switching will be performed as soon as the higher priority task appear in ready state.

![[assets/priority round robin.png]]
reference [Mastering the FreeRTOS Real Time Kernel @ Page 93](https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.freertos.org/media/2018/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf&ved=2ahUKEwinmIrM04OJAxWoTKQEHcA1EZUQFnoECBYQAQ&usg=AOvVaw1MS5-TOFoSISa1k5GrZStM)


# Project
the project doesn't fully implement the FreeRTOS APIs. and shouldn't be used in production it was only for Learning Purposes.
![Video][assets/v3.webm]

