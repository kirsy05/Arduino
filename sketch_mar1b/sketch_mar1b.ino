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

#include "ds18b28_commands.h"

//User-defined constants
const String logfile = "tsensor.log";

RTC_DS1307 rtc;

OneWire ow(4);

void setup() {
  Serial.begin(9600); 

  if(!rtc.begin()) {
    Serial.println("RTC is NOT running. Let's set the time now!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

// when time needs to be set on a new device or after a power loss the following line sets the RTC to the date and time this sketch was complied
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  if(!SD.begin(10)) {   //used pin 10
    Serial.println("SD module initialization failed or Card is not present");
    return;
  }

  // put your setup code here, to run once:

}

void loop() {
  //used webpage: https://www.pjrc.com/teensy/td_libs_OneWire.html
  //Start 1st sequence
  ow.reset();
  ow
  ow.write(CONVERT_T);  //this line wad added 
  // put your main code here, to run repeatedly:

}