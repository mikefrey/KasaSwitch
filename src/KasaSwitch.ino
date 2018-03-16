/*
 * Project KasaSwitch
 * Description:
 * Author:
 * Date:
 */

// This #include statement was automatically added by the Particle IDE.
#include "TPLink.h"
#include "ClickButton.h"

const int ledPin = D1;
int ledState = LOW;

// The button
const int buttonPin = D0;
ClickButton btn(buttonPin, LOW, CLICKBTN_PULLUP);

// uint8_t HS105plugIP[4] = {192,168,0,106};
uint8_t HS105plugIP[4] = {192,168,0,114};

void setup() {
  // turn off the status led
  RGB.control(true);
  RGB.color(0, 0, 0);

  // setup the LED pin
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  btn.debounceTime = 30;
  btn.multiclickTime = 250;
  btn.longClickTime = 1000;
}

void loop() {
  // update buttons state
  btn.Update();

  if (btn.clicks == 1) {
    Particle.publish("SingleClick");
    ledState = HIGH;
    TPLink_Plug(HS105plugIP, 1);
  }

  if (btn.clicks == 2) {
    Particle.publish("DoubleClick");
    ledState = LOW;
    TPLink_Plug(HS105plugIP, 0);
  }

  digitalWrite(ledPin, ledState);
}
