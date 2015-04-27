// Sound to dmx
//
// Author: Otto Urpelainen
// Email: oturpe@iki.fi

#include "config.h"

#include "Atmega328pUtils.h"
#include "DataBuffer.h"

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

/// Limits give value by given minimum and maximum values.
///
/// \param value
///    Value to limit
///
/// \param min
///    Minimum value
///
/// \param max
///    Maximum value
///
/// \return
///    Limited value
int16_t limit(int16_t value, int16_t min, int16_t max) {
  if(value < min)
    return min;
  if(value > max)
    return max;

  return value;
}

int main() {

  initializeAdc();

  //Testing: show values with pwm:
  {
    // Fast pwm mode for timer 0
    TCCR0A |= BV(WGM01) | BV(WGM00);
    // Non-inverting mode for counter A
    TCCR0A |= BV(COM0A1);
    // Non-inverting mode for counter B
    TCCR0A |= BV(COM0B1);

    // Set PD5 (OC0B), PD6 (OC0A) as output
    DDRD |= BV(DDD5) | BV(DDD6);

    Atmega328p::setTimer0Prescaler(PWM_PRESCALER);

    // Enable pwm on OC0A (PD6)
    TCCR0A |= BV(COM0A1);
  }

  DDRB |= BV(DDB0);

  DataBuffer channel1(AVG_WINDOW, (int16_t)0);
  while(true) {
    channel1.add(readAnalog());
    int16_t average = channel1.average();
    int16_t peakToPeak = channel1.peakToPeak();

    //Testing: show values as pwm
    int16_t averageOutput = (average-OFFSET_AVG_1)*SCALE_AVG_1;
    averageOutput = limit(averageOutput, 0, 255);
    OCR0A = averageOutput;

    int16_t peakOutput = (peakToPeak-OFFSET_PEAK_1)*SCALE_PEAK_1;
    peakOutput = limit(peakOutput, 0, 255);
    OCR0B = peakOutput;
  }
}