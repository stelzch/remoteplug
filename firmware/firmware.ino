const int TX_PIN = 13;

const byte a_on[] = {1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0};
const byte a_off[] = {1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  pinMode(TX_PIN, OUTPUT);
}

void inline send_on() {
  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(1075);
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(453);
}

void inline send_off() {
  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(315);
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(1231);
}

void send_array(const byte *arr, int len) {
  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(305);
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(2353);
  
  for(int repetition = 0; repetition < 8; repetition++) {
    for (int i = 0; i < len; i++) {
      if (*(arr++) == 0) {
        send_off();
      } else {
        send_on();
      }
    }
    delayMicroseconds(1124);
    
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  send_array(a_on, 25);
  delay(2000);
  send_array(a_off, 25);
  delay(2000);
}
