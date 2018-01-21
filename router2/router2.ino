#include <XBee.h>
#include <SoftwareSerial.h>
// XBee's DOUT (TX) is connected to MEGA RX1 (Arduino's Software RX)
// XBee's DIN (RX) is connected to MEGA TX1 (Arduino's Software TX)

XBee xbee = XBee();
ZBRxResponse rx = ZBRxResponse();

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
  String sample;
  
  // Encapsulate the message with 64 bits target address
  uint8_t data[] = {'P','I', 'N', 'G'};
  XBeeAddress64 addr64 = XBeeAddress64();
  addr64.setMsb(0x0013a200);//XXXXX -> Msb address of router/end node
  addr64.setLsb(0x41637ee1);//XXXXX -> Lsb address of router/end node 
  ZBTxRequest zbTx = ZBTxRequest(addr64, data, sizeof(data));
  
  // Sending PING message to coordinator
  xbee.send(zbTx);
  digitalWrite(ROUTER_PIN, HIGH);
  delay(50);
  digitalWrite(ROUTER_PIN, LOW);
  delay(50);

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
    } else if (xbee.getResponse().isError()) {
      Serial.print("Error reading packet. Error code is ");
      Serial.println(xbee.getResponse().getErrorCode());
    } // end (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)
  
  } // end if(xbee.getResponse().isAvailable())  
}
