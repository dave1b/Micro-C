/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         Infrared Remote Control driver
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          14.04.2020
 *
 *--------------------------------------------------------------------
 */
#include "platform.h"
#include "ftm0.h"
#include "ir.h"


/**
 * Sets a bit of the @ref rxBuf to '1'
 *
 * @param[in] buf
 *      the desired buffer to set the bit
 * @param[in] bytePos
 *      the desired byte [0..(rxBufSize - 1)]
 * @param[in] bitPos
 *      the desired bit [0...7]
 */
#define set_rx_bit(buf, bytePos, bitPos)      (buf[bytePos] |= (1 << bitPos))

/**
 * Sets a bit of the @ref rxBuf to '0'
 *
 * @param[in] buf
 *      the desired buffer to clear the bit
 * @param[in] bytePos
 *      the desired byte [0..(rxBufSize - 1)]
 * @param[in] bitPos
 *      the desired bit [0...7]
 */
#define clear_rx_bit(buf, bytePos, bitPos)    (buf[bytePos] &= ~(1 << bitPos))


typedef enum
{
  rxIdle,
  rxReceiving,
  rxReceived
} rxStates;

typedef enum
{
  rxStartBit,
  rxRStartBit,
  rx1Bit,
  rx0Bit
} rxBits;

typedef union
{
  uint8_t buf[4];
  struct
  {
    uint16_t adr;
    uint8_t cmd;
    uint8_t cmdN;
  } cmd;
} tCommand;

#define rxBuf     (rxCommand.buf)
static tCommand rxCommand;
static rxStates rxState;


/**
 * This function processes the state machine to receive an IR-command.
 * After every measurement of a pulse and the following pause this
 * function has to be called.
 *
 * @param[in] pulse
 *   the pulse time in timer ticks
 * @param[in] pause
 *   the pause time in timer ticks
 */
void ir_process_receive_state_machine(uint16_t pulse, uint16_t pause)
{
  static uint8_t bitPos = 0;
  static uint8_t bytePos = 0;
  rxBits rxBit;

  // determine the right bit based on the pulse/pause time:
  // startbit, repeated startbit, '1' or '0'
  if (pulse > PULSE_LEN_MIN && pulse < PULSE_LEN_MAX) // pulse ~560us
  {
    if (pause > PAUSE_0_LEN_MIN && pause < PAUSE_0_LEN_MAX) rxBit = rx0Bit;     // pause ~560us
    else if (pause > PAUSE_1_LEN_MIN && pause < PAUSE_1_LEN_MAX)rxBit = rx1Bit; // pause ~1690us
  }
  else if (pulse > START_BIT_PULSE_LEN_MIN && pulse < START_BIT_PULSE_LEN_MAX) // pulse ~9ms
  {
    if (pause > START_BIT_PAUSE_LEN_MIN && pause < START_BIT_PAUSE_LEN_MAX) rxBit = rxStartBit;         // pause ~4500us
    else if (pause > RSTART_BIT_PAUSE_LEN_MIN && pause < RSTART_BIT_PAUSE_LEN_MAX) rxBit = rxRStartBit; // pause ~2250us
  }

  switch (rxState)
  {
  case rxIdle:                                  // idle state
    if (rxBit == rxStartBit) {                  // wait until a valid StartBit has been received
      bitPos = bytePos = 0;                     // startbit received => reset buffer index variables
      rxState = rxReceiving;                    // and change to the rxReceiving state
    }
    else if (rxBit == rxRStartBit) { }          // Repeated Start is ignored (not implemented)
    break;

  case rxReceiving:                                 // receiving state
    if (rxBit==rxStartBit || rxBit==rxRStartBit) {  // startbit during receiving is an error
      bitPos = bytePos = 0;                         // => reset buffer index variables
    }
    else {
      if (rxBit == rx1Bit) set_rx_bit(rxBuf, bytePos, bitPos);  // '1' received => set '1' in the receive buffer
      else clear_rx_bit(rxBuf, bytePos, bitPos);                // '0' receifed => set '0' in the receive buffer

      if (++bitPos > 7) {                           // 8 bits received => byte is full, process next byte
        bitPos = 0;                                 // bitpos of the next byte is 0
        bytePos++;                                  // process next byte
        if (bytePos >= 4) {                         // if 4 bytes has been received => finished
          if ((rxCommand.cmd.cmd ^ rxCommand.cmd.cmdN) == 0xff) rxState = rxReceived;
          else rxState = rxIdle;                    // more than 4 bytes? => Error => wait in idle state for next startbit
        }
      }
    }
    break;

    case rxReceived: break;                         // IR command received, wait until read with "irGetKey()"
    default: rxState = rxIdle; break;               // invalid state? => change to idle state
  }
}


/**
 * This interrupt service routine measures the pulse and the pause time of the
 * signal of the infrared receiver.
 *
 * After the measurement of a pulse and a pause time, the "irProcessReceiveStateMachine"
 * is called.
 */
void FTM0CH5_IRQHandler(void)
{
  static uint16_t oldTicks = 0;
  static uint16_t pulse, pause;

  OnEnterInfraredISR();             // switch on led for debug purposes
  FTM0->CONTROLS[5].CnSC &= ~FTM_CnSC_CHF_MASK;  // clear timer channel flag

  //for (pause=0; pause<100; pause++); // Forbidden Delay in an ISR - remove this line !!!

  // todo ML#10.2-3 implement the ISR as follows:
  // determine if it is a pulse or a pause (check GPIO-Pin)
  // calculate the pulse or pause time
  // call irProcessReceiveStateMachine(pulse, pause); if it was a pause



  OnExitInfraredISR();              // switch off led for debug purposes
}


/**
 * Returns a key or 0 if no key was pressed.
 */
uint8_t ir_get_key(void)
{
  //volatile uint16_t adr; // not used
  uint8_t cmd = 0;

  if (rxState == rxReceived)
  {
	//adr = rxCommand.cmd.adr;
	switch (rxCommand.cmd.cmd)
	{
	  // todo ML#10.2-4 complete the switch statement. See "ir.h" for Key-Codes
	  case 0x16 : cmd = KeyStar; break;
	  default : cmd = KeyUnknown; break;
	}

    rxState = rxIdle;
  }
  return cmd;
}


/**
 * Initalization of the Infrared driver.
 *
 * On PTD5 is the IR-receiver connected. This function configures this
 * port pin as timer channel (FTM0, Channel 5) and initialize the timer
 * to generate interrupts on every changing edge of the pin.
 */
void ir_init(void)
{
  // todo ML#10.2-1 configure the mux of PTD5 as timer channel.
  // can be done here or with the ConfigTool

  // todo ML#10.2-2 configure the timer channel as follows:
  // Input Capture with enabled interrupt on every changing edge of the pin
  // can be done here or with the ConfigTool
}
