#include <XBee.h>
#include <SoftwareSerial.h>
// XBee's DOUT (TX) is connected to MEGA RX1 (Arduino's Software RX)
// XBee's DIN (RX) is connected to MEGA TX1 (Arduino's Software TX)

XBee xbee = XBee();

#define ROUTER_PIN 10

void setup()
{
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  Serial.begin(9600);   //USB
  Serial1.begin(9600);  //XBee/UART1/pins TX1 RX1
  xbee.setSerial(Serial1);
  Serial.println("Sending PING to Corrdinator..."); 
}

void loop() {

  // Encapsulate the message with 64 bits target address
  uint8_t data[] = {'P','I', 'N', 'G'};
  XBeeAddress64 addr64 = XBeeAddress64();
  addr64.setMsb(0x0013a200); //XXXXX -> Msb address of router/end node
  addr64.setLsb(0x41637ee1); //XXXXX -> Lsb address of router/end node 
  ZBTxRequest zbTx = ZBTxRequest(addr64, data, sizeof(data));
  
  xbee.send(zbTx);
  digitalWrite(ROUTER_PIN, HIGH);
  delay(50);
  digitalWrite(ROUTER_PIN, LOW);
  delay(50);
}
