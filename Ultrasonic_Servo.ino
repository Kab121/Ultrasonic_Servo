#include <Servo.h>

// Define Servo object
Servo servo;

// Define ultrasonic sensor pins
int trigPin = 11;
int echoPin = 12;

// Define variables
long duration;
int distance;

void setup() {
  // Attach servo to a PWM pin
  servo.attach(9);       // Use Pin 9 for servo signal
  servo.write(90);       // Set servo to the initial position
  delay(2000);           // Wait for 2 seconds

  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin
  duration = pulseIn(echoPin, HIGH, 20000); // Timeout after 20ms
  if (duration == 0) {
    Serial.println("No echo received - Out of range");
    return; // Skip further processing
  }

  // Calculate distance
  distance = duration * 0.034 / 2;

  // Print the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  // Check distance and control the servo
  if (distance > 0 && distance <= 25) { // Ensure valid range
    Serial.println("Object detected! Moving servo to 180 degrees.");
    servo.write(180); // Move servo to 180 degrees
    delay(3000);      // Wait for 3 seconds
  } else {
    Serial.println("No object detected. Moving servo to 90 degrees.");
    servo.write(90); // Move servo to 90 degrees
  }

  delay(100); // Small delay to avoid excessive looping
}
