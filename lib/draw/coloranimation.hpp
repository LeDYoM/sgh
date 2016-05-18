#ifndef __LIB_COLORANIMATION_HPP__
#define __LIB_COLORANIMATION_HPP__

#include "ianimation.hpp"
#include <lib/include/types.hpp>
#include <lib/include/color.hpp>
namespace lib
{
	namespace draw
	{
		namespace anim
		{
			class ColorAnimation : public IValueAnimation<lib::draw::Color>
			{
			public:
				ColorAnimation(const s32 duration, const lib::draw::Color &startColor, const lib::draw::Color &endColor);
				static sptr<ColorAnimation> create(const s32 duration, const lib::draw::Color &startColor, const lib::draw::Color &endColor);
				static sptr<ColorAnimation> create(const s32 duration, const lib::draw::Color &endColor);
				virtual ~ColorAnimation();
				virtual bool animate(SceneNode *const) override;
				virtual const std::string animationType() const { return "ColorAnimation"; }
			};
		}
	}
}

#endif
