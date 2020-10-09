/*
 * @file  equeue.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Queue tamplate class.
 */

#ifndef EQUEUE_H
#define EQUEUE_H

#include "FreeRTOS.h"
#include "ethread.h"
#include "queue.h"

template <typename T, int Size>
class EQueue {
 public:
  EQueue() : _handle(xQueueCreate(Size, sizeof(T))) {}
  ~EQueue() { vQueueDelete(_handle); }
  void reset() const { xQueueReset(_handle); }
  size_t available() const { return Size - uxQueueSpacesAvailable(_handle); }
  void push(const T &item) const { xQueueSend(_handle, &item, portMAX_DELAY); }
  bool push(const T &item, const size_t ms) const {
    return xQueueSend(_handle, &item, ECore::msToTick(ms));
  }
  void pushToBack(const T &item) const {
    xQueueSendToBack(_handle, &item, portMAX_DELAY);
  }
  bool pushToBack(const T &item, const size_t ms) const {
    return xQueueSendToBack(_handle, &item, ECore::msToTick(ms));
  }
  void pushToFront(const T &item) const {
    xQueueSendToFront(_handle, &item, portMAX_DELAY);
  }
  bool pushToFront(const T &item, const size_t ms) const {
    return xQueueSendToFront(_handle, &item, ECore::msToTick(ms));
  }
  T pop() {
    T item;
    xQueueReceive(_handle, &item, portMAX_DELAY);
    return item;
  }
  bool pop(T &item, const size_t ms) {
    return xQueueReceive(_handle, &item, ECore::msToTick(ms));
  }
  T peek() {
    T item;
    xQueuePeek(_handle, &item, portMAX_DELAY);
    return item;
  }
  bool peek(T &item, const size_t ms) {
    return xQueuePeek(_handle, &item, ECore::msToTick(ms));
  }

  bool pushToBackFromIrq(const T &item) const {
    BaseType_t taskWoken = pdFALSE;
    bool status = xQueueSendToBackFromISR(_handle, &item, &taskWoken);
    if (taskWoken) portYIELD_FROM_ISR(taskWoken);
    return status;
  }

  bool pushToFrontFromIrq(const T &item) const {
    BaseType_t taskWoken = pdFALSE;
    bool status = xQueueSendToFrontFromISR(_handle, &item, &taskWoken);
    if (taskWoken) portYIELD_FROM_ISR(taskWoken);
    return status;
  }
  T popFromIrq() {
    T item;
    BaseType_t taskWoken = pdFALSE;
    xQueueReceiveFromISR(_handle, &item, &taskWoken);
    if (taskWoken) portYIELD_FROM_ISR(taskWoken);
    return item;
  }
  bool popFromIrq(T &item) {
    BaseType_t taskWoken = pdFALSE;
    bool status = xQueueReceiveFromISR(_handle, &item, &taskWoken);
    if (taskWoken) portYIELD_FROM_ISR(taskWoken);
    return status;
  }
  T peekFromIrq() {
    T item;
    BaseType_t taskWoken = pdFALSE;
    xQueuePeekFromISR(_handle, &item, &taskWoken);
    if(taskWoken) portYIELD_FROM_ISR(taskWoken);
    return item;
  }
  bool peekFromIrq(T &item) {
    BaseType_t taskWoken = pdFALSE;
    bool status = xQueuePeekFromISR(_handle, &item, &taskWoken);
    if(taskWoken) portYIELD_FROM_ISR(taskWoken);
    return status;
  }

 private:
  QueueHandle_t _handle;
};

#endif  // EQUEUE_H
