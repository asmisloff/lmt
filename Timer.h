#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <thread>

class Timer {
 public:
	Timer();
	/** 
	 * Установить таймер на ms миллисекунд.
	 * По истечении времени вывести сообщение, что время вышло.
	 */
	void count(int ms, void (*on_expire)());
	/** Остановить таймер до истечения времени. */
	void halt();
	/** Время до истечения таймера в миллисекундах или 0, если таймер не устаноновлен. */
	long left();
 private:
	long mark = 0;
	bool active = false;
	bool halted = false;
	std::thread thread;
	void (*on_expire)() = nullptr;
	static inline long now();
};

long Timer::now() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::system_clock::now().time_since_epoch()
  ).count();
}

#endif // TIMER_H