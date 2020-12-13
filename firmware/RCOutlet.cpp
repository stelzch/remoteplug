#include "RCOutlet.h"

RCOutlet::RCOutlet(int tx_pin) {
  this->tx_pin = tx_pin;
  pinMode(tx_pin, OUTPUT);
}

RCOutlet::~RCOutlet() {

}

void RCOutlet::switchA(bool state) {
  if (state == true) {
    send_array(RCOutlet::A_ON, sizeof(A_ON));
  } else {
    send_array(RCOutlet::A_OFF, sizeof(A_OFF));
  }
}

void inline RCOutlet::send_one() {
  digitalWrite(tx_pin, HIGH);
  delayMicroseconds(SYMBOL_T * ONE_HIGH_LOW_RATIO);
  digitalWrite(tx_pin, LOW);
  delayMicroseconds(SYMBOL_T * (1.f - ONE_HIGH_LOW_RATIO));
}

void inline RCOutlet::send_zero() {
  digitalWrite(tx_pin, HIGH);
  delayMicroseconds(SYMBOL_T * ZERO_HIGH_LOW_RATIO);
  digitalWrite(tx_pin, LOW);
  delayMicroseconds(SYMBOL_T * (1.f - ZERO_HIGH_LOW_RATIO));
}

void inline RCOutlet::start_signal() {
  digitalWrite(tx_pin, HIGH);
  delayMicroseconds(305);
  digitalWrite(tx_pin, LOW);
  delayMicroseconds(2353);
}

void RCOutlet::send_array(const byte *arr, int len) {
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
