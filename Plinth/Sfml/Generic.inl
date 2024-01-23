//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2024 M.J.Silk
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M.J.Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Generic.hpp"
#include "../Range.hpp"
#include <cmath>
#include "../Tween.hpp"

namespace plinth
{
	namespace Sfml
	{

constexpr pl::Range<unsigned char> colorComponentRange{ 0_uc, 255_uc };



// SFML from Plinth

inline sf::Vector2f vector2(const Vector2d& vector)
{
	return{ static_cast<float>(vector.x), static_cast<float>(vector.y) };
}

inline sf::Vector2i vector2(const Vector2i& vector)
{
	return{ vector.x, vector.y };
}

inline sf::Vector2u vector2(const Vector2u& vector)
{
	return{ vector.x, vector.y };
}

inline sf::Vector3f vector3(const Vector3d& vector)
{
	return{ static_cast<float>(vector.x), static_cast<float>(vector.y), static_cast<float>(vector.z) };
}

inline sf::Vector3i vector3(const Vector3i& vector)
{
	return{ vector.x, vector.y, vector.z };
}

inline sf::Vector3i vector3(const Vector3u& vector)
{
	return{ static_cast<int>(vector.x), static_cast<int>(vector.y), static_cast<int>(vector.z) };
}


// Plinth from SFML

inline Vector2d vector2(const sf::Vector2f& vector)
{
	return{ vector.x, vector.y };
}

inline Vector2i vector2(const sf::Vector2i& vector)
{
	return{ vector.x, vector.y };
}

inline Vector2u vector2(const sf::Vector2u& vector)
{
	return{ vector.x, vector.y };
}

inline Vector3d vector3(const sf::Vector3f& vector)
{
	return{ static_cast<double>(vector.x), static_cast<double>(vector.y), static_cast<double>(vector.z) };
}

inline Vector3i vector3(const sf::Vector3i& vector)
{
	return{ vector.x, vector.y, vector.z };
}














inline sf::Color colorFromValue(long int value)
{
	return colorFromRgb(Color::Rgb(value));
}

inline sf::Color colorFromRgb(const Color::Rgb& rgb)
{
	return sf::Color(Tween::linear(0_uc, 255_uc, rgb.r), Tween::linear(0_uc, 255_uc, rgb.g), Tween::linear(0_uc, 255_uc, rgb.b));
}

inline Color::Rgb rgbFromColor(const sf::Color& color)
{
	return Color::Rgb{
		Tween::inverseLinear(0_uc, 255_uc, color.r),
		Tween::inverseLinear(0_uc, 255_uc, color.g),
		Tween::inverseLinear(0_uc, 255_uc, color.b) };
}

inline float lengthSquared(const sf::Vector2f& vector)
{
	return vector.x * vector.x + vector.y * vector.y;
}

inline float length(const sf::Vector2f& vector)
{
	return std::sqrt(lengthSquared(vector));
}

inline float lengthSquared(const sf::Vector3f& vector)
{
	return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
}

inline float length(const sf::Vector3f& vector)
{
	return std::sqrt(lengthSquared(vector));
}

inline float dotProduct(const sf::Vector3f& a, const sf::Vector3f& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return a.x * b.x + a.y * b.y;
}

inline sf::Vector3f crossProduct(const sf::Vector3f& a, const sf::Vector3f& b)
{
	return
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

inline float crossProductPoints(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return{ a.x * b.y - b.x * a.y };
}

inline bool CCW(const sf::Vector2f& point1, const sf::Vector2f& point2, const sf::Vector2f& point3)
{
	return (point3.y - point1.y) * (point2.x - point1.x) > (point2.y - point1.y) * (point3.x - point1.x);
}

// vector of (2) lines. line is a vector of (2) vector2fs (the points of the line).
// i.e. { { line1.x, line.y }, { line2.x, line2.y } }
inline bool doLinesIntersect(const std::vector<std::vector<sf::Vector2f>>& lines)
{
	if (lines.size() != 2_uz)
		return false;
	if ((lines[0_uz].size() != 2_uz) || (lines[1_uz].size() != 2_uz))
		return false;

	return	(	CCW(lines[0_uz][0_uz], lines[1_uz][0_uz], lines[1_uz][1_uz]) !=
				CCW(lines[0_uz][1_uz], lines[1_uz][0_uz], lines[1_uz][1_uz])) &&
			(	CCW(lines[0_uz][0_uz], lines[0_uz][1_uz], lines[1_uz][0_uz]) !=
				CCW(lines[0_uz][0_uz], lines[0_uz][1_uz], lines[1_uz][1_uz]));
}

inline bool isPointInsidePolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygonVertices)
{
	return isPointInsidePolygon(point, polygonVertices, boundingBox(polygonVertices));
}

inline bool isPointInsidePolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygonVertices, const sf::FloatRect& boundingBox)
{
	if (!boundingBox.contains(point))
		return false;

	bool isInside{ false };
	sf::Vector2f pointOutsideBoundingBox{ boundingBox.left - 1.f, boundingBox.top - 1.f };
	for (std::size_t v{ 0_uz }, w{ polygonVertices.size() - 1_uz }; v < polygonVertices.size(); w = v++)
	{
		if (doLinesIntersect({ { polygonVertices[v], polygonVertices[w] }, { pointOutsideBoundingBox, point } }))
			isInside = !isInside;
	}
	return isInside;
}

inline bool doClosedPolylinesIntersect(const std::vector<sf::Vector2f>& a, const std::vector<sf::Vector2f>& b)
{
	for (std::size_t l{ 0_uz }, m{ a.size() - 1_uz }; l < a.size(); m = l++)
	{
		for (std::size_t v{ 0_uz }, w{ b.size() - 1_uz }; v < b.size(); w = v++)
		{
			if (doLinesIntersect({ { a[l], a[m] }, { b[v], b[w] } }))
				return true;
		}
	}
	return false;
}

inline bool doTransformedRectsIntersect(const sf::FloatRect& rect1, const sf::Transform& transform1, const sf::FloatRect& rect2, const sf::Transform& transform2)
{
	if (!transform1.transformRect(rect1).intersects(transform2.transformRect(rect2)))
		return false;

	const sf::Vector2f rect1bottomRight{ rect1.left + rect1.width, rect1.top + rect1.height };
	const sf::Vector2f rect2bottomRight{ rect2.left + rect2.width, rect2.top + rect2.height };

	return doClosedPolylinesIntersect(
		{
			transform1.transformPoint({ rect1.left, rect1.top }),
			transform1.transformPoint({ rect1bottomRight.x, rect1.top }),
			transform1.transformPoint(rect1bottomRight),
			transform1.transformPoint({ rect1.left, rect1bottomRight.y })
		},
		{
			transform2.transformPoint({ rect2.left, rect2.top }),
			transform2.transformPoint({ rect2bottomRight.x, rect2.top }),
			transform2.transformPoint(rect2bottomRight),
			transform2.transformPoint({ rect2.left, rect2bottomRight.y })
		});
}

inline sf::FloatRect boundingBox(const std::vector<sf::Vector2f>& vertices)
{
	sf::FloatRect box{};
	if (vertices.size() == 0_uz)
		return box;
	
	box.left = vertices[0_uz].x;
	box.top = vertices[0_uz].y;
	
	// store bottom right corner otherwise moving the top or left of the box would require also adjusting the width and height to compensate
	sf::Vector2f bottomRight{ vertices[0_uz] };
	
	for (auto& vertex : vertices)
	{
		if (vertex.x < box.left)
			box.left = vertex.x;
		else if (vertex.x > bottomRight.x)
			bottomRight.x = vertex.x;
		if (vertex.y < box.top)
			box.top = vertex.y;
		else if (vertex.y > bottomRight.y)
			bottomRight.y = vertex.y;
	}
	box.width = bottomRight.x - box.left;
	box.height = bottomRight.y - box.top;

	return box;
}

inline void changeAlpha(sf::Color& color, const unsigned char alpha)
{
	color.a = colorComponentRange.clamp(alpha);
}

inline void changeAlpha(sf::Color& color, const float alpha)
{
	changeAlpha(color, Tween::linear(0_uc, 255_uc, alpha));
}

inline void changeAlpha(sf::Color& color, const double alpha)
{
	changeAlpha(color, Tween::linear(0_uc, 255_uc, alpha));
}

inline sf::Color colorFromColorAndAlpha(sf::Color color, const unsigned char alpha)
{
	color.a = colorComponentRange.clamp(alpha);
	return color;
}

inline sf::Color colorFromColorAndAlpha(sf::Color color, const float alpha)
{
	return colorFromColorAndAlpha(color, Tween::linear(0_uc, 255_uc, alpha));
}

inline sf::Color colorFromColorAndAlpha(sf::Color color, const double alpha)
{
	return colorFromColorAndAlpha(color, Tween::linear(0_uc, 255_uc, alpha));
}

inline sf::Vector2f roundVector(const sf::Vector2f& vector)
{
	return{ std::round(vector.x), std::round(vector.y) };
}

inline sf::Vector3f roundVector(const sf::Vector3f& vector)
{
	return{ std::round(vector.x), std::round(vector.y), std::round(vector.z) };
}

inline sf::Vector2f floorVector(const sf::Vector2f& vector)
{
	return{ std::floor(vector.x), std::floor(vector.y) };
}

inline sf::Vector3f floorVector(const sf::Vector3f& vector)
{
	return{ std::floor(vector.x), std::floor(vector.y), std::floor(vector.z) };
}

inline sf::Vector2f ceilVector(const sf::Vector2f& vector)
{
	return{ std::ceil(vector.x), std::ceil(vector.y) };
}

inline sf::Vector3f ceilVector(const sf::Vector3f& vector)
{
	return{ std::ceil(vector.x), std::ceil(vector.y), std::ceil(vector.z) };
}

inline sf::Vector2f absVector(const sf::Vector2f& vector)
{
	return{ abs(vector.x), abs(vector.y) };
}

inline sf::Vector3f absVector(const sf::Vector3f& vector)
{
	return{ abs(vector.x), abs(vector.y), abs(vector.z) };
}

	} // namespace Sfml
} // namespace plinth
