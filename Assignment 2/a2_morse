; a2_morse.asm
; CSC 230: Summer 2022
;
; Student name:
; Student ID:
; Date of completed work:
;
; *******************************
; Code provided for Assignment #2
;
; Author: Mike Zastre (2019-Jun-12)
; 
; This skeleton of an assembly-language program is provided to help you
; begin with the programming tasks for A#2. As with A#1, there are 
; "DO NOT TOUCH" sections. You are *not* to modify the lines
; within these sections. The only exceptions are for specific
; changes announced on conneX or in written permission from the course
; instructor. *** Unapproved changes could result in incorrect code
; execution during assignment evaluation, along with an assignment grade
; of zero. ****
;
; I have added for this assignment an additional kind of section
; called "TOUCH CAREFULLY". The intention here is that one or two
; constants can be changed in such a section -- this will be needed
; as you try to test your code on different messages.
;


; =============================================
; ==== BEGINNING OF "DO NOT TOUCH" SECTION ====
; =============================================

.include "m2560def.inc"

.cseg
.equ S_DDRB=0x24
.equ S_PORTB=0x25
.equ S_DDRL=0x10A
.equ S_PORTL=0x10B

	
.org 0
	; Copy test encoding (of 'sos') into SRAM
	;
	ldi ZH, high(TESTBUFFER)
	ldi ZL, low(TESTBUFFER)
	ldi r16, 0x21
	st Z+, r16
	ldi r16, 0x37
	st Z+, r16
	ldi r16, 0x30
	st Z+, r16
	clr r16
	st Z, r16

	; initialize run-time stack
	ldi r17, high(0x21ff)
	ldi r16, low(0x21ff)
	out SPH, r17
	out SPL, r16

	; initialize LED ports to output
	ldi r17, 0xff
	sts S_DDRB, r17
	sts S_DDRL, r17

; =======================================
; ==== END OF "DO NOT TOUCH" SECTION ====
; =======================================

; ***************************************************
; **** BEGINNING OF FIRST "STUDENT CODE" SECTION **** 
; ***************************************************

	; If you're not yet ready to execute the
	; encoding and flashing, then leave the
	; rjmp in below. Otherwise delete it or
	; comment it out.

	;rjmp stop

    ; The following seven lines are only for testing of your
    ; code in part B. When you are confident that your part B
    ; is working, you can then delete these seven lines. 
	;ldi r17, high(TESTBUFFER)
	;ldi r16, low(TESTBUFFER)
	;push r17
	;push r16
	;rcall flash_message
    ;pop r16
  ;pop r17
   ;stop1:
   ;rjmp stop1
; ***************************************************
; **** END OF FIRST "STUDENT CODE" SECTION ********** 
; ***************************************************


; ################################################
; #### BEGINNING OF "TOUCH CAREFULLY" SECTION ####
; ################################################

; The only things you can change in this section is
; the message (i.e., MESSAGE01 or MESSAGE02 or MESSAGE03,
; etc., up to MESSAGE09).
;

	; encode a message
	;
	ldi r17, high(MESSAGE01 << 1)
	ldi r16, low(MESSAGE01 << 1)
	push r17
	push r16
	ldi r17, high(BUFFER01)
	ldi r16, low(BUFFER01)
	push r17
	push r16
	rcall encode_message
	pop r16
	pop r16
	pop r16
	pop r16

; ##########################################
; #### END OF "TOUCH CAREFULLY" SECTION ####
; ##########################################


; =============================================
; ==== BEGINNING OF "DO NOT TOUCH" SECTION ====
; =============================================
	; display the message three times
	;
	ldi r18, 3
main_loop:
	ldi r17, high(BUFFER01)
	ldi r16, low(BUFFER01)
	push r17
	push r16
	rcall flash_message
	dec r18
	tst r18
	brne main_loop


stop:
	rjmp stop
; =======================================
; ==== END OF "DO NOT TOUCH" SECTION ====
; =======================================


; ****************************************************
; **** BEGINNING OF SECOND "STUDENT CODE" SECTION **** 
; ****************************************************


flash_message:
.set PARAM_OFFSET = 9
push r16
push YL
push YH
push ZL 
push ZH 		

in ZH, SPH	
in ZL, SPL	
				
ldd YL, Z+PARAM_OFFSET	;set the pointer point to BUFFER
ldd YH, Z+PARAM_OFFSET+1
loop: 
ld r16, Y+;load one byte from BUFFER
tst r16
breq over
call morse_flash
								
rjmp loop
				
over:
pop ZH
pop ZL
pop YH
pop YL
pop r16
ret	   
morse_flash:

cpi r16, 0xff
breq SpecialCase
mov r20,r16;separate high 4 bits and low 4 bits，r20 is used for save length，r16 save morse code
swap r20
andi r20, 0x0f;clearn high 4 bits, keep the length
mov r21,r20
dec r21
inc r20
andi r16, 0x0f; keep the morse code
ldi r24, 0x01

findPoint:; make r24 as a momrse counter, move the "1" in r24 to the highest digit of the morse code
lsl r24
dec r21
brne findPoint

countrolLight:; compare with r24, if it is not 0, then it must be dash, and move r24 to lower digit after each compare
dec r20
breq finish
mov r22,r16
and r22,r24
brne Dash
breq Dot
rjmp countrolLight

Dot:
call leds_on
call delay_short
call leds_off
call delay_long
lsr r24
rjmp countrolLight
Dash:
call leds_on
call delay_long
call leds_off
call delay_long
lsr r24
rjmp countrolLight

SpecialCase:
call leds_off
call delay_long
call delay_long
call delay_long
rjmp finish

finish:

	ret



leds_on:
push r16
ldi r16, 0b00000010
sts S_PORTB, r16
pop r16
ret



leds_off:
push r16
ldi r16, 0b00000000	
sts S_PORTB, r16
pop r16
ret



encode_message:
.set PARAM_OFFSET = 10
push XH
push XL
push YH
push YL
push ZH
push ZL

in YH,SPH
IN YL,SPL
ldd ZH, Y+PARAM_OFFSET+3;MESSAGE02 high
ldd ZL, Y+PARAM_OFFSET+2;MESSAGE02 low
ldd XH, Y+PARAM_OFFSET+1;buffer high
ldd XL, Y+PARAM_OFFSET;buffer low
getOneByte:
lpm r19, Z+; take the one byte string massage from Z to r19, and if it is 0, then it is done
cpi r19, 0x00
breq done
call alphabet_encode

st X+, r0; store the encoded morse code to buffer
rjmp getOneByte
done:
pop ZL
pop ZH
pop YL
pop YH
pop XL
pop XH
	ret	



alphabet_encode:

push ZH
push ZL
ldi r22, 0x01
ldi r23, 0x00; length counter
ldi ZH, high(ITU_MORSE<<1)
ldi ZL, low(ITU_MORSE<<1)
lpm r20, Z+; take the data from ITU
cpi r19, 0x20
breq isSpaces

findTheLetter:; compare the letter from MESSAGE with ITU_MORSE


cp r19, r20
breq encodeTheLetter
lpm r20, Z+
rjmp findTheLetter

encodeTheLetter:;after find the letter, fo to the next byte to find the morse code in string
lpm r20, Z+
cpi r20,0x00
breq doneLetter

cpi r20,0x2D; "-" in ASCII is 2D, so if it is not 2D, then is is "."

brne isDot

add r21, r22
rol r21
add r23, r22
rjmp encodeTheLetter

isDot:
rol r21
add r23, r22
rjmp encodeTheLetter
doneLetter:
ror r21
rol r23
rol r23
rol r23
rol r23
add r23, r21
mov r0, r23
clr r21
clr r23
clr r20
pop ZL
pop ZH

ret	 
isSpaces:; load 0xff if it is space
ldi r24,0xff
mov r0,r24
clr r24
pop ZL
pop ZH

ret

; **********************************************
; **** END OF SECOND "STUDENT CODE" SECTION **** 
; **********************************************


; =============================================
; ==== BEGINNING OF "DO NOT TOUCH" SECTION ====
; =============================================

delay_long:
	rcall delay
	rcall delay
	rcall delay
	ret

delay_short:
	rcall delay
	ret

; When wanting about a 1/5th of second delay, all other
; code must call this function
;
delay:
	rcall delay_busywait
	ret


; This function is ONLY called from "delay", and
; never directly from other code.
;
delay_busywait:
	push r16
	push r17
	push r18

	ldi r16, 0x08
delay_busywait_loop1:
	dec r16
	breq delay_busywait_exit
	
	ldi r17, 0xff
delay_busywait_loop2:
	dec	r17
	breq delay_busywait_loop1

	ldi r18, 0xff
delay_busywait_loop3:
	dec r18
	breq delay_busywait_loop2
	rjmp delay_busywait_loop3

delay_busywait_exit:
	pop r18
	pop r17
	pop r16
	ret



.org 0x1000

ITU_MORSE: 
    .db "a",".-",0,0,0,0,0
	.db "b", "-...", 0, 0, 0
	.db "c", "-.-.", 0, 0, 0
	.db "d", "-..", 0, 0, 0, 0
	.db "e", ".", 0, 0, 0, 0, 0, 0
	.db "f", "..-.", 0, 0, 0
	.db "g", "--.", 0, 0, 0, 0
	.db "h", "....", 0, 0, 0
	.db "i", "..", 0, 0, 0, 0, 0
	.db "j", ".---", 0, 0, 0
	.db "k", "-.-", 0, 0, 0, 0
	.db "l", ".-..", 0, 0, 0
	.db "m", "--", 0, 0, 0, 0, 0
	.db "n", "-.", 0, 0, 0, 0, 0
	.db "o", "---", 0, 0, 0, 0
	.db "p", ".--.", 0, 0, 0
	.db "q", "--.-", 0, 0, 0
	.db "r", ".-.", 0, 0, 0, 0
	.db "s", "...", 0, 0, 0, 0
	.db "t", "-", 0, 0, 0, 0, 0, 0
	.db "u", "..-", 0, 0, 0, 0
	.db "v", "...-", 0, 0, 0
	.db "w", ".--", 0, 0, 0, 0
	.db "x", "-..-", 0, 0, 0
	.db "y", "-.--", 0, 0, 0
	.db "z", "--..", 0, 0, 0
	.db 0, 0, 0, 0, 0, 0, 0, 0

MESSAGE01: .db "a a a", 0
MESSAGE02: .db "sos", 0
MESSAGE03: .db "a box", 0
MESSAGE04: .db "dairy queen", 0
MESSAGE05: .db "the shape of water", 0, 0
MESSAGE06: .db "top gun maverick", 0, 0
MESSAGE07: .db "obi wan kenobi", 0, 0
MESSAGE08: .db "oh canada our own and native land", 0
MESSAGE09: .db "is that your final answer", 0

; First message ever sent by Morse code (in 1844)
MESSAGE10: .db "what god hath wrought", 0


.dseg
.org 0x200
BUFFER01: .byte 128
BUFFER02: .byte 128
TESTBUFFER: .byte 4

; =======================================
; ==== END OF "DO NOT TOUCH" SECTION ====
; =======================================
