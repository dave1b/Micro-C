/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         Exercise 02 - GPIO Assembler
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          18.02.2018
 *
 *--------------------------------------------------------------------
 */

    .equ GPIOB_PDOR, 0x400FF040 // Port B, Port Data Output Register
    .equ GPIOB_PSOR, 0x400FF044 // Port B, Port Set Output Register
    .equ GPIOB_PCOR, 0x400FF048 // Port B, Port Clear Output Register
    .equ GPIOB_PTOR, 0x400FF04C // Port B, Port Toggle Output Register
    .equ GPIOB_PDIR, 0x400FF050 // Port B, Port Data Input Register
    .equ GPIOB_PDDR, 0x400FF054 // Port B, Port Data Direction Register

    .equ GPIOC_PDOR, 0x400FF080 // Port C, Port Data Output Register
    .equ GPIOC_PSOR, 0x400FF084 // Port C, Port Set Output Register
    .equ GPIOC_PCOR, 0x400FF088 // Port C, Port Clear Output Register
    .equ GPIOC_PTOR, 0x400FF08C // Port C, Port Toggle Output Register
    .equ GPIOC_PDIR, 0x400FF090 // Port C, Port Data Input Register
    .equ GPIOC_PDDR, 0x400FF094 // Port C, Port Data Direction Register

    .equ GPIOD_PDOR, 0x400FF0C0 // Port D, Port Data Output Register
    .equ GPIOD_PSOR, 0x400FF0C4 // Port D, Port Set Output Register
    .equ GPIOD_PCOR, 0x400FF0C8 // Port D, Port Clear Output Register
    .equ GPIOD_PTOR, 0x400FF0CC // Port D, Port Toggle Output Register
    .equ GPIOD_PDIR, 0x400FF0D0 // Port D, Port Data Input Register
    .equ GPIOD_PDDR, 0x400FF0D4 // Port D, Port Data Direction Register

    .equ PORTB_PCR1, 0x4004A004 // Port B, Port Control Register Pin 1
    .equ PORTB_PCR2, 0x4004A008 // Port B, Port Control Register Pin 2
    .equ PORTB_PCR3, 0x4004A00C // Port B, Port Control Register Pin 3

    .equ PORTC_PCR8, 0x4004B020 // Port C, Port Control Register Pin 8
    .equ PORTC_PCR9, 0x4004B024 // Port C, Port Control Register Pin 9
    .equ PORTC_PCR10, 0x4004B028 // Port C, Port Control Register Pin 10

    .syntax unified
    .arch armv7-m

    .text
    .thumb

    .thumb_func
    .align 2
    .globl   main
    .weak    main
    .type    main, %function

main_:
    ldr     r1, =0x100          // load the MUX value 0x100 (GPIO) into r1
    ldr     r0, =PORTC_PCR8     // load adr of PORTC_PCR8 into r0
    str     r1, [r0]            // store the content of r1 into PORTC_PCR8
    ldr     r0, =PORTC_PCR9     // load adr of PORTC_PCR9 into r0
    str     r1, [r0]            // store the content of r1 into PORTC_PCR9
    ldr     r0, =PORTC_PCR10    // load adr of PORTC_PCR10 into r0
    str     r1, [r0]            // store the content of r1 into PORTC_PCR10

    ldr     r1, =0x103          // load the MUX value 0x100 (GPIO, Pull-Up, Pull-Enable) into r1
    ldr     r0, =PORTB_PCR1     // load adr of PORTB_PCR1 into r0
    str     r1, [r0]            // store the content of r1 into PORTB_PCR1
    ldr     r0, =PORTB_PCR2     // load adr of PORTB_PCR2 into r0
    str     r1, [r0]            // store the content of r1 into PORTB_PCR2
    ldr     r0, =PORTB_PCR3     // load adr of PORTB_PCR3 into r0
    str     r1, [r0]            // store the content of r1 into PORTB_PCR3

    ldr     r0, =GPIOC_PDDR     // load adr of GPIO C, Port Data Direction Register
    ldr     r1, =0x0700         // load bitmask for Bit8, Bit9 and Bit10
    str     r1, [r0]            // store content of r1 into GPIOC_PDDR (adr is in r0)

loop1:
    ldr     r0, =GPIOB_PDIR     // load adr of GPIO B, Port Data Input Register
    ldr     r1, [r0]            // load the value of GPIOB_PDIR into r1
  //lsl r1, r1, #7              // r1 = r1 << 7
    lsl r1, #7                  // r1 <<= 7, logical shift left 7 bits
 //   mvn     r1, r1              // negate register r1
    ldr     r2, =GPIOC_PDOR     // load adr of GPIO C, Port Data Output Register
    str     r1, [r2]            // store the content of r1 into GPIOC_PDOR
    b       loop1


end:    // loop forever
    b      end
