#ifndef __LIB_IANIMATION_HPP__
#define __LIB_IANIMATION_HPP__

#include <lib/core/timer.hpp>
#include <lib/include/types.hpp>
#include <lib/include/color.hpp>

#include <functional>

#ifndef CALL_MEMBER_FN
	#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
#endif


namespace lib
{
	namespace draw
	{
		class SceneNode;
		class IAnimation
		{
		public:
			IAnimation(const str&name) : m_name(name) {}
			virtual ~IAnimation() {}
			const str& name() const { return m_name; }

			virtual bool animate(SceneNode *node) = 0;
		protected:
			str m_name;
		};

		template <typename T, void (SceneNode::*setter)(const T&)>
		class Animation : public IAnimation
		{
		public:
			Animation(const str&name) : IAnimation{ name } {}
			virtual ~Animation() {}

			void setDuration(u64 duration) { m_duration = duration; }
			void setStartValue(const T&startValue) { m_startValue = startValue; }
			void setEndValue(const T&endValue) { m_endValue = endValue; }

			u64 duration() const { return m_duration; }
			const T& startValue() const { return m_startValue; }
			const T& endValue() const { return m_endValue; }

			virtual bool animate(SceneNode *node) override
			{
				currentTime = m_clock.getElapsedTime().asMilliSeconds();
				if (currentTime > m_duration) {
					m_delta = 1.0f;
					return false;
				}
				m_delta = (static_cast<f32>(currentTime) / m_duration);

				T deltaValue{ m_endValue - m_startValue };
				T finalValue{ m_startValue + (deltaValue*m_delta) };
				CALL_MEMBER_FN(*node, setter)(finalValue);

				return true;
			}

		protected:
			u64 currentTime;
			u64 m_duration;
			float m_delta{ 0.0f };
			Timer m_clock;
			T m_startValue;
			T m_endValue;
		};
	}
}

#undef CALL_MEMBER_FN

#endif
