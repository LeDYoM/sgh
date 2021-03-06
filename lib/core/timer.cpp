#include "timer.hpp"
#include <chrono>

namespace lib
{
	typedef std::chrono::high_resolution_clock clock_t;
	static clock_t::time_point globalStart;

	struct TimePrivate
	{
	public:
		std::chrono::microseconds _micrseconds;
		TimePrivate::TimePrivate(std::chrono::microseconds microseconds)
			: _micrseconds{microseconds} {}

		TimePrivate::TimePrivate(TimePrivate &&rh) : _micrseconds{ std::move(rh._micrseconds) } { }
	};

	Time::Time()
		: m_private{ std::make_unique<TimePrivate>(std::chrono::microseconds::zero()) } { }

	Time::Time(Time &&rh)
	{
		m_private = std::move(rh.m_private);
	}

	Time::~Time() {	}

	Time &Time::operator+=(const Time &rh)
	{
		m_private->_micrseconds += rh.m_private->_micrseconds;
		return *this;
	}

	Time Time::operator-(const Time &rh) const
	{
		Time t;
		t.m_private = std::make_unique<TimePrivate>(this->m_private->_micrseconds - rh.m_private->_micrseconds);
		return t;
	}

	Time & Time::operator=(const Time &other)
	{
		m_private->_micrseconds = other.m_private->_micrseconds;
		return *this;
	}

	u64 Time::asMicroSeconds() const
	{
		return m_private->_micrseconds.count();
	}

	u64 Time::asMilliSeconds() const
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_private->_micrseconds).count();
	}

	u64 Time::asSeconds() const
	{
		return std::chrono::duration_cast<std::chrono::seconds>(m_private->_micrseconds).count();
	}

	void Time::setZero()
	{
		if (m_private)
			m_private->_micrseconds = std::chrono::microseconds::zero();
	}

	struct TimerPrivate
	{

		clock_t::time_point start;
		std::chrono::microseconds pausedTime;
		TimerPrivate()
		{
			start = clock_t::now();
			pausedTime = std::chrono::microseconds::zero();
		}
	};

	Timer::Timer()
		: _timerPrivate{ new TimerPrivate } {}

	Timer::~Timer() {}

	const Time Timer::getElapsedTime() const
	{
		std::chrono::microseconds ellapsed = std::chrono::duration_cast<std::chrono::microseconds>(clock_t::now() - _timerPrivate->start);
		Time t;
		t.m_private = std::make_unique<TimePrivate>(ellapsed);
		return t;
	}

	void Timer::restart()
	{
		_timerPrivate->start = clock_t::now();
	}

	void PausableTimer::pause()
	{
		if (!_paused)
		{
			_paused = true;
			_pausedTimer.restart();
		}
	}

	void PausableTimer::resume()
	{
		if (_paused)
		{
			_paused = false;
			_pausedTime += _pausedTimer.getElapsedTime();
		}
	}

	bool PausableTimer::switchPause()
	{
		_paused ? resume() : pause();
		return _paused;
	}

	const Time PausableTimer::getElapsedTime() const
	{
		Time t = (Timer::getElapsedTime() - _pausedTime);
		if (_paused)
			t = t - _pausedTimer.getElapsedTime();
		return t;
	}

	void PausableTimer::restart()
	{
		_pausedTime.setZero();
		_paused = false;
		Timer::restart();
	}

}
