#include <Arduino.h>

const int RELAY_PIN = D8;
const int SOIL_MOISTURE_PIN = D4;
const int WORKING_TIME_THRESHOLD = 80000;

unsigned long workingStartTime = 0;

int currentRelayState = HIGH;

int lastSoilMoisture = -1;

// Function declarations
void relayHandler(int relayPin, int relayState);

void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  Serial.begin(115200);
  relayHandler(RELAY_PIN, HIGH);
}

void loop()
{
  int soilMoisture = digitalRead(SOIL_MOISTURE_PIN);

  Serial.println(soilMoisture);

  if (soilMoisture == LOW)
  {
    relayHandler(RELAY_PIN, LOW);
    workingStartTime = millis();
  }
  else if (millis() - workingStartTime < WORKING_TIME_THRESHOLD)
  {
    // Do nothing while waiting
  }
  else
  {
    relayHandler(RELAY_PIN, HIGH);
  }

  Serial.println(currentRelayState);

  delay(1000);
}

void relayHandler(int relayPin, int relayState)
{
  currentRelayState = relayState;
  digitalWrite(relayPin, relayState);
}
