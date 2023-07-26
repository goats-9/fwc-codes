#include "Fw_global_config.h"   // This defines application specific charactersitics

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "RtosTask.h"
}

/*    Include the generic headers required for QORC */
#include "eoss3_hal_gpio.h"
#include "eoss3_hal_rtc.h"
#include "eoss3_hal_timer.h"
#include "eoss3_hal_fpga_usbserial.h"
#include "ql_time.h"
#include "s3x_clock_hal.h"
#include "s3x_clock.h"
#include "s3x_pi.h"
#include "dbg_uart.h"
#include "hal_fpga_onion_gpioctrl.h"
#include "cli.h"


extern const struct cli_cmd_entry my_main_menu[];


const char *SOFTWARE_VERSION_STR;

/*
 * Global variable definition
 */

#define SW_MB_1 0x40005110
#define PIN_a 1
#define PIN_b 2
#define PIN_c 3
#define PIN_d 4
#define PIN_e 5
#define PIN_f 6
#define PIN_g 7

void sevenseg(int a, int b, int c, int d, int e, int f, int g) {
    hal_fpga_onion_gpioctrl_set_output(PIN_a, a);
    hal_fpga_onion_gpioctrl_set_output(PIN_b, b);
    hal_fpga_onion_gpioctrl_set_output(PIN_c, c);
    hal_fpga_onion_gpioctrl_set_output(PIN_d, d);
    hal_fpga_onion_gpioctrl_set_output(PIN_e, e);
    hal_fpga_onion_gpioctrl_set_output(PIN_f, f);
    hal_fpga_onion_gpioctrl_set_output(PIN_g, g);
}

void disp(int num) {
    switch (num) {
        case 0:
            sevenseg(0,0,0,0,0,0,1);
            return;
        case 1:
            sevenseg(1,0,0,1,1,1,1);
            return;
        case 2:
            sevenseg(0,0,1,0,0,1,0);
            return;
        case 3:
            sevenseg(0,0,0,0,1,1,0);
            return;
        case 4:
            sevenseg(1,0,0,1,1,0,0);
            return;
        case 5:
            sevenseg(0,1,0,0,1,0,0);
            return;
        case 6:
            sevenseg(0,1,0,0,0,0,0);
            return;
        case 7:
            sevenseg(0,0,0,1,1,1,1);
            return;
        case 8:
            sevenseg(0,0,0,0,0,0,0);
            return;
        case 9:
            sevenseg(0,0,0,0,1,0,0);
            return;
        default:
            sevenseg(0,1,1,0,0,0,0);
            return;
    }
}

extern void qf_hardwareSetup();
static void nvic_init(void);
int main(void)
{
    uint32_t i=0,j=0,k=0;
    SOFTWARE_VERSION_STR = "qorc-onion-apps/qf_hello-fpga-gpio-ctlr";
    
    qf_hardwareSetup();
    nvic_init();

    S3x_Clk_Enable(S3X_M4_S12_S15_CLK);

    dbg_str("\n\n");
    dbg_str( "##########################\n");
    dbg_str( "Quicklogic QuickFeather FPGA GPIO CONTROLLER EXAMPLE\n");
    dbg_str( "SW Version: ");
    dbg_str( SOFTWARE_VERSION_STR );
    dbg_str( "\n" );
    dbg_str( __DATE__ " " __TIME__ "\n" );
    dbg_str( "##########################\n\n");


    CLI_start_task( my_main_menu );
	HAL_Delay_Init();
    while(1) {
        uint32_t digit = *SW_MB_1;
        disp(digit);
    }
    /* Start the tasks and timer running. */
    vTaskStartScheduler();
    dbg_str("\n");

    while(1);
}

static void nvic_init(void)
 {
    // To initialize system, this interrupt should be triggered at main.
    // So, we will set its priority just before calling vTaskStartScheduler(), not the time of enabling each irq.
    NVIC_SetPriority(Ffe0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(SpiMs_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(CfgDma_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(Uart_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_SetPriority(FbMsg_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
 }    

//needed for startup_EOSS3b.s asm file
void SystemInit(void)
{

}
