#include <Servo.h>
#define trigPin 12
#define echoPin 11
#define servoPin 13
#define redLightPin 10

Servo tireServo;

long duration;
int distance;
int currentPosition = 0;
int landingThreshold = 20; // Change as needed (in cm)

void setup() {
 Serial.begin(9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(redLightPin, OUTPUT);
 tireServo.attach(servoPin);
 tireServo.write(0); // Start with tire retracted
}

void loop() {
 // Trigger ultrasonic sensor
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);

// Read echo
 duration = pulseIn(echoPin, HIGH);
 distance = duration * 0.034 / 2; // Convert to cm

 Serial.print("Distance: ");
 Serial.print(distance);
 Serial.println(" cm");

 // If landing (distance <= threshold)
 if (distance <= landingThreshold) {
 if (currentPosition != 120) {
 Serial.println("Landing detected - lowering tire.");
 tireServo.write(120); // Lower tire
 currentPosition = 120;
 }

 // Blink red light
 digitalWrite(redLightPin, HIGH);
 delay(200);
 digitalWrite(redLightPin, LOW);
 delay(200);
 } else {
 if (currentPosition != 10) {
 Serial.println("Plane ascending - retracting tire.");
 tireServo.write(10); // Raise tire
 currentPosition = 10;
 }

 digitalWrite(redLightPin, LOW); // Ensure red light is off
 delay(400); // Match total delay with landing blink
 }
}
