#include "Arduino_RouterBridge.h"

void set_led_state(bool state);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    // Start with LED OFF
    digitalWrite(LED_BUILTIN, HIGH);

    Bridge.begin();

    Bridge.provide("set_led_state", set_led_state);
}

void loop() {
}

void set_led_state(bool state) {
    // Built-in LED is active LOW on many Arduino boards
    if (state) {
        digitalWrite(LED_BUILTIN, LOW);   // ON
    } else {
        digitalWrite(LED_BUILTIN, HIGH);  // OFF
    }
}