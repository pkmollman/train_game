#include <Wire.h>

int x = 69;

// client
void client_setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.setSDA(0);
  Wire.setSCL(1);
  Wire.begin(10);
  Wire.onReceive(receiveEvent);
}

void client_loop() {
}

void receiveEvent(int bytes) {
  if (Wire.read() == 69) {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(500);                      // wait for a second
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  }    // read one character from the I2C
}

// host
void host_setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.setSDA(0);
  Wire.setSCL(1);
  delay(2000);
  Wire.begin();
}

void host_loop() {
  hit_client(9);
  hit_client(10);
  delay(500);
}

void hit_client(int address) {
  digitalWrite(LED_BUILTIN, HIGH);
  Wire.beginTransmission(address); // transmit to device #9
  Wire.write(x);              // sends x 
  Wire.endTransmission();    // stop transmitting
  digitalWrite(LED_BUILTIN, LOW);
}
