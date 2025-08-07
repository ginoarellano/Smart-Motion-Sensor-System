#define BLYNK_TEMPLATE_ID "TMPL6QjjQKUZR"
#define BLYNK_TEMPLATE_NAME "Smart Motion Activated Security System"
#define BLYNK_AUTH_TOKEN "kX22dMfjEU7NYbKgoCxAp3Iu5Pn2uor7"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Redmi Note 12";
char pass[] = "123456789";

// Pin assignments
const int trigPin = D5;
const int echoPin = D6;
const int buzzerPin = D7;
const int ledPin = D1;

const int distanceThreshold = 10;  // cm

bool switchState = false;  // Track the switch state
unsigned long lastNotificationTime = 0;
const unsigned long cooldown = 10000;  // 10 seconds for cooldown

BlynkTimer timer;

BLYNK_WRITE(V1) {
  switchState = param.asInt();  // Update the switch state from Blynk app
}

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Blynk.begin(auth, ssid, pass);

  timer.setInterval(2000L, checkDistance);  // Check the distance every 3 seconds
}

void loop() {
  Blynk.run();
  timer.run();
}

void checkDistance() {
  if (!switchState) {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
    return;
  }

  long duration;
  int distance;

  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Blynk.virtualWrite(V2, distance);  // Send distance to Blynk

  if (distance > 0 && distance < distanceThreshold) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);

    if (millis() - lastNotificationTime >= cooldown) {
      Blynk.logEvent("motion_alert", "Unauthorized motion detected in the patient records room!");
      lastNotificationTime = millis();
    }

  } else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
  }

  delay(500);  // Allow brief pause between checks
}
