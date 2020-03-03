/*
  Joakim Wesslen
  2012-06-26

  A library to handle the TX433 Proove/Anslut device.
  Version 1.0

  Here is a link to some overview of some different protocols:
  http://tech.jolowe.se/home-automation-rf-protocols/

  The API:s below handles code parameter of the longer format, i.e. with redundancy bits.
*/

#ifndef TX433_H
#define TX433_H

#define LIB_VERSION 1.0

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif

class Tx433
{
  public:
	/*
	@digitalpin - the digitalpin to send data on to transmitter
	@transmittercode - the unique code of the transmitter (26/52 bits)
	@channelcode - the channel code (2/4 bits)
	*/
	Tx433(byte digitalpin, byte transmittercode, byte channelcode);

	/*
	@unit - the device to turn on. 
		0,1,2 are the three separate devices.
		3 is the complete group.
	*/
	void On(byte unit);	  

	/*
	@unit - the device to turn off. 
		0,1,2 are the three separate devices.
		3 is the complete group.
	*/
	void Off(byte unit);	  

	byte Get_txpin(void);
    byte Get_TxCode(void);
    byte Get_ChCode(void);

  private:
	byte txpin;
	
	byte TxCode;
	byte ChCode;
	static byte GROUP_ON;
	static byte GROUP_OFF;
	static byte ON;
	static byte OFF;
	static byte UNIT[];

	const static int pulse_high;
	const static int pulse_one_low;
	const static int pulse_zero_low;
	const static int pulse_sync_low;
	const static int pulse_pause_low;
  
	// Protocol layer
	void sendCode(byte str, byte len);
	void sendPackets(byte grp, byte dev, byte onoff);

	// Physical layer interfaces
	void sendZero(void);
	void sendOne(void);
	void sendSync(void);
	void sendPause(void);
};
#endif	// TX433_H