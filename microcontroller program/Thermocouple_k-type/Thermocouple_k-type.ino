void setup() {
  Serial.begin(9600);
}

void loop() {
  int adc_val = analogRead(A1);
  int temperature = (((adc_val*4.88)-0.0027)/10)-26;
  //Serial.print(adc_val);
  Serial.print("Temperature = ");
  Serial.println(temperature);
  delay(500);
}
