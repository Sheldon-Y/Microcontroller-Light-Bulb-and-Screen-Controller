; main.asm for Hamming assignment
;
; CSC 230: Summer 2022
;
; Code provided for Assignment #1
;
; Mike Zastre (2022-May-18)

; This skeleton of an assembly-language program is provided to help you
; begin with the programming task for A#1, part (a). In this and other
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
;
; Your task: To compute the Hamming distance between two byte values,
; one in R16, the other in R17. If the first byte is:
;    0b10101101
; and the second byte is:
;    0b10010111
; then the Hamming distance -- that is, the number of corresponding
; bits that are different -- would be 4 (i.e., here bits 5, 4, 3,
; and 1 are different).
;
; In your code, store the computed Hamming-distance value in DISTANCE.
;
; Your solution is free to modify the original values in R16
; and R17.

    
	
	.cseg
    .org 0

; ==== END OF "DO NOT TOUCH" SECTION ==========
	ldi r16, 0x8d
	ldi r17, 0x97

; **** BEGINNING OF "STUDENT CODE" SECTION **** 

ldi r31, 0x01
ldi r28, 0x09 ; set a counter to traverse all 8 bits
mov r19, r16
EOR r19,r17; use xor to find different bits between 0x8d and 0x97
countOnes:
mov r18,r19
dec r28
breq end; jump out when traversed all 8 bits
andi r18,0x01; use AND to isolate the last digit
add r27, r18; add the last digit to r27
ror r19; shift to right one
rjmp countOnes
end:
sts DISTANCE,r27 ; store the result into DISTANCE



; **** END OF "STUDENT CODE" SECTION ********** 

; ==== BEGINNING OF "DO NOT TOUCH" SECTION ====
stop:
    rjmp stop

    .dseg
    .org 0x202
DISTANCE: .byte 1  ; result of computing Hamming distance of r16 & r17
; ==== END OF "DO NOT TOUCH" SECTION ==========
