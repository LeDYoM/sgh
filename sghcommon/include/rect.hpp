#ifndef __LIB_RECT_HPP__
#define __LIB_RECT_HPP__

#include "types.hpp"

namespace lib
{
	template <typename T>
	struct Rect
	{
		T left, top, width, height;

		inline Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight) : left{ rectLeft }, top{ rectTop }, width{ rectWidth }, height{ rectHeight } { }
		inline explicit Rect() : Rect{ {}, {}, {}, {} } {}
		inline Rect(const vector2d<T>& position, const vector2d<T>& size) : Rect{ position.x, position.y, size.x, size.y } {}
		inline Rect(const Rect&) = default;
		template <typename U>
		inline Rect(const Rect<U>& rectangle) :
			left{ static_cast<T>(rectangle.left) }, top{ static_cast<T>(rectangle.top) },
			width{ static_cast<T>(rectangle.width) }, height{ static_cast<T>(rectangle.height) } {}

//		static_assert(std::is_move_constructible<Rect>(), "Rect<T> not movable");

		inline vector2d<T> center() const { return vector2d<T> {left + (width / static_cast<T>(2)), 
			top + (height / static_cast<T>(2))}; }

		inline bool contains(T x, T y) const
		{
			T minX = std::min(left, static_cast<T>(left + width));
			T maxX = std::max(left, static_cast<T>(left + width));
			T minY = std::min(top, static_cast<T>(top + height));
			T maxY = std::max(top, static_cast<T>(top + height));

			return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
		}

		bool contains(const vector2d<T>& point) const
		{
			return contains(point.x, point.y);
		}

		bool intersects(const Rect<T>& rectangle) const
		{
			return intersects(rectangle, std::move(Rect<T>()));
		}

		bool intersects(const Rect<T>& rectangle, Rect<T>& intersection) const
		{
			T r1MinX = std::min(left, right());
			T r1MaxX = std::max(left, right());
			T r1MinY = std::min(top, bottom());
			T r1MaxY = std::max(top, bottom());

			T r2MinX = std::min(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
			T r2MaxX = std::max(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
			T r2MinY = std::min(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));
			T r2MaxY = std::max(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));

			// Compute the intersection boundaries
			T interLeft = std::max(r1MinX, r2MinX);
			T interTop = std::max(r1MinY, r2MinY);
			T interRight = std::min(r1MaxX, r2MaxX);
			T interBottom = std::min(r1MaxY, r2MaxY);

			// If the intersection is valid (positive non zero area), then there is an intersection
			if ((interLeft < interRight) && (interTop < interBottom)) {
				intersection = Rect<T>(interLeft, interTop, interRight - interLeft, interBottom - interTop);
				return true;
			}
			else {
				intersection = Rect<T>(0, 0, 0, 0);
				return false;
			}
		}

		inline bool operator==(const Rect<T> &r) const
		{
			return (left == r.left && width == r.width && top == r.top && height == r.height);
		}

		inline bool operator!=(const Rect<T> &r) const
		{
			return !(operator==(r));
		}

		inline void setLeft(const T&nleft) { left = nleft; }
		inline void setTop(const T&nTop) { top = nTop; }
		inline void setLeftTop(const vector2d<T>&nleftTop) { setLeft(nleftTop.x); setTop(nleftTop.y); }
		inline void move(const vector2d<T>&relativePosition) { left += relativePosition.x; top += relativePosition.y; }
		inline void setSize(const vector2d<T>&nsize) { width = nsize.x; height = nsize.y; }

		inline vector2d<T> leftTop() const { return vector2d<T>{left, top}; }
		inline vector2d<T> size() const { return vector2d<T>{width, height}; }
		inline T right() const { return left + width; }
		inline T bottom() const { return top + height; }
		inline vector2d<T> rightBottom() const { return vector2d<T>{right(), bottom()}; }
		inline vector2d<T> rightTop() const { return vector2d<T>{right(), top}; }
		inline vector2d<T> leftBottom() const { return vector2d<T>{left, bottom()}; }
	};

	using Rects32 = lib::Rect<s32>;
	using Rectf32 = lib::Rect<f32>;
	using Rectu32 = lib::Rect<u32>;

}

#endif
