// SPDX-License-Identifier: MIT
// Copyright © 2028 https://github.com/coolbreeze413

#include "hal_fpga_onion_pwmctrl.h"


void hal_fpga_onion_pwmctrl_enable (uint8_t io_pad_num, 
                                    uint8_t io_pad_pwm_value)
{
    if(io_pad_num == 27)
    {
        *FPGA_ONION_PWMCTRL_REG_ADDR_PWM_0_CONFIG = (1 << 31) | io_pad_pwm_value;
    }
    else if(io_pad_num == 28)
    {
        *FPGA_ONION_PWMCTRL_REG_ADDR_PWM_1_CONFIG = (1 << 31) | io_pad_pwm_value;
    }
    else if(io_pad_num == 29)
    {
        *FPGA_ONION_PWMCTRL_REG_ADDR_PWM_2_CONFIG = (1 << 31) | io_pad_pwm_value;
    }
    else if(io_pad_num == 30)
    {
        *FPGA_ONION_PWMCTRL_REG_ADDR_PWM_3_CONFIG = (1 << 31) | io_pad_pwm_value;
    }
}

void hal_fpga_onion_pwmctrl_disable (uint8_t io_pad_num)
{
    if(io_pad_num == 27)
    {
        *FPGA_ONION_PWMCTRL_REG_ADDR_PWM_0_CONFIG = 0;
    }
    else if(io_pad_num == 28)
    {
        *FPGA_ONION_PWMCTRL_REG_ADDR_PWM_1_CONFIG = 0;
    }
    else if(io_pad_num == 29)
    {
        *FPGA_ONION_PWMCTRL_REG_ADDR_PWM_2_CONFIG = 0;
    }
    else if(io_pad_num == 30)
    {
        *FPGA_ONION_PWMCTRL_REG_ADDR_PWM_3_CONFIG = 0;
    }
}

uint32_t hal_fpga_onion_pwmctrl_getval (uint8_t io_pad_num)
{
    uint32_t pwm_config = 0;

    if(io_pad_num == 27)
    {
        pwm_config = *FPGA_ONION_PWMCTRL_REG_ADDR_PWM_0_CONFIG;
    }
    else if(io_pad_num == 28)
    {
        pwm_config = *FPGA_ONION_PWMCTRL_REG_ADDR_PWM_1_CONFIG;
    }
    else if(io_pad_num == 29)
    {
        pwm_config = *FPGA_ONION_PWMCTRL_REG_ADDR_PWM_2_CONFIG;
    }
    else if(io_pad_num == 30)
    {
        pwm_config = *FPGA_ONION_PWMCTRL_REG_ADDR_PWM_3_CONFIG;
    }

    return pwm_config;
}
