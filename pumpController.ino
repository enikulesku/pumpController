#define RELAY1_PIN D11
#define RELAY2_PIN D12

#define PUMP_PIN   D13

// 4 hours
#define MIN_DELAY     14400000UL
#define INITIAL_DELAY 0UL

unsigned long lastOff, currentMillis;

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
  lastOff = INITIAL_DELAY;
}

void loop() {
  boolean currentState = digitalRead(PUMP_PIN) == HIGH;

  if (!currentState) {
    if (lastState) {
      change(false);
    }
  } else {
    if (!lastState) {
      currentMillis = millis();
      if ((lastOff == INITIAL_DELAY) || (currentMillis - lastOff >= MIN_DELAY)) {
        change(true);
      }
    }
  }
  delay(1000);
}
