/* a4.c
 * CSC Summer 2022
 * 
 * Student name:
 * Student UVic ID:
 * Date of completed work:
 *
 *
 * Code provided for Assignment #4
 *
 * Author: Mike Zastre (2022-Jul-19)
 *
 * This skeleton of a C language program is provided to help you
 * begin the programming tasks for A#4. As with the previous
 * assignments, there are "DO NOT TOUCH" sections. You are *not* to
 * modify the lines within these section.
 *
 * You are also NOT to introduce any new program-or file-scope
 * variables (i.e., ALL of your variables must be local variables).
 * YOU MAY, however, read from and write to the existing program- and
 * file-scope variables. Note: "global" variables are program-
 * and file-scope variables.
 *
 * UNAPPROVED CHANGES to "DO NOT TOUCH" sections could result in
 * either incorrect code execution during assignment evaluation, or
 * perhaps even code that cannot be compiled.  The resulting mark may
 * be zero.
 */


/* =============================================
 * ==== BEGINNING OF "DO NOT TOUCH" SECTION ====
 * =============================================
 */

#define __DELAY_BACKWARD_COMPATIBLE__ 1
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DELAY1 0.000001
#define DELAY3 0.01

#define PRESCALE_DIV1 8
#define PRESCALE_DIV3 64
#define TOP1 ((int)(0.5 + (F_CPU/PRESCALE_DIV1*DELAY1))) 
#define TOP3 ((int)(0.5 + (F_CPU/PRESCALE_DIV3*DELAY3)))

#define PWM_PERIOD ((long int)500)

volatile long int count = 0;
volatile long int slow_count = 0;


ISR(TIMER1_COMPA_vect) {
	count++;
}


ISR(TIMER3_COMPA_vect) {
	slow_count += 5;
}

/* =======================================
 * ==== END OF "DO NOT TOUCH" SECTION ====
 * =======================================
 */


/* *********************************************
 * **** BEGINNING OF "STUDENT CODE" SECTION ****
 * *********************************************
 */

void led_state(uint8_t LED, uint8_t state) {
if(state!=0){
	if (LED == 0x00)
	PORTL |= 0b10000000;
	else if (LED == 0x01)
	PORTL |= 0b000100000;
	else if (LED == 0x02)
	PORTL |= 0b00001000;
	else if (LED == 0x03)
	PORTL |= 0b00000010;
}
else {
	if (LED == 0x00)
	PORTL &= 0b01111111;
	else if (LED == 0x01)
	PORTL &= 0b11011111;
	else if (LED == 0x02)
	PORTL &= 0b11110111;
	else if (LED == 0x03)
	PORTL &= 0b11111101;
}
}



void SOS() {
    uint8_t light[] = {
        0x1, 0, 0x1, 0, 0x1, 0,
        0xf, 0, 0xf, 0, 0xf, 0,
        0x1, 0, 0x1, 0, 0x1, 0,
        0x0
    };

    int duration[] = {
        100, 250, 100, 250, 100, 500,
        250, 250, 250, 250, 250, 500,
        100, 250, 100, 250, 100, 250,
        250
    };

	int length = 19;
	for(int i = 0; i < length; i ++){
		if(light[i]==0x1){
			led_state(0, 1);
			_delay_ms(duration[i]);
			led_state(0, 0);
		}else if(light[i]==0x0){
			_delay_ms(duration[i]);	
		}else if(light[i]==0xf){
			led_state(0, 1);
			led_state(1, 1);
			led_state(2, 1);
			led_state(3, 1);
			_delay_ms(duration[i]);
			led_state(0, 0);
			led_state(1, 0);
			led_state(2, 0);
			led_state(3, 0);
			
		}
	
		}
	}

void glow(uint8_t LED, float brightness) {
	int threshold = PWM_PERIOD * brightness;
	for(;;){
		if (count < threshold)
		led_state(LED, 1);//75ms
		else if (count < PWM_PERIOD)
		led_state(LED, 0);//off part
		else{
			count = 0;//reset count
			led_state(LED, 1);
		}
	}

}



void pulse_glow(uint8_t LED) {
for(;;){
slow_count=0;
count=0;
for(int threshold=0; threshold<=PWM_PERIOD;threshold = slow_count * 0.1){
	
	
		if (count < threshold)
		led_state(LED, 1);
		else if (count < PWM_PERIOD)
		led_state(LED, 0);
		else{
			count = 0;
			led_state(LED, 1);
			}

}

slow_count=0;
count=0;
for(int threshold=0; threshold<=PWM_PERIOD;threshold = slow_count * 0.1){
	
	
	if (count < threshold)
	led_state(LED, 0);
	else if (count < PWM_PERIOD)
	led_state(LED, 1);
	else{
		count = 0;
		led_state(LED,0);
	}
	
	


}

}

}


void light_show() {
uint8_t light[] = {
0b00001111, 0b00000000, 0b00001111, 0b00000000, 0b00001111, 0b00000000,0b00000110, 0b00000000,0b00001001, 0b00000000,0b00001111, 0b00000000, 
0b00001111, 0b00000000, 0b00001111, 0b00000000,0b00001001,0b00000000,0b00000110,0b00000000,
0b00001000,0b00001100,0b00000110,0b00000011,0b00000001,0b00000011,0b00000110,0b00001100,
0b00001000,0b00001100,0b00000110,0b00000011,0b00000001, 0b00000011, 0b00000110,0b00001111,0b00000000,0b00001111,0b00000000,0b00000110,0b00000000,0b00000110, 0b00000000
};

int duration[] = {
250,250,250,250,250,250,100,100,100,100,250,250,250,250,250,250,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,250,250,250,250,250,250,250,250};
int length = 43;

for(int i = 0; i < length; i ++){
	if(light[i]==0b00000110){
		led_state(1, 1);
		led_state(2, 1);
		_delay_ms(duration[i]);
		led_state(1, 0);
		led_state(2, 0);
		}else if(light[i]==0b00000000){
		_delay_ms(duration[i]);
		}else if(light[i]==0b00001111){
		led_state(0, 1);
		led_state(1, 1);
		led_state(2, 1);
		led_state(3, 1);
		_delay_ms(duration[i]);
		led_state(0, 0);
		led_state(1, 0);
		led_state(2, 0);
		led_state(3, 0);
		
	}else if(light[i]==0b00001001){
		led_state(0, 1);
		led_state(3, 1);
		_delay_ms(duration[i]);
		led_state(0, 0);
		led_state(3, 0);
	}else if(light[i]==0b00001000){
		led_state(3, 1);
		_delay_ms(duration[i]);
		led_state(3, 0);
	}else if(light[i]==0b00001100){
	led_state(3, 1);
	led_state(2, 1);
	_delay_ms(duration[i]);
	led_state(2, 0);
	led_state(3, 0);
}else if(light[i]==0b00000011){
led_state(0, 1);
led_state(1, 1);
_delay_ms(duration[i]);
led_state(0, 0);
led_state(1, 0);
}else if(light[i]==0b00000011){
led_state(0, 1);
led_state(1, 1);
_delay_ms(duration[i]);
led_state(0, 0);
led_state(1, 0);
}else if(light[i]==0b00000001){
led_state(0, 1);
_delay_ms(duration[i]);
led_state(0, 0);

}
	
}
}


/* ***************************************************
 * **** END OF FIRST "STUDENT CODE" SECTION **********
 * ***************************************************
 */


/* =============================================
 * ==== BEGINNING OF "DO NOT TOUCH" SECTION ====
 * =============================================
 */

int main() {
    /* Turn off global interrupts while setting up timers. */

	cli();

	/* Set up timer 1, i.e., an interrupt every 1 microsecond. */
	OCR1A = TOP1;
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1B |= (1 << WGM12);
    /* Next two lines provide a prescaler value of 8. */
	TCCR1B |= (1 << CS11);
	TCCR1B |= (1 << CS10);
	TIMSK1 |= (1 << OCIE1A);

	/* Set up timer 3, i.e., an interrupt every 10 milliseconds. */
	OCR3A = TOP3;
	TCCR3A = 0;
	TCCR3B = 0;
	TCCR3B |= (1 << WGM32);
    /* Next line provides a prescaler value of 64. */
	TCCR3B |= (1 << CS31);
	TIMSK3 |= (1 << OCIE3A);


	/* Turn on global interrupts */
	sei();
light_show();

/* =======================================
 * ==== END OF "DO NOT TOUCH" SECTION ====
 * =======================================
 */


/* *********************************************
 * **** BEGINNING OF "STUDENT CODE" SECTION ****
 * *********************************************
 */

/* This code could be used to test your work for part A.

	led_state(0, 1);
	_delay_ms(1000);
	led_state(2, 1);
	_delay_ms(1000);
	led_state(1, 1);
	_delay_ms(1000);
	led_state(2, 0);
	_delay_ms(1000);
	led_state(0, 0);
	_delay_ms(1000);
	led_state(1, 0);
	_delay_ms(1000);
 */

/* This code could be used to test your work for part B.

	SOS();
 */

/* This code could be used to test your work for part C.

	glow(2, .01);
 */



/* This code could be used to test your work for part D.

	pulse_glow(3);
 */


/* This code could be used to test your work for the bonus part.

	light_show();
 */

/* ****************************************************
 * **** END OF SECOND "STUDENT CODE" SECTION **********
 * ****************************************************
 */
}
