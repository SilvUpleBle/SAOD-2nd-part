#pragma once
#include <chrono>
#include <iostream>
template <typename T>
class Timer {
public:
	Timer() = delete;
	~Timer() = delete;
	static void reset() {
		beg_ = clock_::now();
	}

	static T elapsed_minutes() {
		return std::chrono::duration_cast<std::chrono::duration<T, std::ratio<60> >>(clock_::now() - beg_).count();
	}

	static T elapsed_seconds() {
		return std::chrono::duration_cast<std::chrono::duration<T, std::ratio<60> >>(clock_::now() - beg_).count();
	}

	static T elapsed_milliseconds() {
		return std::chrono::duration<T, std::milli>(clock_::now() - beg_).count();
	}

	static void elapsed_microseconds() {
		auto t = clock_::now();
		typedef std::chrono::microseconds ms;
		typedef std::chrono::duration<T> Tsec;
		Tsec Ts = clock_::now() - beg_;
		ms d = std::chrono::duration_cast<ms>(Ts);
		std::cout << d.count() << " microsec\n";
	}

	static void elapsed_nanoseconds() {
		auto t = clock_::now();
		typedef std::chrono::nanoseconds ms;
		typedef std::chrono::duration<T> Tsec;
		Tsec Ts = clock_::now() - beg_;
		ms d = std::chrono::duration_cast<ms>(Ts);
		std::cout << d.count() << " nanosec\n";
	}

private:
	typedef std::chrono::high_resolution_clock clock_;
	static std::chrono::time_point<std::chrono::high_resolution_clock> beg_;
};


