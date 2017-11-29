/*
 * AUTHOR: Rafael Bezerra (https://github.com/rnbez)
 */

#define LIGHT_PIN 13
#define PIR_SENSOR 2
#define STAY_ON_DELAY 10000

int pirState = LOW; // we start, assuming no motion detected
// int hasMovement = 0; // variable for reading the pin status

// Variables will change:
int lightState = LOW;
int ledState = LOW;               // ledState used to set the LED
unsigned long previousMillis = 0; // will store last time LED was updated
unsigned long interval = 1000;

bool hasMovement()
{
  int _read = digitalRead(PIR_SENSOR);
  return (_read == HIGH);
}

void setup()
{
  pinMode(LIGHT_PIN, OUTPUT); // declare LED as output
  pinMode(PIR_SENSOR, INPUT); // declare sensor as input

  Serial.begin(9600);

  if (hasMovement())
  {
    lightState = HIGH;
  }
  else
  {
    lightState = LOW;
  }
}

void loop()
{
  unsigned long currentMillis = millis();

  if (lightState == HIGH)
  {
    if (currentMillis - previousMillis > STAY_ON_DELAY)
    {
      // save the last time you blinked the LED
      previousMillis = currentMillis;

      if (!hasMovement())
      {
        lightState = LOW;
      }
    }
  }
  else
  {
    if (hasMovement())
    {
      lightState = HIGH;
    }
    else
    {
      lightState = LOW;
    }
  }

  digitalWrite(LIGHT_PIN, lightState);
}
