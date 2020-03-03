/*
  Joakim Wesslen
  2012-06-26

  A library to handle the TX433 Proove/Anslut device.
  Version 1.0

  http://tech.jolowe.se/home-automation-rf-protocols/  
*/
#include "tx433.h"

extern "C" {
  // AVR LibC Includes
  #include <inttypes.h>
  #include <avr/interrupt.h>
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif
}

#define RETRANSMIT  5
const int Tx433::pulse_high = 250;
const int Tx433::pulse_one_low = 250;
const int Tx433::pulse_zero_low = 1250;
const int Tx433::pulse_sync_low = 2500;
const int Tx433::pulse_pause_low = 10000;

byte Tx433::GROUP_ON = B01;
byte Tx433::GROUP_OFF = B10;
byte Tx433::ON = B01;
byte Tx433::OFF = B10;
byte Tx433::UNIT[] = {
    B0101,
    B0110,
    B1001,
    B0101
};

/* Public */

Tx433::Tx433(byte digitalpin, byte transmittercode, byte channelcode) {
	txpin = digitalpin;
	pinMode(txpin, OUTPUT);

	TxCode = transmittercode;
	ChCode = channelcode;
}

void Tx433::On(byte dev) {
	if ( dev >= 3 ) {
		sendPackets(GROUP_ON, UNIT[3], ON);
	} else {
		sendPackets(GROUP_OFF, UNIT[dev], ON);
	}
}	  

void Tx433::Off(byte dev) {
	if (dev >= 3) {
		sendPackets(GROUP_ON, UNIT[3], OFF);
	} else {
		sendPackets(GROUP_OFF, UNIT[dev], OFF);
    	}
}	  

byte Tx433::Get_txpin(void) {
	return txpin;
}

byte Tx433::Get_TxCode(void) {
	return TxCode;
}	  

byte Tx433::Get_ChCode(void) {
	return ChCode;
}	  

/* Private */

// Protocol layer
void Tx433::sendCode(byte str, byte len) {
  for ( byte i = 0; i < len; i++ ) {
    byte a = str&(1<<(len-1-i));
    if ( a == 0 ) {
      sendZero();
    } else {
      sendOne();
    }
  }
}

void Tx433::sendPackets(byte grp, byte dev, byte onoff) {
  for ( byte i = 0; i < RETRANSMIT; i++ ) {
	  sendSync();
	  sendCode(B11111111, 8);
	  sendCode(B11111111, 8);
	  sendCode(B11111111, 8);
	  sendCode(B11111111, 8);
	  sendCode(B11111111, 8);
	  sendCode(B1111, 4);
	  sendCode(TxCode, 8);
	  sendCode(grp, 2);
	  sendCode(onoff, 2);
	  sendCode(ChCode, 4);
	  sendCode(dev, 4);
	  sendPause();
  }
}

// Physical layer
void Tx433::sendZero() {
  digitalWrite(txpin, HIGH);
  delayMicroseconds(pulse_high);
  digitalWrite(txpin, LOW);
  delayMicroseconds(pulse_zero_low);
}

void Tx433::sendOne() {
  digitalWrite(txpin, HIGH);
  delayMicroseconds(pulse_high);
  digitalWrite(txpin, LOW);
  delayMicroseconds(pulse_one_low);
}

void Tx433::sendSync() {
  digitalWrite(txpin, HIGH);
  delayMicroseconds(pulse_high);
  digitalWrite(txpin, LOW);
  delayMicroseconds(pulse_sync_low);
}

void Tx433::sendPause() {
  digitalWrite(txpin, HIGH);
  delayMicroseconds(pulse_high);
  digitalWrite(txpin, LOW);
  delayMicroseconds(pulse_pause_low);
}