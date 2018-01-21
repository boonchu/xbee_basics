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

#define ssRxPin 4
#define ssTxPin 5


// Setup XBee variables
SoftwareSerial nss(ssRxPin, ssTxPin);
XBee xbee = XBee();
ZBRxResponse rx = ZBRxResponse();


#define pushButtonPin 2 // hardware interrupt pin 2 Uno
#define ledPin 10
volatile int state = LOW;

// software debouncing in interrupt function
// http://www.instructables.com/id/Arduino-Software-debouncing-in-interrupt-function/
long debouncing_time = 15; // in millsecs
volatile unsigned long last_micros;

void debounceInterrupt() {
  if ((long)(micros() - last_micros) >= debouncing_time * 1000) {
    Interrupt();
    last_micros = micros();
  }
}

// sending message after push button hardware pin 2
void Interrupt() {
  // Encapsulate the message with 64 bits target address
  uint8_t data[] = {'H','E','L','L','O',' ',
        'F','R','O','M',' ',
        'B','O','O','N','C','H','U'};
  XBeeAddress64 addr64 = XBeeAddress64();
  addr64.setMsb(0x0013a200);//XXXXX -> Msb address of router/end node
  addr64.setLsb(0x414faf83);//XXXXX -> Lsb address of router/end node 
  ZBTxRequest zbTx = ZBTxRequest(addr64, data, sizeof(data));

  // Sending PING message to coordinator
  xbee.send(zbTx);  
    
  // flash LED 10 when sending PING
  //for (int i=0; i<5; i++) {
  //  digitalWrite(ledPin, HIGH);
  //  delay(10);
  //  digitalWrite(ledPin, LOW);
  //  delay(10);
  //} 
  // toggle when state change
  state = !state;
    
}

// testing LED pin 10 from hardware pin 2 push button
void blink() {
  // toggle when state change
  state = !state;
}

void setup()
{
  Serial.begin(9600);
  nss.begin(9600);
  xbee.setSerial(nss);
  Serial.println("Wait to receive data from Router..."); 

  pinMode(pushButtonPin, INPUT_PULLUP);  

  // flash led Pin 10 times
  pinMode(ledPin, OUTPUT);
  for (int i=0; i<10; i++) {
    digitalWrite(ledPin, HIGH);
    delay(25);
    digitalWrite(ledPin, LOW);
    delay(25);
  }

  // attach interrupt to push Button (sending message to XBee)
  attachInterrupt(digitalPinToInterrupt(pushButtonPin), debounceInterrupt, CHANGE);

  // https://www.arduino.cc/en/Reference/AttachInterrupt
  // attach interrupt to blink LED (testing) hardware pin 2
  // attachInterrupt(digitalPinToInterrupt(pushButtonPin), blink, CHANGE);
  
}

void loop()
{
  String sample;

  // debug pin to monitor interrupt
  digitalWrite(ledPin, state);
  
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
