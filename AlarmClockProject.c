/*
 * Copyright (c) 2017, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MKL43Z256xxx4_Project.c
 * @brief   Application entry point.
 * EECS 3215 Final Project
 * Alarm Clock
 * Code Written by Danilo Torres Fleites (214152326)
 * Multiple code examples provided in EECS 3215 lectures were used in this project.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL43Z4.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

 volatile int time=0;
 volatile int count=0;
 volatile int soundAlarm=0;
 volatile int alarmTime=715;
 volatile int displayAlarm=1;
 volatile int speakercount=0;

 void delaySeg(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 800; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 800000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

/*Display the desired number on the 7-segment*/
void digitNumber(int x){
	switch(x){

	case 0:
				PTE->PSOR = 0b00000000000000000000000000000001;//g
	break;
	case 1:
   	    		PTA->PSOR = 0b00000000000000000000000000000010;//a
   	    		PTE->PSOR = 0b01000000000000000000000000000000;//d
   	       	    PTA->PSOR = 0b00000000000000000000000000100000;//e
   	       	    PTA->PSOR = 0b00000000000000000010000000000000;//f
   	       	    PTE->PSOR = 0b00000000000000000000000000000001;//g
	break;
	case 2:
   	       	    PTA->PSOR = 0b00000000000000000001000000000000;//c
   	       	    PTA->PSOR = 0b00000000000000000010000000000000;//f
	break;
	case 3:
   	       	    PTA->PSOR = 0b00000000000000000000000000100000;//e
   	       	    PTA->PSOR = 0b00000000000000000010000000000000;//f
	break;
	case 4:
   	    		PTA->PSOR = 0b00000000000000000000000000000010;//a
   	    		PTE->PSOR = 0b01000000000000000000000000000000;//d
   	       	    PTA->PSOR = 0b00000000000000000000000000100000;//e
	break;
	case 5:
   	       	    PTA->PSOR = 0b00000000000000000000000000000100;//b
   	       	    PTA->PSOR = 0b00000000000000000000000000100000;//e
	break;
	case 6:
				PTA->PSOR = 0b00000000000000000000000000000100;//b
	break;
	case 7:
				PTE->PSOR = 0b01000000000000000000000000000000;//d
   	       	    PTA->PSOR = 0b00000000000000000000000000100000;//e
   	       	    PTA->PSOR = 0b00000000000000000010000000000000;//f
   	       	    PTE->PSOR = 0b00000000000000000000000000000001;//g
	break;
	case 8:
				PTA->PCOR = 0b00000000000000000011000000100110;
				PTE->PCOR = 0b01000000000000000000000000000001;
	break;
	case 9:
				PTE->PSOR = 0b01000000000000000000000000000000;//d
   	       	    PTA->PSOR = 0b00000000000000000000000000100000;//e
	break;
	}
}

/*Extract each digit of the desired time to display on the 7-segment.
 *Alternate each digit with a small delay to display the time every time it is updated.
 */

void displayTime(int x){

	int dig1,dig2,dig3,dig4;

	dig4=x%10;
	if (dig4 == 10) {
		dig4 = 0;
	} else {
		dig4 = dig4%10;
	}
	dig3=(int)(x/10)%100;
	if (dig3 == 10) {
		dig3 = 0;
	} else {
		dig3 = dig3%10;
	}
	dig2=(int)(x/100)%1000;
	if (dig2 == 10) {
		dig2 = 0;
	} else {
		dig2 = dig2%10;
	}

	if(x<1000){
		dig1=0;
	}else{
	dig1=(int)(x/1000);
	}


	PTD->PCOR = 0b00000000000000000000000000111100;

	    	    //digit 1
	    	    PTA->PCOR = 0b00000000000000000011000000100110;
	    	    PTE->PCOR = 0b01000000000000000000000000000001;

	    	    PTD->PSOR = 0b00000000000000000000000000000100;//1
	    	    digitNumber(dig1);
	    	    delaySeg();
	    	    PTD->PCOR = 0b00000000000000000000000000000100;

	    	    //digit 2
	      	    PTA->PCOR = 0b00000000000000000011000000100110;
	        	PTE->PCOR = 0b01000000000000000000000000000001;

	    	    PTD->PSOR = 0b00000000000000000000000000001000;//2
	    	    digitNumber(dig2);
	    	    delaySeg();
	       	    PTD->PCOR = 0b00000000000000000000000000001000;

	    	    //digit 3
	      	    PTA->PCOR = 0b00000000000000000011000000100110;
	        	PTE->PCOR = 0b01000000000000000000000000000001;

	    	    PTD->PSOR = 0b00000000000000000000000000010000;//3
	    	    digitNumber(dig3);
	    	    delaySeg();
	       	    PTD->PCOR = 0b00000000000000000000000000010000;

	    	    //digit 4
	      	    PTA->PCOR = 0b00000000000000000011000000100110;
	        	PTE->PCOR = 0b01000000000000000000000000000001;

	    	    PTD->PSOR = 0b00000000000000000000000000100000;//4
	    	    digitNumber(dig4);
	    	    delaySeg();
	       	    PTD->PCOR = 0b00000000000000000000000000100000;

	       	// printf("%d%d%d%d",dig1,dig2,dig3,dig4);
}

int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    printf("Hello World\n");


    //buttons
    SIM -> SCGC5 |= SIM_SCGC5_PORTC_MASK;  //feeding clock to portc
    PORTC -> PCR[3] |= 0x100; //setting multiplexer to gpio
    PORTC -> PCR[3] |= 0b0011; //activating pull up resistor

    PORTC -> PCR[1] |= 0x100; //setting multiplexer to gpio
    PORTC -> PCR[1] |= 0b0011; //activating pull up resistor

    PORTC -> PCR[2] |= 0x100; //setting multiplexer to gpio
    PORTC -> PCR[2] |= 0b0011; //activating pull up resistor

    PORTC -> PCR[4] |= 0x100; //setting multiplexer to gpio
    PORTC -> PCR[4] |= 0b0011; //activating pull up resistor

    PTC->PDDR &= ~(0b00011110); //making bits 1,2,3,4 input


    //7-Seg display initialize

    /*Step 1. Turn on the clocks for Ports A,B,D and E*/
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;


    //Two Timer Based ISR (Interupt Service Routines)

    	__disable_irq();				//global

    	SIM->SOPT2 |= 0x01000000;
    	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;		//setting up 2 timers
    	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;

    	TPM0->SC = 0;					//disable
    	TPM0->SC = 0x07;				//dividing by 128 (slow down)
    	TPM0->MOD = 0x00F0;
    	TPM0->SC |= 0x80;	//TPM_SC_TOF_MASK
    	TPM0->SC |= 0x40;	//TPM_SC_TOIE_MASK
    	TPM0->SC |= 0x08;	//enable timer

    	NVIC->ISER[0] |= 0x00020000;	//IRQ 17 for TPM 0

    	//TPM1
    	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
    	TPM1->SC=0x0;
    	TPM1->SC=0x07;
    	TPM1->MOD=0x7FFF; 	//half of FFFF
    	TPM1->SC |= 0x80;	//TOF clear
    	TPM1->SC |= 0x40;	//enable
    	TPM1->SC |= 0x08;	//enable

    	NVIC->ISER[0] |= 0x00040000;	//IRQ 18 for TPM 1

    	__enable_irq();


    //ADC Code
    	PORTE->PCR[22] = 0x000; 		//Alt0

    //ADC0 setup

    	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
    	ADC0->CFG1 = 0x40 | 0x10 |0x04 | 0x00;
    	ADC0->SC2 &= ~0x40;

    /*Step 2. Set up mux's for each pin to GPIO*/
    PORTA->PCR[1] = 0x100;
    PORTA->PCR[2] = 0x100;
    PORTA->PCR[4] = 0x100;
    PORTA->PCR[5] = 0x100;
    PORTA->PCR[12] = 0x100;
    PORTA->PCR[13] = 0x100;
    PORTB->PCR[0] = 0x100;
    PORTD->PCR[2] = 0x100;
    PORTD->PCR[3] = 0x100;
    PORTD->PCR[4] = 0x100;
    PORTD->PCR[5] = 0x100;
    PORTD->PCR[6] = 0x100;
    PORTE->PCR[0] = 0x100;
    PORTE->PCR[1] = 0x100;
    PORTE->PCR[30] = 0x100;


    /*Step 3. Set various pins as output*/
    PTD->PDDR = 0b00000000000000000000000001111100;
    PTA->PDDR = 0b00000000000000000011000000100110;
    PTE->PDDR = 0b01000000000000000000000000000011;
    PTB->PDDR = 0b00000000000000000000000000000001;

    /*Step 4. Light up LEDs. Start by setting all digit values to output zero.*/
    PTD->PCOR = 0b00000000000000000000000001111100;
    PTA->PCOR = 0b00000000000000000011000000100110;
    PTE->PCOR = 0b01000000000000000000000000000011;
    PTB->PCOR = 0b00000000000000000000000000000001;

    PTD->PSOR = 0b00000000000000000000000001000000;//testing the ":" always turning it on

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
   // volatile static int j = 0 ;

    /* Enter an infinite loop, just incrementing a counter. */

    volatile int result;


    while(1) {
    	  i = PTC -> PDIR;  //copy


    	    //POLLing

    	  /* Alarm View */
    	    if((i&0x00000008)==0){
    	    	delay();

    	    	printf("button pressed \n");

    	    	displayAlarm=!displayAlarm;

    	    }



    	    /*Hours Button*/
    	    if((i&0x00000002)==2){
    	    	delay();

    	    	printf("hour button pressed \n");

    	    	if(displayAlarm==0){

    	    		if(time/100==23){
    	    				time=(time+100)-2300;
    	    			}else{
    	    		time+=100;}

    	    	}else{
    	    		if(alarmTime/100==23){
    	    				alarmTime=0;
    	    			}else{
    	    		alarmTime+=100;}
    	    	}

    	    }

    	   //Minutes Button
    	    if((i&0x00000004)==4){
    	    	delay();

    	    	printf("minutes button pressed \n");

    	    	if(displayAlarm==0){

    	    		if(time%100==59 && time!=2359){

    	    				time+=41;
    	    			}else if(time==2359){
    	    		time=0;}
    	    		else{
    	    		time+=1;
    	    		}

    	    	}else{
    	        	if(alarmTime%100==59 && alarmTime!=2359){

    	    				alarmTime+=41;
    	    			}else if(alarmTime==2359){
    	    		alarmTime=0;}
    	    		else{
    	    		alarmTime+=1;
    	    		}

    	    	}

    	    }


    	  //  ClearTime Button
    	        	    if((i&0x00000010)==16){
    	        	    	delay();

    	        	    	printf("ClearTime button pressed \n");

    	        	    	if(displayAlarm==0){
							time=0;

    	        	    	}else{
    	        	       	alarmTime=0;
    	        	    	}

    	        	    }

    	  // Displaying alarm time or clock time

    	    if(displayAlarm==0){
    	    displayTime(time);
    	    }else{
    	    	displayTime(alarmTime);
    	    }

    	    if(time==alarmTime){
    	    	soundAlarm=1;
    	    }


    	    //Channel 3 of ADC0 (PTE bit 22)

    	    	ADC0->SC1[0] = 3;	//Read CH3 of ADC0

    	    	while(!(ADC0->SC1[0]&0x80)){}
    	    	//wait for CoCo, Conversion Complete
    	    	result = ADC0->R[0];
    	    	//printf("result:%d\n",result);

    	    	//sounding alarm
    	    	if(result<4095){
    	    		soundAlarm=0;
    	    	}

    }
    return 0 ;
}

void TPM0_IRQHandler(void){

	//speaker count is to make it sound numerous times instead of just 1 long beep
	if(soundAlarm==1){
		if(speakercount<1000){
	PTB->PTOR = 0b00000000000000000000000000000001;
		}

		speakercount++;
		if(speakercount==2000){
			speakercount=0;
		}
	}
	//time-=10;
	TPM0->SC |= 0x80; 	//clear TOF
}


void TPM1_IRQHandler(void){

	//outer count of 60 for minutes
	//inner count of 12 for seconds
	if(count==12){

		if(time%100==59 && time!=2359){
			time+=41;
		}
		else if(time==2359){
			time=0;
		}
		else{
			time+=1;
		}
	count=0;
	}

	count++;
	TPM1->SC |= 0x80; 	//clear TOF
}
