const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 8;
const int buzzerPin = 7;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void beep(int duration, int frequency) {
  tone(buzzerPin, frequency, duration);
  delay(duration);
  noTone(buzzerPin);
  delay(50); // Pause between beeps
}

void loop() {
  long duration, distance;

  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo duration
  duration = pulseIn(echoPin, HIGH, 10000);  // Timeout set to 10,000 microseconds

  // Calculate distance in centimeters
  distance = duration * 0.034 / 2;

  // Display distance on the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Adjust LED and buzzer based on distance
  if (distance < 10) {
    // Too close, turn on LED and beep continuously
    digitalWrite(ledPin, HIGH);
    while (distance < 10) {
      beep(200, 1000);
      // Measure the echo duration in the loop
      duration = pulseIn(echoPin, HIGH, 10000);
      // Calculate distance in centimeters
      distance = duration * 0.034 / 2;
    }
    digitalWrite(ledPin, LOW); // Turn off LED when distance is greater than 10 cm
  } else if (distance < 20) {
    // Close, blink LED and fast beep
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    beep(100, 1500);
  } else if (distance < 30) {
    // Medium distance, blink LED and moderate beep
    digitalWrite(ledPin, HIGH);
    delay(300);
    digitalWrite(ledPin, LOW);
    beep(150, 1000);
  } else {
    // Far, turn off LED and no beep
    digitalWrite(ledPin, LOW);
  }

  delay(500); // Adjust the delay based on your preference
}
