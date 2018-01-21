##### XBee #####

- Youtube links:
    - Xbee Wireless Doorbell application (https://youtu.be/B4bG1ZqNCJo)

###### Hardwares :
- Arduino MEGA
- Arduino UNO
- 2x XBee S2C edition (https://www.digi.com/products/models/xb24cz7wit-004)
- XBee Explorer USB adapter
- 2x XBee breakout boards
- Voltage regulator from 5 to 3.3 volt

###### Instructions (MAC Only):
- Download Digi XCTU Mac version 

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/XCTU-1.png)

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/XCTU-2.png)

- Download UART driver (https://learn.sparkfun.com/ftdiDriversMac)
- Download CoolTerm for AT command mode
- Ensure XBee AT mode. Reset the XBee unit if not supporting AT mode
- Use XBee Explorer (USB adapter) to initialize XBee S2C and update firmware
    - My Spec: XBee s2c
    - Run XCTU -> Help ->  "Update the XBee Radio Firmware Library"
    - Wait for updating library...
    - Select Xbee to update firmware, and click "update" 

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/firmware1.png)

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/firmware2.png)

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/firmware3.png)

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/firmware4.png)

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/firmware5.png)

- Test XBee 
    - Select Spectrum Aaalyzer to measure the spectrum of the selected radio band (default: 100)

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/analyze1.png)

- Test AT mode
    - Select the XBee USB UART device
    - Ensure to enable "Local Echo" on Cool Team application
    - my router AT configuration (figure coolterm A)
    - router AT configuration (figure coolterm B)
    - how to write AT configuration parameter back to radio device (figure coolterm C)
    - coordinator AT configuration (figure coolterm D)
    - attach device to screen with local echo mode
        - screen /dev/tty.usbmodem14121 9600
    - exit from screen (Ctrl-A, k)
    
```
output: find tty

$ ls -lt /dev/tty.usb*
crw-rw-rw-  1 root  wheel   20,   4 Sep 23 02:53 /dev/tty.usbserial-A9U9HVFJ
crw-rw-rw-  1 root  wheel   20,   8 Sep 23 02:52 /dev/tty.usbmodem14121
```

![Coolterm A](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/coolterm1.png)

![Coolterm B](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/coolterm2.png)

![Coolterm C](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/coolterm3.png)

![Coolterm D](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/coolterm4.png)

###### Wiring for testing XBee throughput
- Testing Troughtput with XCTU and one Arduino unit with XBee
    - First XBee unit (Coordinator) : use XBee Explorer USB adapter
    - Second XBee unit (Router) : use Arduino MEGA

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/tp1.png)

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/tp2.png)

```
wiring: MEGA

        XBee PIN 1: vcc 3v3 -> 3v3 MEGA
        XBee PIN 2: TX out  -> TX0 MEGA
        XBee PIN 3: RX in   -> RX0 MEGA
        XBee PIN 10: GND    -> GND MEGA
                            -> RST MEGA to GND MEGA (passthrough)
```


###### Sample 1 : Wiring for testing XBee AT mode (Coordinator/Router)
- Wire both XBee to Arduino
    * wire pins to Arduino
    * upload sketch router to MEGA
    * upload sketch coordinator to UNO
    * use Cool Term application to connect both MEGA and UNO

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/xbee_test1.png)

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/xbee_test2.png)

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/xbee_test3.png)

```
    * First XBee unit (Coordinator): Arduino UNO
        XBee PIN 1: vcc 3v3 -> 3v3 UNO
        XBee PIN 2: TX out  -> PIN 2: RX UNO
        XBee PIN 3: RX in   -> PIN 3: TX UNO
        XBee PIN 10: GND    -> GND UNO
```

```
    * Second XBee unit (Router): Arduino MEGA
        XBee PIN 1: vcc 3v3 -> 3v3 MEGA
        XBee PIN 2: TX out  -> RX1 MEGA
        XBee PIN 3: RX in   -> TX1 MEGA
        XBee PIN 10: GND    -> GND MEGA
```


###### Sample 2 : Wiring for testing XBee API mode (Coordinator/Router)
- Wire both XBee to Arduino
    - rewire the Arduino Pins
    - revert the wire after changing radio devices to API
    - upload sketch "router1" to MEGA
    - upload sketch "coordinator1" to UNO
    - use Cool Term application to connect both MEGA and UNO
    - you should see flashing LED light from Digital Pin 10 Second Arduino "Router"
    - see output screenshot 

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/xbee_second1.png)

```
    "First XBee" unit (Coordinator): Arduino UNO
        XBee PIN 1: vcc 3v3 -> 3v3 UNO
        XBee PIN 2: TX out  -> TX0 UNO
        XBee PIN 3: RX in   -> RX0 UNO
        XBee PIN 10: GND    -> GND UNO
                            -> RST UNO to GND UNO (passthrough)
```

```
    "Second XBee" unit (Router): Arduino MEGA
        XBee PIN 1: vcc 3v3 -> 3v3 MEGA
        XBee PIN 2: TX out  -> TX0 MEGA
        XBee PIN 3: RX in   -> RX0 MEGA
        XBee PIN 10: GND    -> GND MEGA
                            -> RST MEGA to GND MEGA (passthrough)
```

```
    Enter AT mode on first unit and run these following commands
        +++
        ATAP 2
        ATWR
```

```
    Switch "First XBee" that previously set to API mode and re-wire pins.
        XBee PIN 1: vcc 3v3 -> 3v3 UNO
        XBee PIN 2: TX out  -> PIN 2: RX UNO
        XBee PIN 3: RX in   -> PIN 3: TX UNO
        XBee PIN 10: GND    -> GND UNO
```

```
    - Switch "Second XBee" that previously set to API mode and re-wire pins.
        XBee PIN 1: vcc 3v3 -> 3v3 MEGA
        XBee PIN 2: TX out  -> RX1 MEGA
        XBee PIN 3: RX in   -> TX1 MEGA
        XBee PIN 10: GND    -> GND MEGA

    - Add LED to D10 and jump GND to Arduino GND pin
```

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/xbee_second_video.gif)

###### Sample 3 : Use push button from coordinator to send message to router
- Wire both XBee to Arduino


- add push button to hardware pin 2 Arduino UNO 
- move pin 2, pin 3 (tx, rx) to pin 4, pin 5

```
    Add hardware interrupt pin 2 to push button 
        XBee PIN 1: vcc 3v3 -> 3v3 UNO
        XBee PIN 2: TX out  -> PIN 4: RX UNO
        XBee PIN 3: RX in   -> PIN 5: TX UNO
        XBee PIN 10: GND    -> GND UNO

        Push button pin 1   -> PIN 2: 5 vcc UNO INPUT
        Push button pin 3   -> registor 200 Ohm and registor wire to GND 5 vcc
        Push button pin 4   -> 5 vcc
```

- no wiring change from MEGA
- upload "router2" to Arduino MEGA
- upload "coordinator2" to Arduino UNO
- See output result (xbee_third*.png)

###### Sample 4 : Door Bell application (Arduino -> Arduino)
- This application is simple. Coordinator radio pass data from one Arduino to 
    another by broadcasting to remote radio device. Doorbell melody will output
    sound to Buzzer after receiving message from radio that match to "RING" word.
    The melody require Arduino processor to send pitch (frequency based sounds) to buzzer.

```
    Wiring for MEGA to output Buzzer melody
        XBee PIN 1: vcc 3v3 -> 3v3 MEGA
        XBee PIN 2: TX out  -> RX1 MEGA
        XBee PIN 3: RX in   -> TX1 MEGA
        XBee PIN 10: GND    -> GND MEGA

    Add Passive Buzzer and use Pin 8 from MEGA
        Passive Buzzer: GND on board
        Passive BUzzer: Digital Pin 8 MEGA
```

- no wiring change from UNO
- upload "doorbell_router" to Arduino MEGA
- upload "doorbell_coordinator" to Arduino UNO

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/doorbell.gif)

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/push_button_xbee.png)


###### Sample 5 : reading data sensor from remote radio device (AT mode at router)
- This example demostrates how read data from radio pin and transfer to coordinator

```
    "Second XBee" unit (Router): Arduino MEGA
        XBee PIN 1: vcc 3v3 -> 3v3 MEGA
        XBee PIN 2: TX out  -> TX0 MEGA
        XBee PIN 3: RX in   -> RX0 MEGA
        XBee PIN 10: GND    -> GND MEGA
                            -> RST MEGA to GND MEGA (passthrough)

    pull out passive Buzzer and insert LED 
    possitive pin from LED goes to PIN 20 Xbee breakout

```

- no wiring changes from UNO
- upload "coordinator2remote_at" to UNO
- run X-CTU application 
- load/fetch router configuration and configure IO sampling rate

```
+++
ATIR 1388
ATWR
ATCN
```

- bring up Serial console window from UNO
- switch D0 to HIGH and LOW 

```
+++
ATD0 5 (LOW->HIGH)
ATCN
+++
ATD0 4 (HIGH->LOW)
ATCN
```

- observe changes from serial console 
- the message status changes from HIGH to LOW or LOW to HIGH when D0 status change from
  remote radio end

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/coord2remote1.png)

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/coord2remote2.png)

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/coord2remote3.png)

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/coord2remote4.png)

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/coordinator2remote.gif)


###### Sample 6 : reading DHT11 humidity sensor from remote radio device (AT mode at router)
- This example demostrates how read data from radio pin 20 ADC0 and transfer to coordinator

```
    - Wiring for MEGA to set up AT mode
        XBee PIN 1: vcc 3v3 -> 3v3 MEGA
        XBee PIN 2: TX out  -> TX0 MEGA
        XBee PIN 3: RX in   -> RX0 MEGA
        XBee PIN 10: GND    -> GND MEGA

    - Add DHT11 sensor
        Signal Pin 1        -> Voltage divider (10k/5k) before sending 1.2v signal to XBee PIN 20
        Vcc Pin 2           -> Vcc 3v3
        GND Pin 3           -> GND 3v3
```

- no wiring changes from UNO
- upload "coordinator2remote_sensor" to UNO
- run X-CTU application 
- load/fetch router configuration and configure IO sampling rate
```
+++
ATIR 1388 (IO sampling rate)
ATD0 2 (Change to ADC mode)
ATWR
ATCN
```

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/coordinator2remote.gif)

- Explanation regarding Analog read from XBee data from IOSampling
    - (https://www.digi.com/resources/documentation/digidocs/pdfs/90002002.pdf) (Page 148) 

```
The sampled data set includes 2 bytes of digital I/O data only if one or more I/O lines on the device are
configured as digital I/O. If no pins are configured as digital I/O, these 2 bytes are omitted. Pins are
configured as digital I/O by setting them to a value of 3, 4, or 5.

The digital I/O data is only relevant if the same bit is enabled in the digital I/O mask.
Analog samples are returned as 10-bit values. The device scales the analog reading such that 0x0000
represents 0 V, and 0x3FF = 1.2 V (The analog inputs on the device cannot read more than 1.2 V.). The
device returns analog samples in order starting with AIN0 and finishing with AIN3, and the supply
voltage. Only enabled analog input channels return data.

To convert the A/D reading to mV, do the following:

AD(mV) = (A/D reading * 1200mV) / 1023

The reading in the sample frame represents voltage inputs of 1143.75 and 342.1875 mV for AD0 and
AD1 respectively
```

- Explanation regarding how DHT11 digital reading works
    - (http://www.micropik.com/PDF/dht11.pdf) (Page 5)

```
Single-bus data format is used for communication and synchronization between MCU and
DHT11 sensor. One communication process is about 4ms.
Data consists of decimal and integral parts. A complete data transmission is 40bit, and the
sensor sends higher data bit first.

Data format: 8bit integral RH data + 8bit decimal RH data + 8bit integral T data + 8bit decimal T
data + 8bit check sum. If the data transmission is right, the check-sum should be the last 8bit of

"8bit integral RH data + 8bit decimal RH data + 8bit integral T data + 8bit decimal T data".

When MCU sends a start signal, DHT11 changes from the low-power-consumption mode to the
running-mode, waiting for MCU completing the start signal. Once it is completed, DHT11 sends a
response signal of 40-bit data that include the relative humidity and temperature information to
MCU. Users can choose to collect (read) some data. Without the start signal from MCU, DHT11
will not give the response signal to MCU. Once data is collected, DHT11 will change to the lowpower-consumption
mode until it receives a start signal from MCU again
```

- output ADC value from analog read from Xbee router that transfer to Xbee coordinator

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/sample-61.png)

```
Calculation:

AD(mV) = (A/D reading * 1200mV) / 1023
    AD mV ~ (538 * 1200) / 1023 ~ 631 mV

This value of voltage mean nothing to me since I cannot be able to calculate and convert into 
temperature and humidity value. According to the document above, Xbee seems not support digital
sensor since the method read out from sensor is different and require Arduino to handle it.
```

- If you want to make temperature sensor working in standalone mode Xbee on router end, you can follow this project.
    - (https://makerzone.mathworks.com/blog/continuous-monitoring-of-wireless-network-of-temperature-sensors-using-matlab-and-xbee-part-1/)
    - Use TMP36 Analog sensor, input 9-12 bits (https://www.sparkfun.com/products/10988)


###### Sample 7 : reading Thermistor registor value from remote radio device (AT mode at router)
- This example demostrates how read temperature from radio pin 20 ADC0 and transfer to coordinator

```
    - Wiring for MEGA to set up AT mode
        XBee PIN 1: vcc 3v3 -> 3v3 MEGA
        XBee PIN 2: TX out  -> TX0 MEGA
        XBee PIN 3: RX in   -> RX0 MEGA
        XBee PIN 10: GND    -> GND MEGA

    - Add Thermistor Temperature Resistor (see picture)
        
```


![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/temperature_sensor2.png)

- no wiring changes from Arduino UNO
- upload "temperature_sensor" sketch to Arduino UNO
- run X-CTU application 
- load/fetch router configuration and configure IO sampling rate, and Pin 20 to ADC input mode

```
+++
ATIR 1388 (IO sampling rate)
ATD0 2 (Change to ADC mode)
ATWR
```

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/temperature_sensor.png)

![ScreenShot](https://github.com/boonchu/arduino_projects/blob/xbee/xbee/temperature_sensor.gif)

- I use codes from below to calculate Analog sampling data from Pin 20 XBee to convert into temperature value

```

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
```

###### Reference:
    - What is XBee s2c?
        - (https://alselectro.wordpress.com/2017/01/23/zigbee-xbee-s2c-how-to-configure-as-coordinator-router-end-device/)
        - (https://spin.atomicobject.com/2016/07/18/xbee-tutorial/)

    - XBee API Configuration Guide
        - (https://github.com/andrewrapp/xbee-api/wiki/XBeeConfiguration)

    - XBee pins assignment
        - (https://github.com/andrewrapp/xbee-api/wiki/XBeePins)

    - XBee Library Example
        - (https://github.com/andrewrapp/xbee-arduino/tree/master/examples/)

    - XBee API Example
        - (https://dzone.com/articles/xbee-zigbee-complaint)

    - XBee reads sampling data from remote radio
        - (https://alselectro.wordpress.com/2014/09/07/xbee-s2digital-sampling-with-api-frame-data/)

    - Xbee network topology
        - (https://www.digi.com/videos/choosing-the-right-mesh-networking-technology-for)
