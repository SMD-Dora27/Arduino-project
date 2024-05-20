#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Motor driver pins for Motor 1
const int enaPin1 = 9;
const int in1Pin1 = 8;
const int in2Pin1 = 7;

// Motor driver pins for Motor 2
const int enaPin2 = 10;
const int in1Pin2 = 11;
const int in2Pin2 = 12;

// Ultrasonic sensor pins
const int trigPin = 13;
const int echoPin = 6;

// IR sensor pins
const int irSensorPin1 = 2;
const int irSensorPin2 = 3;

// GPS pins
const int esp32RxPin = 4; // RX pin of ESP32 connected to pin 4 of Arduino
const int esp32TxPin = 5; // TX pin of ESP32 connected to pin 5 of Arduino

TinyGPSPlus gps;
SoftwareSerial esp32Serial(esp32RxPin, esp32TxPin); // RX, TX pins for the ESP32 device

long duration;
int distance;

bool obstacleDetected = false;

void setup() {
  Serial.begin(9600);
  esp32Serial.begin(9600);
  
  pinMode(enaPin1, OUTPUT);
  pinMode(in1Pin1, OUTPUT);
  pinMode(in2Pin1, OUTPUT);
  pinMode(enaPin2, OUTPUT);
  pinMode(in1Pin2, OUTPUT);
  pinMode(in2Pin2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irSensorPin1, INPUT);
  pinMode(irSensorPin2, INPUT);
  
  // Start both motors in forward motion
  startMotor(enaPin1, in1Pin1, in2Pin1);
  startMotor(enaPin2, in1Pin2, in2Pin2);
}

void loop() {
  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure duration of the pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  distance = (duration * 0.034) / 2;

  // Print distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check for obstacle using ultrasonic sensor
  if (distance < 20) { // Adjust this threshold according to your requirement
    Serial.println("Obstacle detected!");
    // Stop both motors
    stopMotor(enaPin1);
    stopMotor(enaPin2);
    obstacleDetected = true;
  } else {
    Serial.println("No obstacle detected.");
    if (obstacleDetected) {
      // Wait for a minute
      delay(20000);
      // Resume forward motion for both motors
      startMotor(enaPin1, in1Pin1, in2Pin1);
      startMotor(enaPin2, in1Pin2, in2Pin2);
      obstacleDetected = false;
    }
  }

  // Read digital input from IR sensors
  int irSensorState1 = digitalRead(irSensorPin1);
  int irSensorState2 = digitalRead(irSensorPin2);

  // Check for track using IR sensors
  if (irSensorState1 == LOW || irSensorState2 == LOW) {
    Serial.println("Track detected!");
    // Motors are already running in forward motion, no need to do anything
  } else {
    Serial.println("No track detected.");
    // Stop both motors
    stopMotor(enaPin1);
    stopMotor(enaPin2);
    // Wait for a minute
    delay(20000);
    // Resume forward motion for both motors
    startMotor(enaPin1, in1Pin1, in2Pin1);
    startMotor(enaPin2, in1Pin2, in2Pin2);
  }

  // GPS reading
  float latitude = 0.0;
  float longitude = 0.0;
  while (esp32Serial.available() > 0) {
    if (gps.encode(esp32Serial.read())) {
      if (gps.location.isValid()) {
        latitude = gps.location.lat();
        longitude = gps.location.lng();
        Serial.print("Latitude: ");
        Serial.println(latitude, 5);
        Serial.print("Longitude: ");
        Serial.println(longitude, 5);
      }
    }
  }
  
  // Send GPS data to ESP32 through serial communication
  Serial.print("GPS:");
  Serial.print(latitude, 5);
  Serial.print(",");
  Serial.println(longitude, 5);
  
  delay(1000); // Delay between measurements
}

void startMotor(int enaPin, int in1Pin, int in2Pin) {
  // Set motor direction for forward motion
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  // Set motor speed
  analogWrite(enaPin, 255); // Full speed
}

void stopMotor(int enaPin) {
  // Set motor speed to 0 to stop
  analogWrite(enaPin, 0);
}
