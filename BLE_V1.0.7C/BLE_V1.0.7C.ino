/* Project name: Arduino - AT 09 BLE module
   Project URI: https://www.studiopieters.nl/arduino-at-09-ble-module/
   Description: allow the Arduino to communicate with the AT-09 BLE module
   Version: 1.0.7.C
   License: MIT
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
int PIN_EN_OUT = 4;
int PIN_STATE_IN = 5;


void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(9600);

  sendCommand("AT");
  sendCommand("AT+ROLE0");
  sendCommand("AT+UUID0xFFE0");
  sendCommand("AT+CHAR0xFFE1");
  sendCommand("AT+NAMELightBlue");
}

void sendCommand(const char * command){
  Serial.print("Command send :");
  Serial.println(command);
  mySerial.println(command);
  //wait some time
  delay(100);
  
  char reply[100];
  int i = 0;
  while (mySerial.available()) {
    reply[i] = mySerial.read();
    i += 1;
  }
  //end the string
  reply[i] = '\0';
  Serial.print(reply);
  Serial.println("Reply successful");
}

void readSerial(){
  char reply[50];
  int i = 0;
  while (mySerial.available()) {
    reply[i] = mySerial.read();
    i += 1;
  }
  //end the string
  reply[i] = '\0';
  if(strlen(reply) > 0){
    Serial.println(reply);
    Serial.println("Houston we have a signal!");
  }
}

void loop() {
  readSerial();
  delay(500);
}
