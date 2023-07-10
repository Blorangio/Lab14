#include "oled-wing-adafruit.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

#define btn1 D6
#define btn2 D7

OledWingAdafruit display;

void isrIncrementCounter();

volatile int counter = 0;

bool interruptsBool = true;
bool btnPressed = false;

void setup() {
  display.setup();
	display.clearDisplay();
	display.display();
  display.setTextSize(1);
	display.setTextColor(WHITE);

  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);

  attachInterrupt(btn1, isrIncrementCounter, FALLING);
}
void loop() {
  display.loop();
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(counter);
  if(!digitalRead(btn2) && !btnPressed) {
    interruptsBool = !interruptsBool;
    changeInterruptVal();
    btnPressed = true;
  } 
  if(digitalRead(btn2)) {
    btnPressed = false;
  }
  display.display();
}

void isrIncrementCounter() {
  counter++;
}

void changeInterruptVal() {
  if(interruptsBool) {
    interrupts();
  } else {
    noInterrupts();
  }
}