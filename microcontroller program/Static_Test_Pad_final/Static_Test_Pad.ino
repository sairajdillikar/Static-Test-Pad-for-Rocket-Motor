#include "HX711.h"

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2

int BUZZ_LED = 4;
int RELAY = 5;
int SPDT = 6;

float R = 8.314;
float Gm = 0.6485;
float At = 19.635; // diameter of 5mm;
//float mdot = 17.39;
//float Mi;

int temperature;
//float Pc;
unsigned long StartTime = 0;
unsigned long CurrentTime = 0;

HX711 scale;

float calibration_factor = -35900;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZ_LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(SPDT, INPUT);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  //float Mi=scale.get_value();
  //scale.tare();
//loop();

}

void loop() {

  {
  int SwitchPos = digitalRead(SPDT);
  if (SwitchPos == 1) 
  {
    int x;
    for (x = 0; x < 10; x++)
    {
      digitalWrite(BUZZ_LED, HIGH);
      delay(500);
      digitalWrite(BUZZ_LED, LOW);
      delay(500);
    }
    digitalWrite(RELAY, HIGH);
    delay(1000);
  }
  else {
    digitalWrite(RELAY, LOW);
  }
  scale.tare();
  }
  

  
  StartTime = millis();
  while(scale.get_units() > 0)
  {
  int adc_val = analogRead(A1);
  temperature = (((adc_val * 4.88) - 0.0027) / 10) - 25;
  Serial.print("Temperature = ");
  Serial.print(temperature);
  

  int weight = scale.get_units();
  float thrust = weight*9.81;
  scale.set_scale(calibration_factor);
  Serial.print(" | Thrust: ");
  Serial.print(thrust, 1);
  Serial.print(" Newtons");
  Serial.println();

  if (Serial.available())
  {
    char temp = Serial.read();
    if (temp == '+')
      calibration_factor += 10;
    else if (temp == '-')
      calibration_factor -= 10;
  }
}


  CurrentTime = millis();
  int Bt = (CurrentTime - StartTime);
  //delay(1000);
  float Mf=abs(scale.get_value());
  float mdot=abs(Mf/Bt);
  int Tc = (temperature / 0.909);
  float Pc = ((mdot / At) * ( (sqrt(R * Tc)) / Gm ));

  if(Pc > 0)
  {
  Serial.print("Chamber Pressure: ");
  Serial.print(Pc);
  Serial.print(" Pascals");

  Serial.println();
  //StartTime = CurrentTime;
  }
  
}
