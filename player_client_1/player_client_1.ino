// Player Client

#include <Wire.h>

struct Player {
  int playerNum;
  int speed;
  int location;
};

Player players[4];

void setup() {
  Wire.begin(); // join I2C bus
  pinMode(2, INPUT); // IR LED input pins
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
}

void loop() {
  // create array of 4 objects with player number, speed, and location values
  players[0].playerNum = 1;
  players[0].speed = 5;
  players[0].location = 10;
  
  players[1].playerNum = 2;
  players[1].speed = 6;
  players[1].location = 15;
  
  players[2].playerNum = 3;
  players[2].speed = 7;
  players[2].location = 20;
  
  players[3].playerNum = 4;
  players[3].speed = 8;
  players[3].location = 25;
  
  // create I2C packet to send from client board to host board
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write((uint8_t*)&players, sizeof(players)); // send array of objects
  Wire.endTransmission(); // stop transmitting
  
  // receive I2C packet from client board and store object values in array
  Wire.requestFrom(8, sizeof(players));
  while(Wire.available()) {
    Wire.readBytes((uint8_t*)&players, sizeof(players));
  }
  
  // read IR LED input pin readings from 4 digital pins and store in array
  players[0].location = digitalRead(2);
  players[1].location = digitalRead(3);
  players[2].location = digitalRead(4);
  players[3].location = digitalRead(5);
  
  // print values of objects in array to serial monitor
  for(int i=0; i<4; i++) {
    Serial.print("Player ");
    Serial.print(players[i].playerNum);
    Serial.print(" Speed: ");
    Serial.print(players[i].speed);
    Serial.print(" Location: ");
    Serial.println(players[i].location);
  }
  
  delay(1000); // delay for one second before repeating loop
}
