// This sketch will cause an XBee radio attached to the Arduino to
// listen for requests from another XBee radio. It will take the
// payload received by the XBee and add it to a dynamically allocated
// array of strings (character arrays). It will attempt to grow the 
// array holding the strings as it adds them.

// In order to use this sketch, the XBee radio (Series 1 used here)
// must be setup to use API mode (AP=2 in X-CTU).
// I use pins 2 and 3 here, but those can be changed in the defines
// below.

#include <XBee.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <string.h>

#define ssRxPin 2
#define ssTxPin 3

// Setup XBee variables
SoftwareSerial nss(ssRxPin, ssTxPin);
XBee xbee = XBee();
ZBRxResponse rx = ZBRxResponse();

void setup()
{
  Serial.begin(9600);
  nss.begin(9600);
  xbee.setSerial(nss);
  Serial.println("Wait to receive data from Router..."); 
}

void loop()
{
  String sample;
  
  // Read data from the XBee
  xbee.readPacket();
  if(xbee.getResponse().isAvailable())
  {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)
    {
      xbee.getResponse().getZBRxResponse(rx);
      for (int i = 0; i < rx.getDataLength(); i++) {
        sample += (char)rx.getData(i);
      }
      Serial.println(sample);            
    } else if (xbee.getResponse().isError()) {
      Serial.print("Error reading packet. Error code is ");
      Serial.println(xbee.getResponse().getErrorCode());
    } // end (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)
  
  } // end if(xbee.getResponse().isAvailable())

}

