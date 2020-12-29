#include "HX711.h"

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2

int BUZZ_LED=4;
int RELAY=5;
int SPDT=6;

HX711 scale;

float calibration_factor = -35900; 

void setup() {
  Serial.begin(9600);
  pinMode(BUZZ_LED,OUTPUT);
  pinMode(RELAY,OUTPUT);
  pinMode(SPDT,INPUT);
  
  //Serial.println("HX711 calibration sketch");
  //Serial.println("Remove all weight from scale");
  //Serial.println("After readings begin, place known weight on scale");
  //Serial.println("Press + or a to increase calibration factor");
  //Serial.println("Press - or z to decrease calibration factor");
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare();
  
  //long zero_factor = scale.read_average(); 
  //Serial.print("Zero factor: "); 
  //Serial.println(zero_factor);
}

void loop() {
  int SwitchPos = digitalRead(SPDT);

  if(SwitchPos == 1){
    int x;
    for(x=0;x<10;x++)
    {
      digitalWrite(BUZZ_LED, HIGH);
      delay(500);
      digitalWrite(BUZZ_LED, LOW);
      delay(500); 
    }
    digitalWrite(RELAY, HIGH);
    delay(1800);
  }
  else{
    digitalWrite(RELAY, LOW);
    //delay(100);
  }

  
  int adc_val = analogRead(A1);
  int temperature = (((adc_val*4.88)-0.0027)/10)-26;
  //Serial.print(adc_val);
  Serial.print("Temperature = ");
  Serial.print(temperature);
  //delay(500);


  scale.set_scale(calibration_factor); 
  Serial.print(" | Thrust: ");
  Serial.print(scale.get_units()*9.81, 1);
  Serial.print(" Newtons"); 
  //Serial.print(" calibration_factor: ");
  //Serial.print(calibration_factor);
  Serial.println();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
  }
}
