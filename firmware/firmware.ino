const int TX_PIN = 13;

const int SYMBOL_T = 1530; // symbol period in microseconds
const int REPETITION_DELAY = 1124; // delay between repetitions of the same symbols in microseconds
const float ONE_HIGH_LOW_RATIO = 0.7035f; // amount of symbol 1 where signal is high
const float ZERO_HIGH_LOW_RATIO = 0.2037f; // amount of symbol 0 where signal is high


const byte a_on[] = {1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0};
const byte a_off[] = {1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  pinMode(TX_PIN, OUTPUT);
}

void inline send_one() {
  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(SYMBOL_T * ONE_HIGH_LOW_RATIO);
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(SYMBOL_T * (1.f - ONE_HIGH_LOW_RATIO));
}

void inline send_zero() {
  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(SYMBOL_T * ZERO_HIGH_LOW_RATIO);
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(SYMBOL_T * (1.f - ZERO_HIGH_LOW_RATIO));
}

void inline start_signal() {
  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(305);
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(2353);
}

void send_array(const byte *arr, int len) {
  start_signal();
  
  for(int repetition = 0; repetition < 8; repetition++) {
    for (int i = 0; i < len; i++) {
      if (*(arr++) == 0) {
        send_zero();
      } else {
        send_one();
      }
    }
    delayMicroseconds(REPETITION_DELAY);
    
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  send_array(a_on, 25);
  delay(2000);
  send_array(a_off, 25);
  delay(2000);
}
