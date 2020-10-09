/*
 * @file   enotify.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Task notifications observer classes
 */

#ifndef ENOTIFY_H
#define ENOTIFY_H

#include <stdint.h>

#include "ethread.h"

class ENotifiable {
 public:
  static bool wait(uint32_t &event, size_t ms = ECore::MaxDelay) {
    return xTaskNotifyWait(pdFALSE, /* Не очищать биты на входе. */
                           ~((uint32_t)(0)), /* На выходе очищаются все биты. */
                           &event, ECore::msToTick(ms));
  }
  static bool wait(size_t ms = ECore::MaxDelay) {
    return ulTaskNotifyTake(pdFALSE, /* Не очищать биты на входе. */
                            ECore::msToTick(ms));
  }
};

class ENotifyAbstract {
 public:
  explicit ENotifyAbstract(EThread &dest) : _dest(&dest) {}
  virtual ~ENotifyAbstract(){};
  virtual void emmit() = 0;
  virtual void emmit(uint32_t event) = 0;

 protected:
  EThread *_dest;
};

class ENotify : public ENotifyAbstract {
 public:
  explicit ENotify(EThread &dest) : ENotifyAbstract(dest) {}
  virtual void emmit() {
    xTaskNotifyGive(_dest->handle());
  }
  virtual void emmit(uint32_t event) {
    xTaskNotify(_dest->handle(), event, eSetBits); 
  }
};

class ENotifyFromIrq : public ENotifyAbstract {
 public:
  explicit ENotifyFromIrq(EThread &dest) : ENotifyAbstract(dest) {}
  virtual void emmit() {
    BaseType_t taskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(_dest->handle(), &taskWoken);
    if(taskWoken) portYIELD_FROM_ISR(taskWoken);
  }
  virtual void emmit(uint32_t event) {
    BaseType_t taskWoken = pdFALSE;
    xTaskNotifyFromISR(_dest->handle(), event, eSetBits,
                       &taskWoken);
    if(taskWoken) portYIELD_FROM_ISR(taskWoken);
  }
};

#endif  // ENOTIFY_H
