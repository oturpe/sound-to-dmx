// Sound to dmx
//
// Author: Otto Urpelainen
// Email: oturpe@iki.fi

#include "config.h"

#include "Atmega328pUtils.h"
#include "DataBuffer.h"

#include "lib/DmxSimple/DmxSimple.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Cleaner setting of bits
#define BV(x) (1<<x)

/// Initializes analog to digital conversion by setting the reference and
/// prescaler.
void initializeAdc() {
  Atmega328p::setVoltageReference(Atmega328p::VREF_VCC);
  Atmega328p::setAdcPrescalerValue(ADC_PRESCALER);

  // Enable adc
  ADCSRA |= BV(ADEN);

// Disable digital input from pins that are used for adc.
  DIDR0 |= BV(ADC0D) | BV(ADC1D) | BV(ADC2D) | BV(ADC3D);
}

/// Initializes pwm values for outputting led control.
void initializePwm() {
  // Fast pwm mode for timer 0
  TCCR0A |= BV(WGM01) | BV(WGM00);
  // Non-inverting mode for counter A
  TCCR0A |= BV(COM0A1);
  // Non-inverting mode for counter B
  TCCR0A |= BV(COM0B1);

  // Set PD5 (OC0B), PD6 (OC0A) as outputs
  DDRD |= BV(DDD5) | BV(DDD6);

  Atmega328p::setTimer0Prescaler(PWM_PRESCALER);
}

int16_t readAnalog0() {
  // Select analog input ADC0
   ADMUX &= ~BV(MUX3) & ~BV(MUX2) & ~BV(MUX1) & ~BV(MUX0);

  // start conversion and wait until value is available
  ADCSRA |= BV(ADSC);
  while(ADCSRA & BV(ADSC));

  return ADC;
}

int16_t readAnalog1() {
  // Select analog input ADC1
   ADMUX &= ~BV(MUX3) & ~BV(MUX2) & ~BV(MUX1);
   ADMUX |= BV(MUX0);

  // start conversion and wait until value is available
  ADCSRA |= BV(ADSC);
  while(ADCSRA & BV(ADSC));

  return ADC;
}

int16_t readAnalog2() {
  // Select analog input ADC2
   ADMUX &= ~BV(MUX3) & ~BV(MUX2) & ~BV(MUX0);
   ADMUX |= BV(MUX1);

  // start conversion and wait until value is available
  ADCSRA |= BV(ADSC);
  while(ADCSRA & BV(ADSC));

  return ADC;
}

int16_t readAnalog3() {
  // Select analog input ADC3
   ADMUX &= ~BV(MUX3) & ~BV(MUX2);
   ADMUX |= BV(MUX1) | BV(MUX0);

  // start conversion and wait until value is available
  ADCSRA |= BV(ADSC);
  while(ADCSRA & BV(ADSC));

  return ADC;
}

/// Initialized dmx output. This includes initializing timer, enabling
/// interrupts and setting DxmSimple parameters.
void initializeDmx() {
  Atmega328p::setTimer2Prescaler(DMX_PRESCALER);
  sei();
  DmxSimple.maxChannel(3);
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

  #ifdef DEBUG
    // Debug pin
    DDRD |= BV(DDD2);
    PORTD |= BV(PORTD2);
    _delay_ms(500);
    PORTD &= ~BV(PORTD2);
    _delay_ms(500);
    PORTD |= BV(PORTD2);
    _delay_ms(500);
    PORTD &= ~BV(PORTD2);
  #endif

  initializeAdc();
  initializePwm();
  initializeDmx();

  DataBuffer channel1(AVG_WINDOW, (int16_t)0);
  DataBuffer channel2(AVG_WINDOW, (int16_t)0);
  DataBuffer channel3(AVG_WINDOW, (int16_t)0);
  DataBuffer channel4(AVG_WINDOW, (int16_t)0);

  while(true) {
    channel1.add(readAnalog0());
    channel2.add(readAnalog1());
    channel3.add(readAnalog2());
    channel4.add(readAnalog3());

    int16_t peakToPeak1 = channel1.peakToPeak();
    int16_t peakToPeak2 = channel2.peakToPeak();
    int16_t peakToPeak3 = channel3.peakToPeak();
    int16_t peakToPeak4 = channel4.peakToPeak();

    //Testing: show values as some kind of dmx

    int16_t peakOutput1 = (peakToPeak1-OFFSET_PEAK_1)*SCALE_PEAK_1;
    peakOutput1 = limit(peakOutput1, 0, 255);
    if(peakOutput1 > 100) {
      DmxSimple.write(1, peakOutput1);
      DmxSimple.write(2, peakOutput1);
      DmxSimple.write(3, peakOutput1);
    } else {
      DmxSimple.write(1, 0);
      DmxSimple.write(2, 0);
      DmxSimple.write(3, 0);
    }

    //Testing: show values as pwm

    int16_t peakOutput2 = (peakToPeak2-OFFSET_PEAK_2)*SCALE_PEAK_2;
    peakOutput2 = limit(peakOutput2, 0, 255);
    OCR0B = peakOutput2;

    int16_t peakOutput3 = (peakToPeak3-OFFSET_PEAK_3)*SCALE_PEAK_3;
    peakOutput3 = limit(peakOutput3, 0, 255);
    OCR2A = peakOutput3;

    // Removed testing: timer 2 not used for pwm anymore
    /*
    int16_t peakOutput4 = (peakToPeak4-OFFSET_PEAK_4)*SCALE_PEAK_4;
    peakOutput4 = limit(peakOutput4, 0, 255);
    OCR2B = peakOutput4;
    */

    #ifdef DEBUG
      if(peakOutput4 > 100) {
      PORTD |= BV(PORTD2);
      } else {
        PORTD &= ~BV(PORTD2);
      }
    #endif
  }
}
