// Host Board
#include <Wire.h>

#define HOST_ADDRESS 0x09
#define NUM_CLIENTS 4

unsigned long lastTime[NUM_CLIENTS];
const byte CLIENT_ADDRESSES[NUM_CLIENTS] = {0x08, 0x0A, 0x0C, 0x0E};

void setup() {
  Wire.begin(HOST_ADDRESS);
  Serial.begin(9600);
  for (int i = 0; i < NUM_CLIENTS; i++) {
    lastTime[i] = 0;
  }
}

void loop() {


  for (int i = 0; i < NUM_CLIENTS; i++) {
    unsigned long currentTime = millis();
    if (currentTime - lastTime[i] >= 100) { // request data every 100ms
      
      lastTime[i] = currentTime;
      
      Wire.requestFrom(CLIENT_ADDRESSES[i], 1);
      
      if (Wire.available()) {
        byte data = Wire.read();
      
        Serial.print("Received data from client ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(data);
      
      } //i2c read

    }
  } // End all timed client checks

} //Main loop

