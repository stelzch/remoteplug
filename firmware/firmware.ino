#include "RCOutlet.h"

RCOutlet rco(13);


void setup() {
  
}

void loop() {
  // put your main code here, to run repeatedly:
  rco.switchA(true);
  delay(2000);
  rco.switchA(false);
  delay(2000);
}
