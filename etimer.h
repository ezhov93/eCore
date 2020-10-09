#ifndef THREAD_H
#define THREAD_H

class Thread {
 public:
  Thread(const char *name);
  ~Thread();
  void setPriority(unsigned long priority) { _priority = priority; }
  unsigned long priority() const { return _priority; }
  unsigned short stackSize() const { return _stackDepth; }
  void resume();
  void pause();
  void moveToExec();
  static void exec();

 protected:
  virtual void run() = 0;
  void sleep(int ms);

 private:
  const char *_name;
  unsigned short _stackDepth;
  unsigned long _priority;
  static void toTaskFunction(void *thread) {
    static_cast<Thread *>(thread)->run();
  }
  void *_handle;
};

#endif  // THREAD_H
