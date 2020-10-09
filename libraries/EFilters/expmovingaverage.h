#ifndef EXPMOVINGAVERAGE_H
#define EXPMOVINGAVERAGE_H

class ExpMovingAverage {
 public:
  ExpMovingAverage(const float coef = 0.f, const int interval = 0)
      : _coef(coef), _value(0), _interval(interval) {}
  void setCoef(const float coef) { _coef = coef; }
  void setInterval(const int interval) { _interval = interval; }
  float add(const float);
  float value() const { return _value; }
  void reset() { _value = 0; }
  void reset(const float init) { _value = init; }

 private:
  float _coef;
  float _value;
  int _interval;
};

#endif  // EXPMOVINGAVERAGE_H
