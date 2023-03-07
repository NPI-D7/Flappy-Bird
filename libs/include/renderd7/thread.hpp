#pragma once
#include <3ds.h>
#include <atomic>
#include <functional>
#include <renderd7/parameter.hpp>
#include <string>

using CTRU_Thread = Thread;

#define THREAD_STACK_SIZE 0x1000

namespace RenderD7 {
namespace Threads {
inline bool threadrunning = false;

struct Thread {
  Handle handle;
  void (*ep)(void);
  bool finished;
  void *stacktop;
};

bool Create();
bool Join();
void Exit();
} // namespace Threads
class Thread {
public:
  /**
   * @brief Default constructor
   * @note This should only be called when calling m3d::Thread::initialize()
   * before calling m3d::Thread::start()
   */
  Thread();

  /**
   * @brief Constructs the thread
   * @param t_function  The thread function
   * @param t_parameter The parameter to pass to the function
   * @param t_autostart Whether the thread should start instantly
   * @param t_detached  Whether the thread starts detached or not
   * @param t_stackSize The stacksize allocated for the thread in bytes (rounded
   * to multiples of 8 bytes)
   * @note t_function needs to be of type `void` and take one (and only one)
   * parameter of type m3d::Parameter
   * @warning If the thread priority is lower than the priority of the calling
   * thread, the thread will never get executed. Use
   * m3d::Thread::getCurrentPriority() to get the priority of the current thread
   */
  Thread(std::function<void(RenderD7::Parameter)> t_function,
         RenderD7::Parameter t_parameter = nullptr, bool t_autostart = false,
         bool t_detached = false,
         unsigned long long int t_stackSize = 4 * 1024);

  /**
   * @brief Destructs the thread
   */
  virtual ~Thread();

  /**
   * @brief Initializes the thread
   * @param t_function  The thread function
   * @param t_parameter The parameter to pass to the function
   * @param t_autostart Whether the thread should start instantly
   * @param t_detached  Whether the thread starts detached or not
   * @param t_stackSize The stacksize allocated for the thread in bytes (rounded
   * to multiples of 8 bytes)
   * @note t_function needs to be of type `void` and take one (and only one)
   * parameter of type m3d::Parameter
   * @warning If the thread priority is lower than the priority of the calling
   * thread, the thread will never get executed. Use
   * m3d::Thread::getCurrentPriority() to get the priority of the current thread
   */
  void initialize(std::function<void(RenderD7::Parameter)> t_function,
                  RenderD7::Parameter t_parameter = nullptr,
                  bool t_autostart = false, bool t_detached = false,
                  unsigned long long int t_stackSize = 4 * 1024);

  /**
   * @brief Sets the size of the stack that gets allocated for the next thread
   * that get's started
   * @param t_stackSize The allocated space in bytes (rounded to multiples of 8
   * bytes)
   */
  void setStackSize(unsigned long long int t_stackSize);

  /**
   * @brief Starts the thread. To restart it, call Thread::join() before
   * @param t_detached Whether the thread should start detached or not
   */
  void start(bool t_detached = false);

  /**
   * @brief Detaches the thread
   */
  void kill();

  /**
   * @brief Waits for the thread to finish
   * @param t_timeout The timeout in nanoseconds. Leave it for no timeout
   */
  void join(long long unsigned int t_timeout = U64_MAX);

  bool isRunning();

  /**
   * @brief Puts the thread to sleep
   *
   * This is needed if you have multiple threads running at the same time. It
   * doesn't affect the execution-time of the thread, it just makes it possible
   * for the other threads to get their chance to shine.
   */
  static void sleep();

  /**
   * @brief Sleeps for the given time
   * @param t_milliseconds The time to sleep in milliseconds
   */
  static void sleep(int t_milliseconds);

private:
  struct ThreadData {
    RenderD7::Parameter m_parameter;
    std::function<void(RenderD7::Parameter)> m_function;
    std::atomic<bool> *m_running;
  };

  static void threadFunction(void *t_arg);
  /* data */
  int m_priority, m_stackSize;
  bool m_started;
  std::atomic<bool> m_running;
  RenderD7::Thread::ThreadData m_data;
  CTRU_Thread m_thread;
};
} // namespace RenderD7
