#ifndef UNIQUE_JTHREAD_H
#define UNIQUE_JTHREAD_H

#include<thread>

namespace clang_jthread {

class jthread {
public:
  template<typename Callable, typename... Args>
  explicit jthread(Callable&& f, Args&&... args)
    : t(std::forward<Callable>(f), std::forward<Args>(args)...) {}
  jthread(jthread&& other) noexcept : t(std::move(other.t)) {}

  jthread& operator=(jthread&& other) noexcept {
    if (this != &other) {
      if (t.joinable())
        t.join();
      t = std::move(other.t);
    }
    return *this;
  }

  jthread(jthread const&) = delete;
  jthread& operator=(jthread const&) = delete;

  ~jthread() {
    if (t.joinable())
      t.join();
  }
  
private:
  std::thread t;
};

} // End namespace clang_jthread

#endif