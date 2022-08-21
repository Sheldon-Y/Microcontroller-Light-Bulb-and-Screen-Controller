; reverse.asm
; CSC 230: Summer 2022
;
; Code provided for Assignment #1
;
; Mike Zastre (2022-May-18)

; This skeleton of an assembly-language program is provided to help you
; begin with the programming task for A#1, part (b). In this and other
; files provided through the semester, you will see lines of code
; indicating "DO NOT TOUCH" sections. You are *not* to modify the
; lines within these sections. The only exceptions are for specific
; changes announced on conneX or in written permission from the course
; instructor. *** Unapproved changes could result in incorrect code
; execution during assignment evaluation, along with an assignment grade
; of zero. ****
;
; In a more positive vein, you are expected to place your code with the
; area marked "STUDENT CODE" sections.

; ==== BEGINNING OF "DO NOT TOUCH" SECTION ====
; Your task: To reverse the bits in the word IN1:IN2 and to store the
; result in OUT1:OUT2. For example, if the word stored in IN1:IN2 is
; 0xA174, then reversing the bits will yield the value 0x2E85 to be
; stored in OUT1:OUT2.

    .cseg
    .org 0

; ==== END OF "DO NOT TOUCH" SECTION ==========

; **** BEGINNING OF "STUDENT CODE" SECTION **** 
    ; These first lines store a word into IN1:IN2. You may
    ; change the value of the word as part of your coding and
    ; testing.
    ;

   ldi R16, 0xA1
   sts IN1, R16
	ldi r28, 0x08
	ldi r19, 0x00
	reverse:
	mov r18,r16
	ror r16; shift the oringin numbers to right
    andi r18,0x01; isolate the last bit
	add r19,r18; put the last digit into r19
	dec r28; make sure to traversed all 8 bits
    breq endIN1
	rol r19;after insert the last digit of the origin number, shift to left
	rjmp reverse
    endIN1:
	mov r16,r19
	sts OUT2, R16
	
    
	;do same thing for IN2
	ldi R16, 0x74
    sts IN2, R16
	ldi r28, 0x08
	ldi r19, 0x00
	reverse2:
	mov r18,r16
	ror r16
    andi r18,0x01
	add r19,r18
	dec r28
    breq endIN2
	rol r19
	rjmp reverse2
    endIN2:
	mov r16,r19
	sts OUT1, R16
	

; **** END OF "STUDENT CODE" SECTION ********** 



; ==== BEGINNING OF "DO NOT TOUCH" SECTION ====
stop:
    rjmp stop

    .dseg
    .org 0x200
IN1:	.byte 1
IN2:	.byte 1
OUT1:	.byte 1
OUT2:	.byte 1
; ==== END OF "DO NOT TOUCH" SECTION ==========
