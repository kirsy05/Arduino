/*****
Author: Kirsten Schulze
eMail: kirsten.schulze@studium.uni-hamburg.de
Date: 2023-03-01

This script uses an Arduino together with a DS18B20 Sensor
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

}

void loop() {
  byte rom_code[8]; //create an array containing 8 elements of type byte for the ROM code
  byte sp_data[9]; //new array for Scratchpad date of lenght 9


  //used webpage: https://www.pjrc.com/teensy/td_libs_OneWire.html
  //Start 1st sequence to read out the rom code (sensor family on USB, then 48-bit registration number)
  ow.reset();
  ow.write(READ_ROM);
  for (int i=0; i<8; i++){
    rom_code[i]= ow.read();
  }

  //check if right sensor family
  if(rom_code[0] !=IS_DS18B20_SENSOR) {
    Serial.println("Sensor is not a DS18B20 sensor!");
    //return;

    //Serial.println("Family code: ");
    //Serial.println(rom_code[0]);
  }

  String registration_number;
  for (int i=1; i<7; i++) {
    registration_number += String(rom_code[i], HEX); //formate ROM code as a HEX
  }

  //start sequence for converting temperature
  ow.reset();
  ow.write(SKIP_ROM);
  ow.write(CONVERT_T);

  //start sequence for reading data from Scratchpad
  ow.reset();
  ow.write(SKIP_ROM);
  ow.write(READ_SCRATCHPAD);
  for (int i=0; i<9; i++) {
    sp_data[i]=ow.read();
  }  

  int16_t tempRead = sp_data[1] << 8 | sp_data[0]; //operating 8-bit shift of LSB T_0 and MSB T_1 and store it in a 16 bit long array, calling it tempRead

  float tempCelsius = tempRead / 16.0; //divide by 2^4 = 16 for 4 digits after the comma

  //Serial.print(registration_number);
  //Serial.print(", ");
  //Serial.println(tempCelsius); //print temperature results on serial monitor

  printOutput(getISOtime());  //comment out if using plotter
  printOutput(", "); //comment out if using plotter
  printOutput((String)millis());
  printOutput(", ");
  printOutput(registration_number);
  printOutput(", ");
  printOutputln((String)tempCelsius);
  
  

  delay(1000); //adding a delay of 1000 ms


}