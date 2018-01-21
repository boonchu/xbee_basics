/**
   Copyright (c) 2015 Matthijs Kooijman

   This file is part of XBee-Arduino.

   XBee-Arduino is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   XBee-Arduino is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the * GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with XBee-Arduino.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <XBee.h>
#include <Printers.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <string.h>

#define ssRxPin 4
#define ssTxPin 5

// Setup XBee variables
SoftwareSerial nss(ssRxPin, ssTxPin);

/*
  This example is for Series 1 and 2 XBee (no changes needed for either).
  It listens for incoming packets and echoes back any data received back
  to the sender. This example shows how to use XBeeWithCallbacks to
  concisely express reading of response packets.
  This example assumes an Arduino with two serial ports (like the
  Leonardo or Mega). Replace Serial and Serial1 below appropriately for
  your hardware.
*/

XBee xbee = XBee();
ZBRxIoSampleResponse ioSample = ZBRxIoSampleResponse();
XBeeAddress64 test = XBeeAddress64();

void setup() { 
  Serial.begin(9600);
  nss.begin(9600);
  xbee.setSerial(nss);
  delay(9000);
}

void loop() {
  //attempt to read a packet    
  xbee.readPacket();

  if (xbee.getResponse().isAvailable()) {
    // got something

    if (xbee.getResponse().getApiId() == ZB_IO_SAMPLE_RESPONSE) {
      xbee.getResponse().getZBRxIoSampleResponse(ioSample);

      Serial.print("Received I/O Sample from: ");
      
      Serial.print(ioSample.getRemoteAddress64().getMsb(), HEX);  
      Serial.print(ioSample.getRemoteAddress64().getLsb(), HEX);  
      Serial.println("");
      
      if (ioSample.containsAnalog()) {
        Serial.println("Sample contains analog data");
      }

      if (ioSample.containsDigital()) {
        Serial.println("Sample contains digtal data");
      }      

      // read analog inputs
      for (int i = 0; i <= 4; i++) {
        if (ioSample.isAnalogEnabled(i)) {
          Serial.print("Analog (AI");
          Serial.print(i, DEC);
          Serial.print(") is ");
          Serial.println(ioSample.getAnalog(i), DEC);
        }
      }

      // check digital inputs
      for (int i = 0; i <= 12; i++) {
        if (ioSample.isDigitalEnabled(i)) {
          Serial.print("Digital (DI");
          Serial.print(i, DEC);
          Serial.print(") is ");
          Serial.println(ioSample.isDigitalOn(i), DEC);
        }
      }
      
      // method for printing the entire frame data
      for (int i = 0; i < xbee.getResponse().getFrameDataLength(); i++) {
          Serial.print(xbee.getResponse().getFrameData()[i], HEX);
          Serial.print(" ");
      }
      Serial.println("");
    } 
    else {
      Serial.print("Expected I/O Sample, but got ");
      Serial.print(xbee.getResponse().getApiId(), HEX);
    }    
  } else if (xbee.getResponse().isError()) {
    Serial.print("Error reading packet.  Error code: ");  
    Serial.println(xbee.getResponse().getErrorCode());
  }
}
