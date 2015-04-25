// Sound to dmx
//
// Author: Otto Urpelainen
// Email: oturpe@iki.fi

#include "config.h"

#include "Atmega328pUtils.h"
#include "AveragingDataSet.h"

#include <avr/io.h>
#include <util/delay.h>

// Cleaner setting of bits
#define BV(x) (1<<x)

/// Initializes analog to digital conversion by setting the reference and
/// prescaler.
void initializeAdc() {
  Atmega328p::setVoltageReference(Atmega328p::VREF_VCC);
  Atmega328p::setAdcPrescalerValue(ADC_PRESCALER);

  // Enable adc
  ADCSRA |= BV(ADEN);

// Disable digital inout from pins that are used for adc.
  DIDR0 |= BV(ADC0D) | BV(ADC1D) | BV(ADC2D) | BV(ADC3D);
}

int16_t readAnalog() {
  // Select analog input ADC0
   ADMUX &= ~BV(MUX3) & ~BV(MUX2) & ~BV(MUX1) & ~BV(MUX0);

  // start conversion and wait until value is available
  ADCSRA |= BV(ADSC);
  while(ADCSRA & BV(ADSC));

  // Measurement is done with inverse voltage. Invert again.
  return ADC;
}

int main() {

  initializeAdc();

  //Testing: show values with pwm:
  {
    // Set PD6 as output
    DDRD |= BV(DDD6);

    // Non-inverting mode
    TCCR0A |= BV(COM0A1);
    // Phase correct pwm mode
    TCCR0A |= BV(WGM00);

    Atmega328p::setTimer0Prescaler(PWM_PRESCALER);

  // Enable pwm
  TCCR0A |= BV(COM0A1);
  }

  DDRB |= BV(DDB0);

  AveragingDataSet channel1(0);
  while(true) {
    int16_t average = channel1.add(readAnalog(), true);

    //Testing: show values as pwm
    int16_t output = (average-OFFSET_1)*SCALE_1;
    if (output < 0) {
      output = 0;
    } else if (output > 255) {
      output = 255;
    }
    OCR0A = output;
  }
}