#ifndef AVERAGE_H
#define AVERAGE_H

class Average {
 public:
  explicit Average(int size = 3, int window = 1);
  ~Average();
  float add(const float);
  void clear();
  float value();

 private:
  int _size;
  int _window;
  float *_array;
  int _counter;
};

#endif  // AVERAGE_H
