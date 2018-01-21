#include <XBee.h>
#include <SoftwareSerial.h>
#include "pitches.h"  

// XBee's DOUT (TX) is connected to MEGA RX1 (Arduino's Software RX)
// XBee's DIN (RX) is connected to MEGA TX1 (Arduino's Software TX)

XBee xbee = XBee();
ZBRxResponse rx = ZBRxResponse();

#define ROUTER_PIN 10
#define BUZZER_PIN 8

//notes in the melody
int melody[]={NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
//digital pin 12 has a button attached to it. Give it an name

//note durations. 4=quarter note / 8=eighth note
int noteDurations[]={4, 8, 8, 4, 4, 4, 4, 4};

void setup()
{
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  Serial.begin(9600);   //USB
  Serial1.begin(9600);  //XBee/UART1/pins TX1 RX1
  xbee.setSerial(Serial1);
  Serial.println("Sending PING to Corrdinator..."); 
  
  pinMode(ROUTER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  String sample;
  
  // Encapsulate the message with 64 bits target address
  uint8_t data[] = {'R','E','A','D','Y'};
  XBeeAddress64 addr64 = XBeeAddress64();
  addr64.setMsb(0x0013a200);//XXXXX -> Msb address of router/end node
  addr64.setLsb(0x41637ee1);//XXXXX -> Lsb address of router/end node 
  ZBTxRequest zbTx = ZBTxRequest(addr64, data, sizeof(data));
  
  // Sending PING message to coordinator
  xbee.send(zbTx);

  // Wait to receive the interrupt message from remote radio
  xbee.readPacket();
  if(xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)
    {
      Serial.println("Data shows up!");
      xbee.getResponse().getZBRxResponse(rx);
      for (int i = 0; i < rx.getDataLength(); i++) {
        sample += (char)rx.getData(i);
      }
      Serial.println(sample);
      if (sample == "RING") {
        melodyOutput(BUZZER_PIN, HIGH);
      }
    } else if (xbee.getResponse().isError()) {
      Serial.print("Error reading packet. Error code is ");
      Serial.println(xbee.getResponse().getErrorCode());
    } // end (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)
  
  } // end if(xbee.getResponse().isAvailable())  
}

void melodyOutput(byte pin, volatile byte state) {
    // ensure state is high to turn on melody
    if (state != HIGH) {
        return; 
    }

    //iterate over the notes of the melody
    for (int thisNote=0; thisNote <8; thisNote++){

      //to calculate the note duration, take one second. Divided by the note type
      int noteDuration = 1000 / noteDurations [thisNote];
      tone(pin, melody [thisNote], noteDuration);

      //to distinguish the notes, set a minimum time between them
      //the note's duration +30% seems to work well
      int pauseBetweenNotes = noteDuration * 1.30;
      digitalWrite(ROUTER_PIN, HIGH);
      delay(pauseBetweenNotes);
      digitalWrite(ROUTER_PIN, LOW);

      //stop the tone playing
      noTone(pin);
    }
}
