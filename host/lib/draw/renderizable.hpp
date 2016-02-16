#ifndef __LIB_RENDERIZABLE_HPP__
#define __LIB_RENDERIZABLE_HPP__

#include "hasname.hpp"
#include "idrawable.hpp"
#include <SFML/Graphics.hpp>
#include <lib/include/rect.hpp>

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			enum class Alignment : u8
			{
				Left = 0,
				Center = 1,
				Right = 2
			};

			class Renderizable : public lib::core::HasName, public IDrawable, public sf::Transformable
			{
			public:
				explicit Renderizable(const std::string &name);
				virtual ~Renderizable();

				virtual u32 draw(lib::core::Window *window, lib::scn::draw::RenderStates &states) override;
				virtual void setColor(const lib::scn::draw::Color &color) = 0;

				virtual Rectf32 getLocalBounds() const = 0;
				virtual Rectf32 getGlobalBounds() const = 0;

				// Some useful shortcuts
				using sf::Transformable::setPosition;
				void setPosition(const sf::Vector2f &pos, Alignment alignment);
				void setPositionX(const float x, Alignment alignment = Alignment::Left);
				void setPositionY(const float y, Alignment alignment = Alignment::Left);
				void setAlignment(Alignment alignment);
			};
		}
	}
}

#endif
