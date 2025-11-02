// C++ code
//
#ifndef LED_BUILTIN
  #define LED_BUILTIN 2 // Define LED_BUILTIN if not already defined
#endif
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}
