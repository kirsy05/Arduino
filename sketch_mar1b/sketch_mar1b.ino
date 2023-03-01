/*****
Author: Kirsten Schulze
eMail: kirsten.schulze@studium.uni-hamburg.de
Date: 2023-03-01

This script uses an Arduino together with a 0518
*****/

#include <SD.h>
#include <SPI.h>
#include <RTClib.h>
#include <OneWire.h>

RTC_051307 rtc;

OneWire ow(4);

void setup() {
  Serial.begin(9600); 

  if(!rtc.begin()) {
    Serial.println("RTC is NOT running. Let's set the time now!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  if(!SD.begin(10)) {
    Serial.println("SD module initialization failed or Card is not present");
    return;
  }

  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}