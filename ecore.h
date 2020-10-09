/*
 * @file   ecore.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Main include file for the eCore.
 */

#ifndef ECORE_H
#define ECORE_H

#include "FreeRTOS.h"
#include "task.h"

#define E_DISABLE_COPY(Class) \
  Class(const Class &);       \
  Class &operator=(const Class &);

template <typename T>
T clearSwap(T &val) {
  T tmp(val);
  memset(&val, 0, sizeof(T));
  return tmp;
}

class ECore {
 public:
  enum State { Suspend, NotStarted, Running };
  static const size_t MaxDelay = portMAX_DELAY * portTICK_PERIOD_MS;
  static void exec() { vTaskStartScheduler(); }
  static unsigned int tickCount() { return xTaskGetTickCount(); };
  static State state() { return static_cast<State>(xTaskGetSchedulerState()); }
  static int numberOfThreads() { return uxTaskGetNumberOfTasks(); };
  static void threadList(char *str) { return vTaskList(str); }
  static size_t msToTick(const size_t ms) {
    return (size_t)ms / (size_t)(portTICK_PERIOD_MS);
  }
  static size_t tickToMs(const size_t tick) {
    return tick * (portTICK_PERIOD_MS);
  }
  static size_t millis() { return tickCount() * portTICK_PERIOD_MS; }
  static void setCoreClock(float mhz);
};

#endif  // ECORE_H
