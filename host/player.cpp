#include "player.hpp"
#include "gamescene.hpp"

namespace zoper
{
	Player::Player(lib::draw::RenderGroup *const p_parent, const lib::vector2du32 &bPosition, const lib::vector2df &size)
		: GameBaseTile{ p_parent, 0, size, "player" },
		playerDirection{ Direction::Up }
	{
		setPointCount(3);
		color = getColorForToken();
		setBoardPosition(bPosition);
	}

	Player::~Player()
	{
	}

	void Player::setBoardPosition(const lib::vector2du32 &np)
	{
		_boardPosition = np;
	}

	void Player::setCurrentDirection(const Direction & direction)
	{
		playerDirection = direction;
	}
}
