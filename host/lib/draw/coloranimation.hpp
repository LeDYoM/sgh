#ifndef __LIB_COLORANIMATION_HPP__
#define __LIB_COLORANIMATION_HPP__

#include "ianimation.hpp"
#include <lib/include/types.hpp>

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			namespace anim
			{
				class ColorAnimation : public IValueAnimation<lib::scn::draw::Color>
				{
				public:
					ColorAnimation(const s32 duration, sptr<Renderizable> node, const lib::scn::draw::Color &startColor, const lib::scn::draw::Color &endColor);
					static sptr<ColorAnimation> create(const s32 duration, sptr<Renderizable> node, const lib::scn::draw::Color &startColor, const lib::scn::draw::Color &endColor);
					static sptr<ColorAnimation> create(const s32 duration, sptr<Renderizable> node, const lib::scn::draw::Color &endColor);
					virtual ~ColorAnimation();
					virtual bool animate();
					virtual const std::string animationType() const { return "ColorAnimation"; }
				};
			}
		}
	}
}

#endif
