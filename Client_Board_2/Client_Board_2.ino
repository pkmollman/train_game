// Client Board
//Test Board - #1 (Address 8)

#include <Wire.h>

#define HOST_ADDRESS 0x09
#define CLIENT_ADDRESS 0x08 // replace with unique address for each client

//This can be removed soon
byte dataToSend = 0x01;

//debug flag to send debug data to console
bool DEBUG = true;

const int sensorPin1 = 3;  // IR sensor 1 connected to digital pin 8
const int sensorPin2 = 5;  // IR sensor 2 connected to digital pin 9
const int sensorPin3 = 6;  // IR sensor 3 connected to digital pin 10
const int sensorPin4 = 9;  // IR sensor 4 connected to digital pin 11
const int sensorPin5 = 10;  // IR sensor 5 connected to digital pin 12
const int sensorPin6 = 11;  // IR sensor 6 connected to digital pin 13

int detected = 0;  // variable to count detected LEDs
const int NUM_LED = 5; //6 leds
int SCOREDELAY = 900; //delay in MS, this could be lowered needs testing

unsigned long lastTime[NUM_LED];

void setup() {
  Wire.begin(CLIENT_ADDRESS);
  Wire.onRequest(requestEvent);

  // set the sensor pins as inputs
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);
  pinMode(sensorPin5, INPUT);
  pinMode(sensorPin6, INPUT);
  



  Serial.begin(9600);

    Serial.println("New Game");
}

void loop() {
  unsigned long P1_currentTime = millis();
  unsigned long P2_currentTime = millis();
  unsigned long P3_currentTime = millis();
  unsigned long P4_currentTime = millis();
  unsigned long P5_currentTime = millis();
  unsigned long P6_currentTime = millis();

  //check for goal detection
  //Goal 1
  if (P1_currentTime - lastTime[0] >= SCOREDELAY) {
    if (digitalRead(sensorPin1) == LOW) {
      //Goal Hole 1
      lastTime[0] = P1_currentTime;
      
      detected = detected + 10;
      if ( DEBUG == true) {
        Serial.println("Goal Detected: 1");
      }
    }
  }

  //Goal 2
  if (P2_currentTime - lastTime[1] >= SCOREDELAY) {
    if (digitalRead(sensorPin2) == LOW) {
      //Goal Hole 2
      lastTime[1] = P2_currentTime;
      
      detected = detected + 10;
      if ( DEBUG == true) {
        Serial.println("Goal Detected: 2");
      }
    }
  }

//Goal 3
  if (P3_currentTime - lastTime[2] >= SCOREDELAY) {
    if (digitalRead(sensorPin3) == LOW) {
      //Goal Hole 3
      lastTime[2] = P3_currentTime;

      detected = detected + 10;
      if ( DEBUG == true) {
        Serial.println("Goal Detected: 3");
      }
    }
  }

//Goal 4
  if (P4_currentTime - lastTime[3] >= SCOREDELAY) {
    if (digitalRead(sensorPin4) == LOW) {
      //Goal Hole 4
      lastTime[3] = P4_currentTime;
      
      detected = detected + 50;

      if ( DEBUG == true) {
        Serial.println("Goal Detected: 4");
      }
    }
  }

//Goal 5
  if (P5_currentTime - lastTime[4] >= SCOREDELAY) {
    if (digitalRead(sensorPin5) == LOW) {
      //Goal Hole 5
      lastTime[4] = P5_currentTime;
      
      detected = detected + 100;

      if ( DEBUG == true) {
        Serial.println("Goal Detected: 5");
      }
    }
  }


//Goal 6
  if (P6_currentTime - lastTime[5] >= SCOREDELAY) {
    if (digitalRead(sensorPin6) == LOW) {
      //Goal Hole 6
      lastTime[5] = P6_currentTime;
      
      detected = detected + 50;

      if ( DEBUG == true) {
        Serial.println("Goal Detected: 6");
      }
    }
  }

  // wait for 10ms before checking again
  delay(10); // This needs to be as low as possible 
} // End Main loop

void requestEvent() {

  dataToSend = detected;
  Wire.write(dataToSend);

  if ( DEBUG == true) {
    Serial.print("Sent data ");
    Serial.print(dataToSend);
    Serial.print(" to host from client at address ");
    Serial.println(CLIENT_ADDRESS);
  }
  dataToSend = 0;
  detected = 0;
}
// End requestEvent