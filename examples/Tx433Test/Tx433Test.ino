/*
  Example of using the Tx433 lib to control Home Automation power outlet sockets
*/

#include <tx433.h>

// Replace these bytes with appropriate code/pattern for your devices
byte tx_proove = B11111111;
//byte tx_anslut = B00000000;

byte ch_proove = B0101;
//byte ch_anslut = B0101;

Tx433 Proove(3, tx_proove, ch_proove);
//Tx433 Anslut(3, tx_anslut, ch_anslut);

void setup() {
}

void loop() {
  Proove.On(2);
  delay(1000);
  Proove.Off(2);
  delay(1000);
  Proove.On(0);
  delay(1000);
  Proove.Off(0);
  delay(1000);
}
