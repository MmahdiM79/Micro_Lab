

PIO_per EQU 0x400E0E00;
PIO_sodr EQU 0x400E0E30;
PIO_codr EQU 0x400E0E34;
PIO_pudr EQU 0x400E0E60;
PIO_oer EQU 0x400E0E10;
PIO_odr EQU 0x400E0E14;
PIO_rehlsr EQU 0x400E0ED4;
PIO_lsr EQU 0x400E0EC4;
PIO_aimer EQU 0x400E0EB0;
PIO_isr EQU 0x400E0E4C;
PIO_ifdr EQU 0x400E0E24;
PIO_odsr EQU 0x400E0E38;



	AREA codes, CODE, READONLY
	EXPORT __main
	entry
	
__main
	BL set_pins;
	
	MOV r6, #0;
	
	BL led_off;
	MOV r11, #2_01000;
	MOV r12, #2_10000;
	
loop
	LDR r9, =PIO_isr;
	LDR r10, [r9];
	CMP r10, r11;
	BEQ turn_on;
	BL next;
turn_on
	MOV r6, #1;

next
	LDR r9, =PIO_isr;
	LDR r10, [r9];
	CMP r10, r12;
	BEQ turn_off;
	BL set;
turn_off
	MOV r6, #0;
	
set
	CMP r6, #1;
	BEQ led_on;
	BL led_off;
	
end_loop
	B loop;
		
here B here;
	
	
		
set_pins
	MOV r4, #2_00111;
	LDR r5, =PIO_per;
	STR r4, [r5];
	
	MOV r4, #2_11111;
	LDR r5, =PIO_pudr;
	STR r4, [r5];
	
	MOV r4, #2_00111;
	LDR r5, =PIO_oer;
	STR r4, [r5];
	
	MOV r4, #2_11000;
	LDR r5, =PIO_odr;
	STR r4, [r5];
	
	MOV r4, #2_11000;
	LDR r5, =PIO_ifdr;
	STR r4, [r5];
	
	MOV r4, #2_11000;
	LDR r5, =PIO_rehlsr;
	STR r4, [r5];
	
	MOV r4, #2_11000;
	LDR r5, =PIO_lsr;
	STR r4, [r5];
	
	MOV r4, #2_11000;
	LDR r5, =PIO_aimer;
	STR r4, [r5];
	
	BX lr;
	
	
	
led_on
	ADD r7, r7, #1;
	
	LDR r5, =PIO_odsr;
	STR r7, [r5];
	BL delay;
	
	LDR r5, =PIO_codr;
	STR r7, [r5];
	BL delay;
	
	LDR r5, =PIO_sodr;
	STR r7, [r5];
	BL delay;
	
	BL end_loop;
	
	
	
led_off
	MOV r4, #2_00111;
	
	LDR r5, =PIO_codr;
	STR r4, [r5];
	
	MOV r7, #0;
	
	BX lr;
	
	
	
delay
	MOV r4, #0;
	LDR r5, =0x0015000;
	
delay_loop
	ADD r4, r4, #1;
	
	CMP r4, r5;
	BNE delay_loop;
	
	BX lr;
	
	
	
	end;
	
	
	
	