#include <DHT.h>
#include <RotaryEncoder.h>

const int hallPin = A0; 
const int led = 13; 
const int button = 2; 
const int dhtPin = 4; 
const int temperatureUpperThreshold = 29;
const int temperatureLowerThreshold = 7;
const int pressureUpperThreshold = 200;
const int pressureLowerThreshold = 50;
const int encoderCLK =5;
const int encoderDT= 6;
const int encoderSW = 7;

#define DHTTYPE DHT11
DHT dht(dhtPin, DHTTYPE);
RotaryEncoder encoder(encoderCLK, encoderDT);

long currentPressure = 100; 
int rotations = 0; 
unsigned long lastMillis = 0;
const int interval = 1000;
bool highPressureWarningPrinted = false;
bool lowPressureWarningPrinted = false;
bool isMagnet = false;
unsigned long lastHallEvent = 0;
const int debounceDelay = 50;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  dht.begin();
  delay(5000);
}

void loop() {
  encoder.tick();
  long newPos = encoder.getPosition();
  int hallValue = analogRead(hallPin); 
  if (hallValue > 540 || hallValue < 500) {
  if (!isMagnet && millis() - lastHallEvent > debounceDelay) {
    rotations++;
    isMagnet = true;
    lastHallEvent = millis();
  }
} else {
  isMagnet = false;
}
  if (millis()-lastMillis >=interval){
    lastMillis = millis();
    
  float temperature = dht.readTemperature();
  Serial.println(temperature);
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } 
  if (temperature > temperatureUpperThreshold) {
    Serial.println("WARNING: Tire Temperature is HIGH!");
  }
  if (temperature < temperatureLowerThreshold) {
    Serial.println("WARNING: Tire Temperature is LOW!");
  }
   if (newPos != currentPressure) {
    currentPressure = newPos;
    Serial.print("Current Pressure: ");
    Serial.println(currentPressure);
  }
  long rpm=(rotations * 60);
  Serial.print("RPM: ");
  Serial.println(rpm);
  rotations = 0;
  }

  
 
 if (currentPressure > pressureUpperThreshold) {
    digitalWrite(led, HIGH);
    if (!highPressureWarningPrinted) {
      Serial.println("WARNING: Tire Pressure is HIGH!");
      highPressureWarningPrinted = true;
      lowPressureWarningPrinted = false; 
    }
  } else if (currentPressure < pressureLowerThreshold) {
    digitalWrite(led, HIGH);
    if (!lowPressureWarningPrinted) {
      Serial.println("WARNING: Tire Pressure is LOW!");
      lowPressureWarningPrinted = true;
      highPressureWarningPrinted = false; g
    }
  } else {
    digitalWrite(led, LOW);
    highPressureWarningPrinted = false; 
    lowPressureWarningPrinted = false;
  }

}