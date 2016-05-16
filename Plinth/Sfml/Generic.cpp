//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2016 M.J.Silk
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

#include "Generic.hpp"
#include "../Range.hpp"
#include <math.h>
#include "../Tween.hpp"

namespace
{

const pl::Range<unsigned int> colorComponentRange{ 0u, 255u };

} // namespace

namespace plinth
{
	namespace Sfml
	{


// SFML from Plinth

sf::Vector2f vector2(const Vector2d& vector)
{
	return{ static_cast<float>(vector.x), static_cast<float>(vector.y) };
}

sf::Vector2i vector2(const Vector2i& vector)
{
	return{ vector.x, vector.y };
}

sf::Vector2u vector2(const Vector2u& vector)
{
	return{ vector.x, vector.y };
}

sf::Vector3f vector3(const Vector3d& vector)
{
	return{ static_cast<float>(vector.x), static_cast<float>(vector.y), static_cast<float>(vector.z) };
}

sf::Vector3i vector3(const Vector3i& vector)
{
	return{ vector.x, vector.y, vector.z };
}

sf::Vector3i vector3(const Vector3u& vector)
{
	return{ static_cast<int>(vector.x), static_cast<int>(vector.y), static_cast<int>(vector.z) };
}


// Plinth from SFML

Vector2d vector2(const sf::Vector2f& vector)
{
	return{ vector.x, vector.y };
}

Vector2i vector2(const sf::Vector2i& vector)
{
	return{ vector.x, vector.y };
}

Vector2u vector2(const sf::Vector2u& vector)
{
	return{ vector.x, vector.y };
}

Vector3d vector3(const sf::Vector3f& vector)
{
	return{ vector.x, vector.y, vector.z };
}

Vector3i vector3(const sf::Vector3i& vector)
{
	return{ vector.x, vector.y, vector.z };
}














sf::Color colorFromValue(long int value)
{
	return colorFromRgb(Color::Rgb(value));
}

sf::Color colorFromRgb(const Color::Rgb& rgb)
{
	return sf::Color(Tween::linear(0, 255, rgb.r), Tween::linear(0, 255, rgb.g), Tween::linear(0, 255, rgb.b));
}

Color::Rgb rgbFromColor(const sf::Color& color)
{
	return Color::Rgb{
		Tween::inverseLinear(0u, 255u, static_cast<unsigned int>(color.r)),
		Tween::inverseLinear(0u, 255u, static_cast<unsigned int>(color.g)),
		Tween::inverseLinear(0u, 255u, static_cast<unsigned int>(color.b))};
}

float lengthSquared(const sf::Vector2f& vector)
{
	return vector.x * vector.x + vector.y * vector.y;
}

float length(const sf::Vector2f& vector)
{
	return sqrt(lengthSquared(vector));
}

float lengthSquared(const sf::Vector3f& vector)
{
	return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
}

float length(const sf::Vector3f& vector)
{
	return sqrt(lengthSquared(vector));
}

float dotProduct(const sf::Vector3f& a, const sf::Vector3f& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return a.x * b.x + a.y * b.y;
}

sf::Vector3f crossProduct(const sf::Vector3f& a, const sf::Vector3f& b)
{
	return
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

float crossProductPoints(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return{ a.x * b.y - b.x * a.y };
}

bool CCW(const std::vector<sf::Vector2f>& points)
{
	if (points.size() != 3)
		return false;

	return (points[2].y - points[0].y) * (points[1].x - points[0].x) > (points[1].y - points[0].y) * (points[2].x - points[0].x);
}

// vector of (2) lines. line is a vector of (2) vector2fs (the points of the line).
// i.e. { { line1.x, line.y }, { line2.x, line2.y } }
bool doLinesIntersect(const std::vector<std::vector<sf::Vector2f>>& lines)
{
	if (lines.size() != 2)
		return false;
	if ((lines[0].size() != 2) || (lines[1].size() != 2))
		return false;

	return	(	CCW({ lines[0][0], lines[1][0], lines[1][1] }) !=
				CCW({ lines[0][1], lines[1][0], lines[1][1] })) &&
			(	CCW({ lines[0][0], lines[0][1], lines[1][0] }) !=
				CCW({ lines[0][0], lines[0][1], lines[1][1] }));
}

bool isPointInsidePolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygonVertices)
{
	return isPointInsidePolygon(point, polygonVertices, boundingBox(polygonVertices));
}

bool isPointInsidePolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygonVertices, const sf::FloatRect& boundingBox)
{
	if (!boundingBox.contains(point))
		return false;

	bool isInside{ false };
	sf::Vector2f pointOutsideBoundingBox{ boundingBox.left - 1, boundingBox.top - 1 };
	for (unsigned int v{ 0 }, w{ polygonVertices.size() - 1 }; v < polygonVertices.size(); w = v++)
	{
		if (doLinesIntersect({ { polygonVertices[v], polygonVertices[w] }, { pointOutsideBoundingBox, point } }))
			isInside = !isInside;
	}
	return isInside;
}

bool doClosedPolylinesIntersect(const std::vector<sf::Vector2f>& a, const std::vector<sf::Vector2f>& b)
{
	for (unsigned int l{ 0 }, m{ a.size() - 1 }; l < a.size(); m = l++)
	{
		for (unsigned int v{ 0 }, w{ b.size() - 1 }; v < b.size(); w = v++)
		{
			if (doLinesIntersect({ { a[l], a[m] }, { b[v], b[w] } }))
				return true;
		}
	}
	return false;
}

sf::FloatRect boundingBox(const std::vector<sf::Vector2f>& vertices)
{
	sf::FloatRect box;
	if (vertices.size() == 0)
		return box;
	
	box.left = vertices[0].x;
	box.top = vertices[0].y;
	
	// store bottom right corner otherwise moving the top or left of the box would require also adjusting the width and height to compensate
	sf::Vector2f bottomRight{ vertices[0] };
	
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

void changeAlpha(sf::Color& color, unsigned int alpha)
{
	color.a = colorComponentRange.clamp(alpha);
}

void changeAlpha(sf::Color& color, float alpha)
{
	changeAlpha(color, Tween::linear(0u, 255u, alpha));
}

void changeAlpha(sf::Color& color, double alpha)
{
	changeAlpha(color, Tween::linear(0u, 255u, alpha));
}

sf::Color colorFromColorAndAlpha(sf::Color color, unsigned int alpha)
{
	color.a = colorComponentRange.clamp(alpha);
	return color;
}

sf::Color colorFromColorAndAlpha(sf::Color color, float alpha)
{
	return colorFromColorAndAlpha(color, Tween::linear(0u, 255u, alpha));
}

sf::Color colorFromColorAndAlpha(sf::Color color, double alpha)
{
	return colorFromColorAndAlpha(color, Tween::linear(0u, 255u, alpha));
}

sf::Vector2f roundVector(const sf::Vector2f& vector)
{
	return{ round(vector.x), round(vector.y) };
}

sf::Vector3f roundVector(const sf::Vector3f& vector)
{
	return{ round(vector.x), round(vector.y), round(vector.z) };
}

sf::Vector2f floorVector(const sf::Vector2f& vector)
{
	return{ floor(vector.x), floor(vector.y) };
}

sf::Vector3f floorVector(const sf::Vector3f& vector)
{
	return{ floor(vector.x), floor(vector.y), floor(vector.z) };
}

sf::Vector2f ceilVector(const sf::Vector2f& vector)
{
	return{ ceil(vector.x), ceil(vector.y) };
}

sf::Vector3f ceilVector(const sf::Vector3f& vector)
{
	return{ ceil(vector.x), ceil(vector.y), ceil(vector.z) };
}

sf::Vector2f absVector(const sf::Vector2f& vector)
{
	return{ abs(vector.x), abs(vector.y) };
}

sf::Vector3f absVector(const sf::Vector3f& vector)
{
	return{ abs(vector.x), abs(vector.y), abs(vector.z) };
}

	} // namespace Sfml
} // namespace plinth
