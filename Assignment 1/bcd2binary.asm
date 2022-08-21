; bcd2binary.asm
; CSC 230: Summer 2022
;
; Code provided for Assignment #1
;
; Mike Zastre (2022-May-18)

; This skeleton of an assembly-language program is provided to help you
; begin with the programming task for A#1, part (c). In this and other
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
; Your task: Given a binary-coded decimal (BCD) number stored in
; R16, conver this number into the usual binary representation,
; and store in BCD2BINARY.
;

    .cseg
    .org 0

    .equ TEST1=0x99 ; 99 decimal, equivalent to 0b01100011
    .equ TEST2=0x81 ; 81 decimal, equivalent to 0b01010001
	.equ TEST3=0x20 ; 20 decimal, equivalent to 0b00010100
	 
	ldi r16, TEST1

; ==== END OF "DO NOT TOUCH" SECTION ==========

; **** BEGINNING OF "STUDENT CODE" SECTION **** 
mov r17,r16
andi r17,0xf0; clean the lower 4 bits, and copy it to r17
ldi r18,0x04; loop counter, make sure only move the high 4 bits to low 4 bits
andi r16,0x0f; clean the higher 4 bits, and copy it to r16
move4:; move the higher 4 bits to lower bits
ror r17
dec r18
brne move4
ldi r18, 0x09; set a counter to make sure add 10 times
mov r19,r17
multiply:;multiply r17 by 10 to make r17 to tens place
add r17,r19
dec r18
brne multiply
add r17, r16; add the tens place number with the ones place number
sts BCD2BINARY,r17

; **** END OF "STUDENT CODE" SECTION ********** 

; ==== BEGINNING OF "DO NOT TOUCH" SECTION ====
end:
	rjmp end


.dseg
.org 0x200
BCD2BINARY: .byte 1
; ==== END OF "DO NOT TOUCH" SECTION ==========
