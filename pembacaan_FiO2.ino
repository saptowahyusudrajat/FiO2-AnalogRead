#include <Wire.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads;
double fio2;
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup(void)
{
  Serial.begin(9600);
  ads.setGain(GAIN_ONE);
  ads.begin();
  myservo.attach(9);
}


void loop(void)
{

  //val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
 // val = map(val, 0, 1023, 0, 80);     // scale it to use it with the servo (value between 0 and 180)
  //myservo.write(val);                  // sets the servo positio
  Serial.println(read_fio2());
  //Serial.print(",");
  //Serial.println(val);
  delay(100);
}


double read_fio2() {
  /*
    -15 bit = 32767
    -vref arduino : 4.1 V
    -(1/32767) * 4100 mV = 0.1251258889

    -ke-50 : FiO2 21% = 47 mV
    -ke-25 : FiO2 21% = 12.14 mV
    
    -pembagi ke50 : 47/21 = 2.25238095
    -pembagi ke25 : 12.14/21 = 0.571
    -FiO2 = adc * ((1/32767) * 4100 mV) / pembagi
  */
  fio2 = (ads.readADC_SingleEnded(0) * 0.1251258889) / 0.571;
  return fio2;
}
