#include "camera.hpp"
#include <SFML/Graphics/View.hpp>

namespace lib
{
	namespace draw
	{
		class CameraPriv
		{
		public:
			CameraPriv() {}
			~CameraPriv() {}

			sf::View m_view;
		};

		Camera::Camera(const Rectf32 &rectangle) 
			: m_priv{ new CameraPriv() }, m_target(rectangle)
		{

		}

		Camera::~Camera() {}

		void Camera::setSize(const vector2df &size)
		{
			m_target.width = size.x;
			m_target.height = size.y;
		}
	}
}

