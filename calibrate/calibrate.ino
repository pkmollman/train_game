// Calibrate

// Define distance between point A and point B
const int distance = 100;

// Define speed and time variables for four cars
int car1_speed, car2_speed, car3_speed, car4_speed;
float car1_time, car2_time, car3_time, car4_time;

void setup() {
  // Initialize serial communication for debugging purposes
  Serial.begin(9600);
  
  // Read speed and time values for each car
  car1_speed = 50;
  car2_speed = 33;
  car3_speed = 40;
  car4_speed = 32;
  car1_time = 2.0;
  car2_time = 3.0;
  car3_time = 2.5;
  car4_time = 3.1;
}

void loop() {
  // Calculate speed at point B for each car
  float car1_speed_b = distance / car1_time;
  float car2_speed_b = distance / car2_time;
  float car3_speed_b = distance / car3_time;
  float car4_speed_b = distance / car4_time;

  // Print speed at point B for each car
  Serial.print("Speed at point B for Car 1: ");
  Serial.print(car1_speed_b);
  Serial.print(" ft/s\n");
  Serial.print("Speed at point B for Car 2: ");
  Serial.print(car2_speed_b);
  Serial.print(" ft/s\n");
  Serial.print("Speed at point B for Car 3: ");
  Serial.print(car3_speed_b);
  Serial.print(" ft/s\n");
  Serial.print("Speed at point B for Car 4: ");
  Serial.print(car4_speed_b);
  Serial.print(" ft/s\n");

  // Calculate average time taken by the four cars to reach point B
  float avg_time = (car1_time + car2_time + car3_time + car4_time) / 4.0;

  // Calculate acceleration required for each car to reach point B at the same time
  float car1_acceleration = (2 * distance) / (pow(car1_time, 2) - pow(avg_time, 2));
  float car2_acceleration = (2 * distance) / (pow(car2_time, 2) - pow(avg_time, 2));
  float car3_acceleration = (2 * distance) / (pow(car3_time, 2) - pow(avg_time, 2));
  float car4_acceleration = (2 * distance) / (pow(car4_time, 2) - pow(avg_time, 2));

  // Print acceleration required for each car
  Serial.print("Acceleration required for Car 1: ");
  Serial.print(car1_acceleration);
  Serial.print(" ft/s^2\n");
  Serial.print("Acceleration required for Car 2: ");
  Serial.print(car2_acceleration);
  Serial.print(" ft/s^2\n");
  Serial.print("Acceleration required for Car 3: ");
  Serial.print(car3_acceleration);
  Serial.print(" ft/s^2\n");
  Serial.print("Acceleration required for Car 4: ");
  Serial.print(car4_acceleration);
  Serial.print(" ft/s^2\n");

  // Wait for a few seconds before repeating the loop
  delay(5000);
}