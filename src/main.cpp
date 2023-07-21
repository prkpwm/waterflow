#include <Arduino.h>

const int RELAY_PIN = D8;
const int SOIL_MOISTURE_PIN = D4;
const int WORKING_TIME_THRESHOLD = 120000;

unsigned long workingStartTime = 0;

int currentRelayState = LOW;

// Function declarations
void relayHandler(int relayPin, int relayState);

void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  Serial.begin(9600);
}

void loop()
{
  int soilMoisture = digitalRead(SOIL_MOISTURE_PIN);

  if (Serial.available() > 0)
  {
    soilMoisture = Serial.read();
  }

  if (soilMoisture == LOW)
  {
    relayHandler(RELAY_PIN, HIGH);
    workingStartTime = millis();
  }
  else if (millis() - workingStartTime < WORKING_TIME_THRESHOLD)
  {
    // Do nothing while waiting
  }
  else
  {
    relayHandler(RELAY_PIN, LOW);
  }

  Serial.println(currentRelayState);


  delay(100);
}

void relayHandler(int relayPin, int relayState)
{
  currentRelayState = relayState;
  digitalWrite(relayPin, relayState);
}
