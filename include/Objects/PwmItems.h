
#pragma once

#include <Arduino.h>

#ifdef ESP8266
#include <Servo.h>
#else
#include <ESP32Servo.h>
#endif

#include "Base/Item.h"

class Pwm : public Item {
   public:
    Pwm(const String& name, const String& assigned, const String& value) : Item{name, assigned, value} {
        pinMode(getPin(), OUTPUT);
    };

    void onStateChange() override {
        analogWrite(getPin(), getState());
    };
};

class Pwms {
   public:
    Pwms();
    Pwm* add(String name, String assign, String param);
    Pwm* at(size_t index);
    Pwm* get(const String name);
    size_t count();

   private:
    Pwm* last();

   private:
    std::vector<Pwm> _items;
};

extern Pwms myPwm;