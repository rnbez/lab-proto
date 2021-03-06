/*
 * AUTHOR: Rafael Bezerra (https://github.com/rnbez)
 */

#define LIGHT_PIN 3
#define PIR_SENSOR 2
#define MQTT_IN 6
#define MQTT_OUT 9
#define STAY_ON_DELAY 10000
#define PIR_READ_DELAY 1000

int lightState = LOW;
unsigned long lastPIRRead = 0;
unsigned long previousMillis = 0; // will store last time LED was updated

bool hasMovement()
{
  int _read = digitalRead(PIR_SENSOR);
  lastPIRRead = millis();
  Serial.print("Sensor read: ");
  Serial.println(_read);
  return (_read == HIGH);
}

void setRelay(int state) {
  digitalWrite(LIGHT_PIN, !state);
}

void setup()
{
  pinMode(LIGHT_PIN, OUTPUT); // declare LED as output
  pinMode(PIR_SENSOR, INPUT); // declare sensor as input
  pinMode(MQTT_IN, INPUT);
  pinMode(MQTT_OUT, OUTPUT);
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
  int mqtt_in = digitalRead(MQTT_IN);
  if (mqtt_in == 1)
  {
    lightState = HIGH;
  }
  else
  {
    if (lightState == HIGH)
    {
      unsigned long now = millis();
      if (now - previousMillis > STAY_ON_DELAY)
      {
        // save the last time you blinked the LED
        previousMillis = now;

        if (!hasMovement())
        {
          lightState = LOW;
        }
      }
    }
    else
    {
      if (millis() - lastPIRRead > PIR_READ_DELAY)
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
    }
  }

  if (lightState == 1)
  {
    analogWrite(MQTT_OUT, 170);
  }
  else
  {
    analogWrite(MQTT_OUT, 0);
  }
  setRelay(lightState);
}
