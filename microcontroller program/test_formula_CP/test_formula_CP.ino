

float R = 8.314;
float Gm = 0.6485;
float At = 19.635;
float mdot = 17.39;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
int Tc = (250 / 0.909);
  float Pc = ((mdot / At));
  //*( ((R * Tc)) / Gm ));

  Serial.print(" | Chamber Pressure: ");
  Serial.print(Pc,4);
  Serial.print(" Pascals");

  Serial.println();
}
