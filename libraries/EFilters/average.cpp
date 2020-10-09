#include "average.h"

#include <string.h>

// simple avarege filter class
Average::Average(int size, int window) {
  _size = size;
  _window = window;
  _counter = 0;
  _array = new float[size];
}

Average::~Average() { delete[] _array; }

float Average::add(float value) {
  _array[_counter++] = value;
  if (_counter >= _size) _counter = 0;
  return Average::value();
}

void Average::clear() { memset(_array, 0, sizeof(_array[0]) * _size); }

float Average::value() {
  float *begin;
  float *array = null;
  float tmp = 0.f;
  if (_size > _window) {
    array = new float[_size];
    memcpy(array, _array, sizeof(array[0]) * _size);
    ESort::selection<float>(_array, _size);
    begin = _array + ((_size - _window) >> 1);
  } else
    begin = _array;
  for (int i = 0; i < _window; ++i) tmp += begin[i];
  if (array != null) delete[] array;
  return tmp / _window;
}