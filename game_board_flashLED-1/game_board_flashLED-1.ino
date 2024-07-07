#include <Wire.h>

#define TRAIN_ADDR 9 // I2C address of the train object
#define PLAYER_ADDR 8 // I2C address of the player object
#define NUM_TRAINS 2 // number of trains
#define NUM_PLAYERS 2 // number of players

#define LED_STRIP_PIN 2 // output pin for the LED strip
#define RELAY_PIN 3 // output pin for the relay

// train object structure
struct TrainObject {
  int trainNumber;
  int speed;
  int location;
  int acceleration;
  int direction; // added value for direction
} trainObjects[NUM_TRAINS];

// player object structure
struct PlayerObject {
  int playerNumber;
  int score;
  bool hasWon;
} playerObjects[NUM_PLAYERS];

void setup() {
  Wire.begin(TRAIN_ADDR + NUM_TRAINS + PLAYER_ADDR + NUM_PLAYERS); // start I2C bus with all addresses
  Wire.onReceive(receiveEvent); // set receive event function
  Serial.begin(9600); // initialize serial communication
  pinMode(LED_STRIP_PIN, OUTPUT); // set LED strip pin as output
  pinMode(RELAY_PIN, OUTPUT); // set relay control pin as output
}

void loop() {
  // update train object values
  for (int i = 0; i < NUM_TRAINS; i++) {
    Wire.beginTransmission(TRAIN_ADDR + i); // start transmission to train object
    Wire.write(trainObjects[i].trainNumber);
    Wire.write(trainObjects[i].speed);
    Wire.write(trainObjects[i].location);
    // add update
    Wire.endTransmission();
  }

  // update player object values
  for (int i = 0; i < NUM_PLAYERS; i++) {
    Wire.beginTransmission(PLAYER_ADDR + i); // start transmission to player object
    Wire.write(playerObjects[i].playerNumber);
    Wire.write(playerObjects[i].score);
    Wire.write(playerObjects[i].hasWon);
    Wire.endTransmission();
  }

  // test each player for hasWon
  bool anyPlayerWon = false;
  for (int i = 0; i < NUM_PLAYERS; i++) {
    if (playerObjects[i].hasWon) {
      anyPlayerWon = true;
      break;
    }
  }

  // if any player has won, flash the LED strip and activate the relay every second
  if (anyPlayerWon) {
    digitalWrite(RELAY_PIN, HIGH); // activate the relay
    for (int i = 0; i < 12; i++) {
      digitalWrite(LED_STRIP_PIN, HIGH); // turn on LED strip
      delay(500);
      digitalWrite(LED_STRIP_PIN, LOW); // turn off LED strip
      delay(500);
    }
    digitalWrite(RELAY_PIN, LOW); // deactivate the relay
  }

  delay(1000); // wait for a second before updating values again
}

void receiveEvent(int bytes) {
  int address = Wire.read(); // read the I2C address of the client
  int index = address - TRAIN_ADDR; // calculate the index in the array based on the I2C address
  if (index >= 0 && index < NUM_TRAINS) {
    trainObjects[index].trainNumber = Wire.read();
    trainObjects[index].speed = Wire.read();
    trainObjects[index].location = Wire.read();
  } else {
    index = address - PLAYER_ADDR - NUM_TRAINS;
    if (index >= 0 && index < NUM_PLAYERS) {
      playerObjects[index].playerNumber = Wire.read();
      playerObjects[index].score = Wire.read();
      playerObjects[index].hasWon = Wire.read();
    }
  }
}
