

#ifndef RTOSCONFIG_H
#define RTOSCONFIG_H




/**************	Section: Includes ***************************/

/**************	Section: Macro Definitions Declarations *****/

/**
 * @brief Minimal Recommended Stack Size of a task
 *          Note it's not in bytes it is in WORDS
 *          EX: for 32bit architectures 100 means 100 * 4 = 400 Bytes
 */
#define configMINIMAL_STACK_SIZE (100)


/**
 * @brief Define Number of Priorities levels supported. Starts from 0 to (configMAX_PRIORITIES - 1)
 *          Should Be Minimized as possible to decrease Memory Usage and Increase Performance
 */
#define configMAX_PRIORITIES    (32)


/**
 * @brief Time Slice Size in HZ (ex 100 HZ -> 10ms)
 */
#define configTICK_RATE_HZ      (100)


/**
 * @brief Maximum Task Name Length. Only Used For Debugging Purposes you can make it smaller to decrease the memory consumed by it since every task allocate that size of bytes
 */
#define configMAX_NAME_LEN	(20)

/**
 * @brief Initial Ticks Value for the Scheduler
 */
#define configINITIAL_TICK_COUNT (0)
/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/




/**************	Section: Methods Declarations  **************/
#endif //RTOSCONFIG_H
