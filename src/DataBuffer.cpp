#include "config.h"

#define __STDC_LIMIT_MACROS
#include <stdlib.h>

#include "DataBuffer.h"

DataBuffer::DataBuffer(uint16_t size, int16_t initialValue)
    : size(size), cursor(0) {
  buffer = (int16_t *)malloc(size * sizeof(int16_t));

  for (int i = 0; i < size; i++) {
    buffer[i] = initialValue;
  }
}

void DataBuffer::add(int16_t value) {
  buffer[cursor] = value;
  cursor = (cursor + 1) % size;
}

int16_t DataBuffer::average() {
  int32_t sum = 0;
  for (int i = 0; i < size; i++) {
    sum += buffer[i];
  }

  return sum / size;
}

int16_t DataBuffer::peakToPeak() {
  int16_t max = INT16_MIN;
  int16_t min = INT16_MAX;
  for (int i = 0; i < size; i++) {
    int16_t value = buffer[i];
    if (max < value) {
      max = value;
    }
    if (min > value) {
      min = value;
    }
  }

  int32_t amplitude = max - min;
  if(amplitude > INT16_MAX)
    return INT16_MAX;
  if(amplitude < INT16_MIN)
    return INT16_MIN;
  return amplitude;
}