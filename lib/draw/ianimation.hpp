#ifndef __LIB_IANIMATION_HPP__
#define __LIB_IANIMATION_HPP__

#include <lib/core/timer.hpp>

namespace lib
{
	namespace draw
	{
		class SceneNode;
		class IAnimation
		{
		public:
			IAnimation(const u32 duration);
			virtual const std::string animationType() const = 0;
			virtual bool animate(SceneNode *const);
			virtual ~IAnimation();
		protected:
			u64 currentTime;
			u64 _duration;
			float _delta{ 0.0f };
			Timer _clock;
		};

		template <typename T>
		class IValueAnimation : public IAnimation
		{
		public:
			IValueAnimation(const s32 duration, const T&start, const T&end)
				: IAnimation(duration), _startValue(start), _endValue(end) {}
		protected:
			T _startValue;
			T _endValue;
		};
	}
}

#endif
