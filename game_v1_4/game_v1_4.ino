int score = 0;  // initialize the score to 0
int loopCount = 0;  // initialize the loop counter to 0
//int scoreMax = 254;
int gameOver = 0;
int calibExit = 0;

//Pins
#define enA 5
#define in1 2
#define in2 3
int IR_Sensor1 = 7;
//#define IR_Sensor2 8


int trainSpeedMIN = 0;
int trainSpeedMAX = 250;
int trainSpeedIDLE = 95;
int trainDirection = 0;

void setup() {
  Serial.begin(9600);

  //PIN Modes
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(IR_Sensor1, INPUT);
  pinMode(IR_Sensor2, INPUT);
  
}

void loop() {

  //Begin Main Menu
  Serial.println("Menu:");
  Serial.println("1. Play Game");
  Serial.println("2. Play Demo");
  Serial.println("3. Option 3: Calibrate");

  while (Serial.available() == 0) {
    // wait for keyboard input
  }

  char option = Serial.read();

  switch (option) {
    case '1':
      game1();
      break;
    case '2':
      game2();
      break;
    case '3':
      option3();
      break;
    default:
      Serial.println("Invalid option. Please choose again.");
      break;
  }
} // end Games Main Menu


// Begin Game Loop
void game1() {
  score = 0;
  gameOver = 0;
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  Serial.println("Direction: FWD ");
  //for (int loopCount = 0; loopCount < 1200; loopCount++) { //end on time no matter what

  while ( gameOver == 0)  {

    //forward
    
    //score = trainSpeedIDLE;

    if (Serial.available()) {  // check if there is data available to read from serial port
        char input = Serial.read();  // read the input character
        if (input == 'a') {  // check if the input character is 'a'
          score = score + 10;  // increment the score by 1
        }
        if (input == 's') {
          score = score + 50;
        }
        if (input == 'd') {
         score = score + 100;
        }

       if (input == 't') {
         score = trainSpeedMIN;
        } // stop

        
        if (input == 'r') {
          if (trainDirection == 0) {
          //fwd
          digitalWrite(in1, LOW);
          digitalWrite(in2, HIGH);
          trainDirection = 1;    
          Serial.println("Direction: REV ");          
          } else {

          //rev
          digitalWrite(in1, HIGH);
          digitalWrite(in2, LOW);
          trainDirection = 0;
          Serial.println("Direction: FWD "); 
          }

        } //end direction input

        if (input == 'f') { //Do the game over animation!!
          gameOver = 1; //Game Over Man, Game over!!
          //Need to do the game over, which player won to animate the winner condition
        }
     } // end keyboard input loop
    Serial.print("Score: ");
    Serial.println(score);  // print the current score to the serial monitor
    
    
  
    score = score - 1;
    if (score > trainSpeedMAX) {score = trainSpeedMAX;}
    if (score < trainSpeedIDLE) {score = trainSpeedIDLE;}
    
    //Send Signal to Motor Controller
    analogWrite(enA, score); // Send PWM signal to motor A    
    
    loopCount++;  // increment the loop counter by 1
    Serial.println(loopCount);
    if (loopCount >= 1300){

      gameOver = 1;
    }
   
    delay(100);  // delay for 0.1 second
    } //end While
  //} //End For Loop, this is the time loop

  //Game End Process, cut motors Initiaite Game Over functions
  analogWrite(enA, 0);
  Serial.println("Game over.");
} //End Game 1, the game loop and return to the menu

void game2() {
  int randomValues[4];

  for (int i = 0; i < 4; i++) {
    randomValues[i] = random(100, 501);
    Serial.print("Random value ");
    Serial.print(i+1);
    Serial.print(": ");
    Serial.println(randomValues[i]);
    delay(100);
  }

  while (Serial.available() == 0) {
    // wait for keyboard input
  }

  Serial.read(); // clear any input that was entered

  Serial.println("Returning to menu.");
} //end game2

void option3() {

  int calibExit = 0;
  int ir_value = HIGH;

  Serial.println("Begin Calibration (B = Break) - Are you sure? (y/n)");

  while ( calibExit == 0)  {

    if (Serial.available()) {  // check if there is data available to read from serial port
        char input = Serial.read();  // read the input character
        if (input == 'y') {  // check if the input character is 'a'
        
        int detect = 0;
        while (detect == 0) {
            int ir_sensor_value = digitalRead(IR_Sensor1);

              // check if obstacle is detected
             if (ir_sensor_value == HIGH) {
             // 
             Serial.println(ir_sensor_value);
             } else {
             //Serial.print("IR sensor value: ");
             Serial.println(" detected ");
             detect = 1;
             calibExit = 1;
             }
        } //end detect          


        }  //End Yes for calibration

      if (input == 'n') {
        Serial.println("Option 3 is no.");
        calibExit = 1;
        Serial.println("Returning to menu.");
      } 
      if (input == 'b') {
        calibExit = 1;
        Serial.println("Break - Returning to menu.");
      }
    } // End Keyboard check
    //Serial.println("test.");
  } //end while
  Serial.println("Exiting.");
} //end option3