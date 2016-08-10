#include "font.hpp"
#include <lib/drivers/render/font.hpp>

namespace lib
{
	namespace draw
	{
		Font::Font(drivers::render::Font *tHandle)
			: m_driverFont{ tHandle } {}

		Font::~Font()
		{
		}
	}
}
