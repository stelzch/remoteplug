#include <Arduino.h>

/**
 * Encapsulates communication protocol for a 433-MHz controlled
 * power outlet
 */
class RCOutlet {
  public:
    /**
     * Constructs a new RCOutlet instance.
     * 
     * @param tx_pin The pin number of the output pin where a 433 MHz transmit
     *               module is attached.
     */
    RCOutlet(int tx_pin);
    virtual ~RCOutlet();

    /**
     * Set the state of power outlet A.
     * 
     * @param state true turns the outlet on, false turns it off.
     */
    void switchA(bool state);
  protected:
    void send_one();
    void send_zero();
    void start_signal();
    void send_array(const byte *arr, int len);

    static constexpr int SYMBOL_T = 1530; // symbol period in microseconds
    static constexpr int REPETITION_DELAY = 1124; // delay between repetitions of the same symbols in microseconds
    static constexpr float ONE_HIGH_LOW_RATIO = 0.7035f; // amount of symbol 1 where signal is high
    static constexpr float ZERO_HIGH_LOW_RATIO = 0.2037f; // amount of symbol 0 where signal is high
    const byte A_ON[25] = {1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0};
    const byte A_OFF[25] = {1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0};

    int tx_pin;
};
