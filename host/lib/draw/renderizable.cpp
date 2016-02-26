#include "renderizable.hpp"
#include <lib/core/window.hpp>
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		Renderizable::Renderizable(const std::string &name)
			: HasName{ name }
		{
			LOG_CONSTRUCT("Name: " << name << " of type");

		}

		u32 Renderizable::draw(lib::core::Window *window, lib::draw::RenderStates &states)
		{
			window;
			states;
			if (isVisible())
			{
//					window->draw()
//					window->draw(*getAsDrawable(),states);
				return 1;
			}
			return 0;
		}

		Renderizable::~Renderizable()
		{
		}

		void Renderizable::setPosition(const vector2df &pos, Alignment alignment)
		{
			switch (alignment)
			{
			default:
			case lib::draw::Alignment::Left:
				Transformable::setPosition(pos);
				break;
			case lib::draw::Alignment::Center:
				Transformable::setPosition(lib::vector2df{ pos.x - (getLocalBounds().width / 2.0f), pos.y - (getLocalBounds().height / 2.0f) });
				break;
			case lib::draw::Alignment::Right:
				Transformable::setPosition(lib::vector2df{ pos.x - (getLocalBounds().width), pos.y - (getLocalBounds().height) });
				break;
			}
		}

		void Renderizable::setPositionX(const float x, Alignment alignment /*= Alignment::Left*/)
		{
			const lib::vector2df position( Transformable::position() );
			switch (alignment)
			{
			default:
			case lib::draw::Alignment::Left:
				Transformable::setPosition(lib::vector2df{ x, position.y });
				break;
			case lib::draw::Alignment::Center:
			{
				Transformable::setPosition(lib::vector2df{ x - (getLocalBounds().width / 2.0f), position.y });
			}
				break;
			case lib::draw::Alignment::Right:
				Transformable::setPosition(lib::vector2df{ x - (getLocalBounds().width), position.y });
				break;
			}
		}

		void Renderizable::setPositionY(const float y, Alignment alignment /*= Alignment::Left*/)
		{
			const lib::vector2df position(Transformable::position());
			switch (alignment)
			{
			default:
			case lib::draw::Alignment::Left:
				Transformable::setPosition(lib::vector2df{ position.x, y });
				break;
			case lib::draw::Alignment::Center:
				Transformable::setPosition(lib::vector2df{ position.x, y - (getLocalBounds().height / 2.0f) });
				break;
			case lib::draw::Alignment::Right:
				Transformable::setPosition(lib::vector2df{ position.x, y - (getLocalBounds().height) });
				break;
			}
		}

		void Renderizable::setAlignment(Alignment alignment)
		{
			setPosition(position(), alignment);
		}
	}
}
