#include <SoftwareSerial.h>
// XBee's DOUT (TX) is connected to MEGA RX1 (Arduino's Software RX)
// XBee's DIN (RX) is connected to MEGA TX1 (Arduino's Software TX)

#define XBee Serial1

void setup()
{
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(9600);  //XBee/UART1/pins TX1 RX1
  Serial.begin(9600);   //USB
  XBee.write("Hello from Mega Router!");
  
}

void loop()
{
  if (Serial.available()) //USB
  { 
    // If data comes in from serial monitor, send it out to XBee
    XBee.write(Serial.read()); //XBee/UART1/pins 0 and 1
  }
  if (XBee.available())   //XBee/UART1/pins 0 and 1
  { 
    // If data comes in from XBee, send it out to serial monitor
    Serial.write(XBee.read());  //Serial port
  }
}
