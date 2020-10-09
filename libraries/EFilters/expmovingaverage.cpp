#include "expmovingaverage.h"

#include "ecore/ethread.h"

float ExpMovingAverage::add(const float value) {
  if (_interval != 0) EThread::sleep(_interval);
  _value += (value - _value) * _coef;
  return _value;
}

