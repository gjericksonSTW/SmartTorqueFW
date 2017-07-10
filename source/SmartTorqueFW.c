/*******************************************************************************
*	SMART TORQUE WRENCH SYSTEM - 2017 SHELL TECHWORKS
*
******************************************************************************/

/*******************************************************************************
 * Libraries
 ******************************************************************************/

/* Headers for each hardware peripheral used */
#include <_ADCSense.h>
#include <_Bluetooth.h>
#include <_FRAM.h>
#include <_HMI.h>
//#include <_RTC.h>
#include <_Timer.h>
#include <_Sys_Control.h>

/* Headers for the FreeRTOS engine */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Device Specific Drivers and Initialization */
#include "fsl_device_registers.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void vApplicationTickHook(void);
void vApplicationMallocFailedHook(void);
void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName);
void vApplicationIdleHook(void);

/*******************************************************************************
 * Code
 ******************************************************************************/

//Main function initiating all RTOS tasks and configuring pins / peripherals
int main(void)
{
    /* Initialize board hardware. */
	BOARD_I2C_ReleaseBus();
    BOARD_InitOSC();
    BOARD_BootClockRUN();
    BOARD_InitLEDs();
    BOARD_InitPins();	// Configure all hardware related pin assignments **Does not notify you to turn on certain pins
    BOARD_InitLCD();
    BOARD_InitDEBUG_UART();
    Timer_INIT();

    //Initialize ADC interface and peripherals
    ADC_INIT(ADC16_BASE);

    //Initialize Buttons and Display
    HMI_INIT();

    //Initialize I2C for access to FRAM chip and stored configuration data
    FRAM_INIT();

    //Initialize default system settings
    Sys_Control_INIT();

    //Initialize Bluetooth interface and peripherals
    Bluetooth_INIT();

    //Initialize the RTC interface and peripheral, currently not implemented on RTOS (Time captured by host device)
    //RTC_INIT();

    //Begin ADC task for reading values from the two channels to handle Torque and Battery sensing
    xTaskCreate(vADC16Task, "VoltageConverter", 500, NULL, 1, NULL);

    //Begin the system configuration task that will handle all updates to the system settings/ communicate with FRAM
    xTaskCreate(vSystemControllerTask, "SystemControl", 500, NULL, 1, NULL);

    //Begin Bluetooth communication task via UART2 and Debug/LPUART task to send information to the console
    xTaskCreate(vBluetoothTask, "Bluetooth", 600, NULL, 1, NULL);

    //Reset the Bluetooth chip before starting the scheduler so it is in a known state
    Bluetooth_Reset();

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following line
    will never be reached.  If the following line does execute, then there was
    insufficient FreeRTOS heap memory available for the idle and/or timer tasks
    to be created.  See the memory management section on the FreeRTOS web site
    for more details.  */

    for (;;)
        ;
}

// Called each time a tick occurs from the RTOS
void vApplicationTickHook(void)
{

    static uint32_t ulCount = 0;

    /* The RTOS tick hook function is enabled by setting configUSE_TICK_HOOK to
    1 in FreeRTOSConfig.h.

    "Give" the semaphore on every 500th tick interrupt. */
    ulCount++;
    if (ulCount >= 500UL)
    {
        /* This function is called from an interrupt context (the RTOS tick
        interrupt),    so only ISR safe API functions can be used (those that end
        in "FromISR()".

        xHigherPriorityTaskWoken was initialized to pdFALSE, and will be set to
        pdTRUE by xSemaphoreGiveFromISR() if giving the semaphore unblocked a
        task that has equal or higher priority than the interrupted task. */
        ulCount = 0UL;
    }

    /* If xHigherPriorityTaskWoken is pdTRUE then a context switch should
    normally be performed before leaving the interrupt (because during the
    execution of the interrupt a task of equal or higher priority than the
    running task was unblocked).  The syntax required to context switch from
    an interrupt is port dependent, so check the documentation of the port you
    are using.

    In this case, the function is running in the context of the tick interrupt,
    which will automatically check for the higher priority task to run anyway,
    so no further action is required. */
}

// Called when insufficient memory is in the RTOS heap
void vApplicationMallocFailedHook(void)
{
    /* The malloc failed hook is enabled by setting
    configUSE_MALLOC_FAILED_HOOK to 1 in FreeRTOSConfig.h.

    Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
    for (;;)
        ;
}

/*!
 * @brief Stack overflow hook.
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName)
{
    (void)pcTaskName;
    (void)xTask;

    /* Run time stack overflow checking is performed if
    configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected.  pxCurrentTCB can be
    inspected in the debugger if the task name passed into this function is
    corrupt. */
    for (;;)
        ;
}

/*!
 * @brief Idle hook.
 */
void vApplicationIdleHook(void)
{
    volatile size_t xFreeStackSpace;

    /* The idle task hook is enabled by setting configUSE_IDLE_HOOK to 1 in
    FreeRTOSConfig.h.

    This function is called on each cycle of the idle task.  In this case it
    does nothing useful, other than report the amount of FreeRTOS heap that
    remains unallocated. */
    xFreeStackSpace = xPortGetFreeHeapSize();

    if (xFreeStackSpace > 100)
    {
        /* By now, the kernel has allocated everything it is going to, so
        if there is a lot of heap remaining unallocated then
        the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
        reduced accordingly. */
    }
}
