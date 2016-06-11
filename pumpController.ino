#define RELAY1_PIN D11
#define RELAY2_PIN D12

#define PUMP_PIN   D13

// 4 hours
#define MIN_DELAY  14400000

long lastOff;

boolean lastState = false;

void change(boolean isOn) {
  if (isOn) {
    digitalWrite(RELAY1_PIN, LOW);
    digitalWrite(RELAY2_PIN, LOW);
  } else {
    digitalWrite(RELAY1_PIN, HIGH);
    digitalWrite(RELAY2_PIN, HIGH);
    lastOff = millis();
  }

  lastState = isOn;
}

void setup() {
  pinMode(PUMP_PIN, INPUT);
  
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  change(false);
  lastOff = 0;
}

void loop() {
  boolean currentState = digitalRead(PUMP_PIN) == HIGH;

  if (!currentState) {
    if (lastState) {
      change(false);
    }
  } else {
    if (!lastState) {
      if ((lastOff == 0) || (abs(millis() - lastOff) >= MIN_DELAY)) {
        change(true);
      }
    }
  }
  delay(1000);
}
