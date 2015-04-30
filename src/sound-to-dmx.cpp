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
  DmxSimple.maxChannel(1);
}

/// Initializes the pins and interrupts needed to drive the three dimming triacs.
void initializeTriacDrive() {
  DDRD |= BV(DDD1);
  DDRD |= BV(DDD7);
  DDRB |= BV(DDB0);
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
  initializeDmx();
  initializeTriacDrive();


  DataBuffer channel1(AVG_WINDOW, (int16_t)0);
  DataBuffer channel2(AVG_WINDOW, (int16_t)0);
  DataBuffer channel3(AVG_WINDOW, (int16_t)0);
  DataBuffer channel4(AVG_WINDOW, (int16_t)0);

  int counter = 0;
  while(true) {
    channel1.add(readAnalog0());
    channel2.add(readAnalog1());
    channel3.add(readAnalog2());
    channel4.add(readAnalog3());

    int16_t peakToPeak1 = channel1.peakToPeak();
    int16_t peakToPeak2 = channel2.peakToPeak();
    int16_t peakToPeak3 = channel3.peakToPeak();
    int16_t peakToPeak4 = channel4.peakToPeak();

    int16_t peakOutput1 = (peakToPeak1-OFFSET_PEAK_1)*SCALE_PEAK_1;
    peakOutput1 = limit(peakOutput1, 0, 255);
    DmxSimple.write(1, peakOutput1);

    // Testing: Control triac
    _delay_ms(500);
    if(counter % 2) {
      PORTB &= ~BV(PORTB0);
    } else {
      PORTB |= BV(PORTB0);
    }

    if(counter % 3) {
      PORTD &= ~BV(PORTD1);
    } else {
      PORTD |= BV(PORTD1);
    }

    if(counter % 5) {
      PORTD &= ~BV(PORTD7);
    } else {
      PORTD |= BV(PORTD7);
    }

    counter += 1;

    #ifdef DEBUG
      if(peakOutput1 > 100) {
        PORTD &= ~BV(PORTD2);
      }
    #endif
  }
}
