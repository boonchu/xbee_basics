/**
   Copyright (c) 2017 Boonchu Ngampairoijpibul
   This file is part of XBee-Arduino.

   XBee-Arduino is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   XBee-Arduino is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
   
   See the * GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with XBee-Arduino.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <XBee.h>
#include <Printers.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
  Serial.println("Cooridinator is ready");
}

void loop() {
  //attempt to read a packet    
  xbee.readPacket();

  if (xbee.getResponse().isAvailable()) {
    // got something

    if (xbee.getResponse().getApiId() == ZB_IO_SAMPLE_RESPONSE) {
      xbee.getResponse().getZBRxIoSampleResponse(ioSample);      
      
      if (ioSample.containsAnalog()) {

        #define ADC_RESOLUTION        10240000
        #define DEFAULT_ADC_PIN       0
        #define DEFAULT_NOMINAL_RES   10000       
          
        float sample = 0;
                  
        // read analog inputs
        if (ioSample.isAnalogEnabled(DEFAULT_ADC_PIN)) {          
          sample = ioSample.getAnalog(DEFAULT_ADC_PIN);
          Serial.print("Analog A0 reads value: ");
          Serial.println(sample, DEC);

          // convert value to resistance for 10 bits resolution
          sample = (ADC_RESOLUTION/sample)*(1200/1023) - DEFAULT_NOMINAL_RES;

          // shows thermistor resistance
          Serial.print("Thermistor resistance value: ");
          Serial.println(sample);

          // https://github.com/ItKindaWorks/libraries/blob/master/Thermistor/Thermistor.cpp
          // Steinhart-Hart equation
          /******************************************************************/
          /* Utilizes the Steinhart-Hart Thermistor Equation:               */
          /*    Temperature in Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]^3}     */
          /*    where A = 0.001129148, B = 0.000234125 and C = 8.76741E-08  */
          /******************************************************************/
          double Temp;

          Temp = logf(sample);                  // ln(analog_resistance)
          Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
          Temp = Temp - 273.15;  // Convert Kelvin to Celsius


          Serial.print("Temperature "); 
          Serial.print(Temp);
          Serial.println(" *C");
          
          // Serial.print("Temperature: "); 
          // Serial.print(t1);
          // Serial.println(" C"); 
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
