// Cpu frequency for util/delay.h
#define F_CPU 8000000

#define AVG_WINDOW 100

#define ADC_PRESCALER Atmega328p::ADC_PSV_32

#define PWM_PRESCALER Atmega328p::PSV_1

#define DMX_PRESCALER Atmega328p::PSV_128
#define DMX_PORT PORTB
#define DMX_PIN PORTB1

#define OFFSET_AVG_1 509
#define SCALE_AVG_1 32

#define OFFSET_PEAK_1 50
#define SCALE_PEAK_1 1

#define OFFSET_PEAK_2 50
#define SCALE_PEAK_2 1

#define OFFSET_PEAK_3 50
#define SCALE_PEAK_3 1

#define OFFSET_PEAK_4 50
#define SCALE_PEAK_4 1

//Enables debug messaging
#define DEBUG
