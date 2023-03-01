// C++ code
//

#define LED 9
unsigned long myTime;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}


void loop()
{
  //float time = millis()
  //digitalWrite(LED, HIGH); //I
  //delay(1000); // Wait for 1000 millisecond(s)//I
  //digitalWrite(LED, LOW);//I
  //delay(1000); // Wait for 1000 millisecond(s)//I
  
  //Serial.print("Time: "); //I
  myTime = millis();//I

  //Serial.println(myTime); // prints time since program started I
  //delay(1000);    //I
  
  if (myTime%1000<100) {
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
}
}