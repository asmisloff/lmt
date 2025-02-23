#include "./Timer.h"
#include <chrono>

Timer::Timer() {
  thread = std::thread([this] {
    while (!halted) {
      if (active && left() < 0) {
        active = false;
        if (on_expire != nullptr) {
          on_expire();
        }
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  });
  thread.detach();
}

void Timer::count(int ms, void (*on_expire)()) {
  mark = now() + ms;
  active = true;
  this->on_expire = on_expire;
}

void Timer::halt() {
  halted = true;
}

long Timer::left() {
  return mark - now();
}