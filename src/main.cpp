#include <Arduino.h>
#include <sbus.h>

void SBUS_eventCallback(int eventCode, int eventParam) {
  switch(eventCode) {
    case SBUS_EVENT_FAILSAFE:
      Serial.printf("Failsafe event: %s\n", eventParam?"true":"false");
      break;
    case SBUS_EVENT_TIMEOUT:
      Serial.printf("Timeout event: %s\n", eventParam?"true":"false");
      break;
    case SBUS_EVENT_VALUE_CHANGED:
      Serial.printf("Channel %d changed: %d\n", eventParam, SBUS.getChannel(eventParam));
      break;
    case SBUS_EVENT_CLICKED:
      Serial.printf("Channel %d clicked\n", eventParam);
      break;
    case SBUS_EVENT_PRESSED:
      Serial.printf("Channel %d pressed\n", eventParam);
      break;
    case SBUS_EVENT_LONG_CLICKED:
      Serial.printf("Channel %d long clicked\n", eventParam);
      break;
    case SBUS_EVENT_LONG_PRESSED:
      Serial.printf("Channel %d long pressed\n", eventParam);
      break;
    case SBUS_EVENT_RELEASED:
      Serial.printf("Channel %d released\n", eventParam);
      break;
    default:
      break;
  }
}

void SBUS_callback(int eventCode, int eventParam) {
  Serial.printf("Channel 1: %d\nChannel 2: %d\nChannel 3: %d\n", SBUS.getChannel(0), SBUS.getChannel(1), SBUS.getChannel(2));
  Serial.printf("Channel 4: %d\nChannel 5: %d\nChannel 6: %d\n", SBUS.getChannel(3), SBUS.getChannel(4), SBUS.getChannel(5));
  Serial.printf("Frame lost: %s\nFailsafe: %s\nTimeout: %s\n\n", SBUS.getLostFrame()?"true":"false", SBUS.getFailsafe()?"true":"false", SBUS.getTimeout()?"true":"false");
}

void setup() {
  Serial.begin(115200);
  while(!Serial);

  Serial1.begin(100000, SERIAL_8E2);
  Serial1.setTimeout(6);
  SBUS.begin(Serial1);

  // steering config
  SBUS.setEnabled(0, true);
  // SBUS.setReverse(0, true);
  // SBUS.setNeutral(0, 32);
  SBUS.setDeadzone(0, 100);

  // throttle config
  SBUS.setEnabled(1, true);
  SBUS.setDeadzone(1, 10);

  // switch F1
  SBUS.setEnabled(3, true);
  SBUS.setDigital(3, true);

  // switch F2
  SBUS.setEnabled(4, true);
  SBUS.setDigital(4, true);

  // switch F3
  SBUS.setEnabled(5, true);
  SBUS.setDigital(5, true);

  // SBUS.attach(SBUS_callback);
  SBUS.attachEvent(SBUS_EVENT_FAILSAFE, SBUS_eventCallback);
  SBUS.attachEvent(SBUS_EVENT_TIMEOUT, SBUS_eventCallback);
  SBUS.attachEvent(SBUS_EVENT_VALUE_CHANGED, SBUS_eventCallback);
  SBUS.attachEvent(SBUS_EVENT_CLICKED, SBUS_eventCallback);
  SBUS.attachEvent(SBUS_EVENT_LONG_CLICKED, SBUS_eventCallback);
  SBUS.attachEvent(SBUS_EVENT_PRESSED, SBUS_eventCallback);
  SBUS.attachEvent(SBUS_EVENT_LONG_PRESSED, SBUS_eventCallback);
  SBUS.attachEvent(SBUS_EVENT_RELEASED, SBUS_eventCallback);

  Serial.println("Ready!");
}

void loop() {
  SBUS.processInput();
}
