#include "tile.hpp"
#include <lib/draw/NodeShape.hpp>

namespace zoper
{
	lib::u32 Tile::_tileCounter{ 0 };

	Tile::Tile(lib::draw::RenderGroup *const p_parent, lib::board::BoardTileData data, const lib::vector2df &size) 
		: GameBaseTile{ p_parent, data, size, std::string("tile") + std::to_string(_tileCounter) }
	{
		++_tileCounter;
		color = getColorForToken();
	}

	Tile::~Tile()
	{
	}

	void Tile::resetTileCounter()
	{
		_tileCounter = 0;
	}
}
