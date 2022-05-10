/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         System initialization and utils.
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          16.02.2020
 *
 *--------------------------------------------------------------------
 */
#include "MK22F51212.h"
#include "system.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"

extern char _vStackTop[];
extern char _vStackBase[];
extern unsigned int _StackSize;

#define SEMIHOSTING 0


void SystemInitHook(void)
{
  __asm(
     /* Dieser Block füllt den Stack mit dem Muster 0x55 / joc 29.02.2020 */
    "ldr     r1, =_vStackBase\n"      /* bottom of stack (kleinste Adresse) */
 /* "ldr     r2, =_vStackTop\n"*/     /* top of stack (grösste Adresse) */
    "mov     r2, sp\n"                /* aktuelle sp Wert ~top of stack (grösste Adresse) */
    "subs    r2, r1\n"                /* r2 = size = top - bottom */
    "subs    r2, 4\n"                 /* r2 = r2 - 4 */
    "ldr     r0, =0x55555555\n"
  ".Loop0:\n"
    "str     r0, [r1, r2]\n"          /* speichere r0 (0x55555555) an adr r1 + r2 */
    "subs    r2, 4\n"                 /* r2 = r2 - 4 */
    "bge     .Loop0\n"                /* springe falls >=0 zu Loop0 */
  ".endLoop0:\n");

  // Clock Gating
  SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK  | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
}


/**
 * This function checks the size of the used stack
 *
 * @return information about the used and free stack size
 */
tStackData utilCheckStackSize(void)
{
  char* i;
  int stackSize = _vStackTop - _vStackBase;
  tStackData stackData;
  stackData.stackFree = 0;
  stackData.stackUsed = stackSize;
  for (i=_vStackBase; i<_vStackTop; i++)
  {
    if (*i == 0x55) stackData.stackFree++;
    else break;
  }
  stackData.stackUsed -= stackData.stackFree;
  return stackData;
}


/**
 * Init system before main is calling
 */
void systemPostInit(void)
{
  /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
}


#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
void McuHardFault_HandlerC(uint32_t *hardfault_args)
{
  /*lint -save  -e550 Symbol not accessed. */
  static volatile unsigned long stacked_r0;
  static volatile unsigned long stacked_r1;
  static volatile unsigned long stacked_r2;
  static volatile unsigned long stacked_r3;
  static volatile unsigned long stacked_r12;
  static volatile unsigned long stacked_lr;
  static volatile unsigned long stacked_pc;
  static volatile unsigned long stacked_psr;
  static volatile unsigned long _CFSR;
  static volatile unsigned long _HFSR;
  static volatile unsigned long _DFSR;
  static volatile unsigned long _AFSR;
  static volatile unsigned long _BFAR;
  static volatile unsigned long _MMAR;
  stacked_r0 = ((unsigned long)hardfault_args[0]);
  stacked_r1 = ((unsigned long)hardfault_args[1]);
  stacked_r2 = ((unsigned long)hardfault_args[2]);
  stacked_r3 = ((unsigned long)hardfault_args[3]);
  stacked_r12 = ((unsigned long)hardfault_args[4]);
  stacked_lr = ((unsigned long)hardfault_args[5]);
  stacked_pc = ((unsigned long)hardfault_args[6]);
  stacked_psr = ((unsigned long)hardfault_args[7]);

  /* Configurable Fault Status Register */
  /* Consists of MMSR, BFSR and UFSR */
  _CFSR = (*((volatile unsigned long *)(0xE000ED28)));

  /* Hard Fault Status Register */
  _HFSR = (*((volatile unsigned long *)(0xE000ED2C)));

  /* Debug Fault Status Register */
  _DFSR = (*((volatile unsigned long *)(0xE000ED30)));

  /* Auxiliary Fault Status Register */
  _AFSR = (*((volatile unsigned long *)(0xE000ED3C)));    //                             oooo$$$$$$$$$$$$oooo
                                                          //                          oo$$$$$$$$$$$$$$$$$$$$$$$$o
                                                          //                        oo$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o         o$   $$ o$
  /* Read the Fault Address Registers. */                 //        o $ oo        o$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o       $$ $$ $$o$
  /* These may not contain valid values. */               //     oo $ $ "$      o$$$$$$$$$    $$$$$$$$$$$$$    $$$$$$$$$o       $$$o$$o$
  /* Check BFARVALID/MMARVALID to see */                  //     "$$$$$$o$     o$$$$$$$$$      $$$$$$$$$$$      $$$$$$$$$$o    $$$$$$$$
  /* if they are valid values */                          //       $$$$$$$    $$$$$$$$$$$      $$$$$$$$$$$      $$$$$$$$$$$$$$$$$$$$$$$
  /* MemManage Fault Address Register */                  //       $$$$$$$$$$$$$$$$$$$$$$$    $$$$$$$$$$$$$    $$$$$$$$$$$$$$  """$$$
  _MMAR = (*((volatile unsigned long *)(0xE000ED34)));    //        "$$$""""$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     "$$$
  /* Bus Fault Address Register */                        //         $$$   o$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     "$$$o
  _BFAR = (*((volatile unsigned long *)(0xE000ED38)));    //        o$$"   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$       $$$o
                                                          //        $$$    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" "$$$$$$ooooo$$$$o
  __asm("BKPT #0\n") ; /* cause the debugger to stop */   //       o$$$oooo$$$$$  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   o$$$$$$$$$$$$$$$$$
  /*lint -restore */                                      //       $$$$$$$$"$$$$   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     $$$$""""""""
} /*                                                              """"       $$$$    "$$$$$$$$$$$$$$$$$$$$$$$$$$$$"      o$$$
                                                                             "$$$o     """$$$$$$$$$$$$$$$$$$"$$"         $$$
                                                                               $$$o          "$$""$$$$$$""""           o$$$
                                                                                $$$$o                                o$$$"
                                                                                 "$$$$o      o$$$$$$o"$$$$o        o$$$$
                                                                                   "$$$$$oo     ""$$$$o$$$$$o   o$$$$""
                                                                                      ""$$$$$oooo  "$$$o$$$$$$$$$"""
                                                                                         ""$$$$$$$oo $$$$$$$$$$
                                                                                                 """"$$$$$$$$$$$
                                                                                                     $$$$$$$$$$$$
                                                                                                      $$$$$$$$$$"
                                                                                                       "$$$""


                                                                                       C R A S H   B O O M   B A N G . . .

                                                                                  http://www.asciiworld.com/-Smiley,20-.html */

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
__attribute__((naked)) void HardFault_Handler(void)
{
  // append printf fallback to jTAG - default handeling defined by MCUXpresso
  __asm(  ".syntax unified\n"
	  // Check which stack is in use
		  "MOVS   R0, #4  \n"
		  "MOV    R1, LR  \n"
		  "TST    R0, R1  \n"
		  "BEQ    _MSP    \n"
		  "MRS    R0, PSP \n"
		  "B  _process      \n"
		  "_MSP:  \n"
		  "MRS    R0, MSP \n"
	  // Load the instruction that triggered hard fault
	  "_process:     \n"
		  "LDR    R1,[R0,#24] \n"
		  "LDRH    R2,[r1] \n"
	  // Semihosting instruction is "BKPT 0xAB" (0xBEAB)
		  "LDR    R3,=0xBEAB \n"
		  "CMP     R2,R3 \n"
		  "BEQ    _semihost_return \n"
	  // Wasn't semihosting instruction so enter infinite loop
		  "B . \n"
	  // Was semihosting instruction, so adjust location to
	  // return to by 1 instruction (2 bytes), then exit function
	  "_semihost_return: \n"
		  "ADDS    R1,#2 \n"
		  "STR    R1,[R0,#24] \n"
	// Set a return value from semihosting operation.
	// 32 is slightly arbitrary, but appears to allow most
	// C Library IO functions sitting on top of semihosting to
	// continue to operate to some degree
			"MOVS   R1,#32 \n"
			"STR R1,[ R0,#0 ] \n" // R0 is at location 0 on stack
	// Return from hard fault handler to application
		  "BX LR \n"
	  ".syntax divided\n") ;
}
