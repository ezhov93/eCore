#ifndef ETHREAD_H
#define ETHREAD_H

#include "ecore.h"

class EThread {
 public:
  typedef TaskHandle_t ThreadHandle;

  enum StackSize {
    SizeMinimal = configMINIMAL_STACK_SIZE,  // size_t to bytes
    SizeMedium = SizeMinimal * 2,
    SizeBig = SizeMinimal * 4,
    SizeMax = SizeMinimal * 8
  };
  enum Priority {
    PriorityLowest,
    PriorityLow,
    PriorityMedium,
    PriorityHigh,
    PriorityHighest
  };

  friend class ERtos;

  explicit EThread(const char *name, Priority priority = PriorityMedium,
                   size_t size = SizeMedium)
      : _name(name), _stackSize(size), _priority(priority), _lastWakeTime(0) {}
  ~EThread() { vTaskDelete(_handle); }
  const char *name() const { return _name; }
  void setPriority(Priority priority) {
    if (_handle != NULL) vTaskPrioritySet(_handle, priority);
    _priority = priority;
  }
  Priority priority() const { return _priority; }
  size_t stackSize() const { return _stackSize; }
  void resume() const { vTaskResume(_handle); }
  void resumeFromIrq() const { xTaskResumeFromISR(_handle); };
  void pause() const { vTaskSuspend(_handle); }
  void moveToCore() {
    xTaskCreate(taskFunction, _name, _stackSize, this,
                _priority, &_handle);
  }
  TaskHandle_t handle() const { return _handle; }

  static void sleep(size_t ms) { vTaskDelay(ECore::msToTick(ms)); }
  static void yield() { taskYIELD(); }
  struct Crittical {
    static void begin() { taskENTER_CRITICAL(); }
    static void end() { taskEXIT_CRITICAL(); }
  };

 protected:
  virtual void run() = 0;
  // void sleep(size_t ms) const { vTaskDelay(ECore::msToTick(ms)); }
  void sleepUntil(size_t ms) const {
    vTaskDelayUntil(const_cast<TickType_t *>(&_lastWakeTime),
                    ECore::msToTick(ms));
  }

 private:
  const char *_name;
  const size_t _stackSize;
  Priority _priority;
  TaskHandle_t _handle;
  TickType_t _lastWakeTime;
  void exec() {
    _lastWakeTime = xTaskGetTickCount();
    run();
  }
  static void taskFunction(void *thread) {
    static_cast<EThread *>(thread)->exec();
  }
};

#endif  // ETHREAD_H
