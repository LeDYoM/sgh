#ifndef __LIB_RENDERIZABLE_HPP__
#define __LIB_RENDERIZABLE_HPP__

#include "hasname.hpp"
#include "idrawable.hpp"
#include <lib/include/rect.hpp>
#include "transformable.hpp"

namespace lib
{
	namespace draw
	{
		enum class Alignment : u8
		{
			Left = 0,
			Center = 1,
			Right = 2
		};

		class Renderizable : public lib::core::HasName, public IDrawable, public Transformable
		{
		public:
			explicit Renderizable(const std::string &name);
			virtual ~Renderizable();

			virtual u32 draw(lib::core::Window *window, lib::draw::RenderStates &states) override;
			virtual void setColor(const lib::draw::Color &color) = 0;

			virtual Rectf32 getLocalBounds() const = 0;
			virtual Rectf32 getGlobalBounds() const = 0;

			// Some useful shortcuts
			using Transformable::setPosition;
			void setPosition(const vector2df &pos, Alignment alignment);
			void setPositionX(const f32 x, Alignment alignment = Alignment::Left);
			void setPositionY(const f32 y, Alignment alignment = Alignment::Left);
			void setAlignment(Alignment alignment);
		};
	}
}

#endif
