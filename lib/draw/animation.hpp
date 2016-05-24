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
		using AnimationStartedCallback = std::function<void()>;
		using AnimationFinishedCallback = std::function<void()>;

		class SceneNode;
		class IAnimation
		{
		public:
			IAnimation(const str&name) : m_name(name), m_animationStartedCallback{ nullptr }, m_animationFinishedCallback{ nullptr },
				m_currentTime{ 0 }, m_duration{ 0 }, m_delta{ 0.0f }, m_running{ false } {}
			virtual ~IAnimation() {}

			const str& name() const { return m_name; }

			void start() {
				if (!m_running) {
					m_running = true;
					if (m_animationStartedCallback) {
						m_animationFinishedCallback();
					}
				}
			}
			
			void finish()
			{
				if (m_running) {
					m_running = false;
					if (m_animationFinishedCallback) {
						m_animationFinishedCallback();
					}
				}
			}

			virtual bool animate(SceneNode *node) = 0;
			void setAnimationStartedCallback(AnimationStartedCallback asc);
			void setAnimationFinishedCallback(AnimationFinishedCallback afc);

		protected:
			str m_name;
			AnimationStartedCallback m_animationStartedCallback;
			AnimationFinishedCallback m_animationFinishedCallback;

			u64 m_currentTime;
			u64 m_duration;
			float m_delta;
			Timer m_clock;

		private:
			bool m_running;

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
				m_currentTime = m_clock.getElapsedTime().asMilliSeconds();
				if (m_currentTime > m_duration) {
					m_delta = 1.0f;
					finish();
					return false;
				}
				m_delta = (static_cast<f32>(m_currentTime) / m_duration);

				T deltaValue{ m_endValue - m_startValue };
				T finalValue{ m_startValue + (deltaValue*m_delta) };
				CALL_MEMBER_FN(*node, setter)(finalValue);

				return true;
			}

		protected:
			T m_startValue;
			T m_endValue;
		};
	}
}

#undef CALL_MEMBER_FN

#endif
