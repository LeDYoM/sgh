#include "coloranimation.hpp"
#include "rendernode.hpp"

namespace lib
{
	namespace draw
	{
		namespace anim
		{
			ColorAnimation::ColorAnimation(const s32 duration, sptr<RenderNode> node, const lib::draw::Color &startColor, const lib::draw::Color &endColor)
				: IValueAnimation(duration, node, startColor, endColor)
			{
			}


			ColorAnimation::~ColorAnimation()
			{
			}

			lib::draw::Color interpolate(const lib::draw::Color &color, float interpolateValue)
			{
				lib::draw::Color value{ color };
				value.r = static_cast<lib::u8>(static_cast<float>(value.r) * interpolateValue);
				value.g = static_cast<lib::u8>(static_cast<float>(value.g) * interpolateValue);
				value.b = static_cast<lib::u8>(static_cast<float>(value.b) * interpolateValue);
				value.a = static_cast<lib::u8>(static_cast<float>(value.a) * interpolateValue);
				return value;
			}

			bool ColorAnimation::animate()
			{
				bool result = IAnimation::animate();
				lib::draw::Color deltaColor{ _endValue - _startValue };
				lib::draw::Color finalColor{ _startValue + (interpolate(deltaColor,_delta)) };
				_node->setColor(finalColor);
				return result;
			}

			sptr<ColorAnimation> ColorAnimation::create(const s32 duration, sptr<RenderNode> node, const lib::draw::Color &startColor, const lib::draw::Color &endColor)
			{
				auto animation = std::make_shared<ColorAnimation>(duration, node, startColor, endColor);
				return animation;
			}

			sptr<ColorAnimation> ColorAnimation::create(const s32 duration, sptr<RenderNode> node, const lib::draw::Color &endColor)
			{
				auto animation = std::make_shared<ColorAnimation>(duration, node, endColor, endColor);
				return animation;
			}
		}
	}
}
