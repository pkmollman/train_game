/*
Code for Arduino for lanes
*/

// Define the pin numbers for the IR sensors
const int IRSensor1 = 3;  // IR Sensor 1 connected to digital pin 2
const int IRSensor2 = 5;  // IR Sensor 2 connected to digital pin 3
const int IRSensor3 = 6;  // IR Sensor 3 connected to digital pin 4
const int IRSensor4 = 9;  // IR Sensor 4 connected to digital pin 5
const int IRSensor5 = 10;  // IR Sensor 5 connected to digital pin 6
const int IRSensor6 = 11;  // IR Sensor 6 connected to digital pin 7

// dip in proper order
const int SWITCHES[] = { 4, 7, 8 };



// Array to store the IR sensor pins
int IRSensors[] = {IRSensor1, IRSensor2, IRSensor3, IRSensor4, IRSensor5, IRSensor6};

// Variables to track detection timing for each IR sensor
unsigned long lastDetectionTime[6] = {0, 0, 0, 0, 0, 0};  // Stores the last detection time for each sensor
const unsigned long detectionCooldown = 1000;  // Minimum time (ms) between detections for each sensor

void setup() {
  // Initialize serial communication for printing to the console
  Serial.begin(9600);

  for (int i = 0; i < 3; i++) {
    pinMode(SWITCHES[i], INPUT_PULLUP);
  }

  // Set the IR sensor pins as input
  for (int i = 0; i < 6; i++) {
    pinMode(IRSensors[i], INPUT);
  }
}

void loop() {
  // Get the current time
  unsigned long currentTime = millis();

  int flag_state = 0;

  for (int i = 0; i < 3; i++) {
    int dip_state = digitalRead(SWITCHES[i]);
    flag_state = flag_state + (dip_state << i);
    // Serial.print("Dip: ");
    // Serial.print(i);
    // Serial.print(" State: ");
    // Serial.println(dip_state);
  }
  // Serial.println(flag_state);

  // Check each IR sensor for detection
  for (int i = 0; i < 6; i++) {
    // If the IR sensor detects the ball (assuming LOW indicates detection) and the cooldown period has passed
    if (digitalRead(IRSensors[i]) == LOW && (currentTime - lastDetectionTime[i] > detectionCooldown)) {
      Serial.print("IR Sensor ");
      Serial.print(i + 1);
      Serial.println(": DETECTED");

      send_score_event(flag_state, i+1);

      // Update the last detection time for the current sensor
      lastDetectionTime[i] = currentTime;
    }
  }
}

void send_message(String messageType, String messageContent) {
  Serial.println(messageType + ";" + messageContent + ";" + messageType);
}

void send_score_event(int playerId, int targetId) {
  send_message("PLAYER_SCORE", "player_id:"+String(playerId)+";"+"targetId:"+String(targetId));
}
  