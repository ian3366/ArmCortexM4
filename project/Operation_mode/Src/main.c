/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

void generate_interrupt()
{
	uint32_t* pSTIR = (uint32_t*)0xE000EF00;
	uint32_t* pISER0 = (uint32_t*)0xE000E100;

	//enable IRQ3 interrupt
	*pISER0 |= (1<<3);
	//gen interrupt
	*pSTIR 	|= (3 & 0x1FF);

}
void change_access_level_unpriv(){
	//some process system control register address can only be access in privileged access level
	//when unprivileged access level attempt to change the contain of these register will cause exception
	__asm volatile("MRS R0 , CONTROL");
	__asm volatile("ORR R0 , 0x1");
	__asm volatile("MSR CONTROL , R0");
}

int main(void)
{
    /* Loop forever */
	printf("In Thread Mode : before Interrupt \n");
	change_access_level_unpriv();
	generate_interrupt();
	printf("In Thread Mode : after Interrupt \n" );


	for(;;);
}

void RTC_WKUP_IRQHandler(void){
	printf("In Handler Mode : ISR \n"); //   interrupt service routine
}

void HardFault_Handler(void){
	printf("In Hard Fault Exception");
}


