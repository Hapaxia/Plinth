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

#ifndef PLINTH_SFML_GENERIC_HPP
#define PLINTH_SFML_GENERIC_HPP

#include "Common.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../Generic.hpp"
#include "../Vectors.hpp"
#include "../Color.hpp"

namespace plinth
{
	namespace Sfml
	{

// SFML vector from Plinth vector (to allow direct conversion)
sf::Vector2f vector2(const Vector2d& vector);
sf::Vector2i vector2(const Vector2i& vector);
sf::Vector2u vector2(const Vector2u& vector);
sf::Vector3f vector3(const Vector3d& vector);
sf::Vector3i vector3(const Vector3i& vector);
sf::Vector3i vector3(const Vector3u& vector);

// Plinth vector from SFML vector (to allow direct conversion)
Vector2d vector2(const sf::Vector2f& vector);
Vector2i vector2(const sf::Vector2i& vector);
Vector2u vector2(const sf::Vector2u& vector);
Vector3d vector3(const sf::Vector3f& vector);
Vector3i vector3(const sf::Vector3i& vector);

sf::Color colorFromValue(long int value);
sf::Color colorFromRgb(const Color::Rgb& rgb);
Color::Rgb rgbFromColor(const sf::Color& color);

float lengthSquared(const sf::Vector2f& vector);
float length(const sf::Vector2f& vector);
float lengthSquared(const sf::Vector3f& vector);
float length(const sf::Vector3f& vector);
float dotProduct(const sf::Vector3f& a, const sf::Vector3f& b);
float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b);
sf::Vector3f crossProduct(const sf::Vector3f& a, const sf::Vector3f& b);
float crossProductPoints(const sf::Vector2f& a, const sf::Vector2f& b);

bool CCW(const std::vector<sf::Vector2f>& points); // "counter clock-wise" based on vertical axis not being flipped (SFML's is flipped) - used internally by doLinesIntersect
bool doLinesIntersect(const std::vector<std::vector<sf::Vector2f>>& lines);
bool isPointInsidePolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygonVertices); // creates its own bounding box
bool isPointInsidePolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygonVertices, const sf::FloatRect& boundingBox);
bool doClosedPolylinesIntersect(const std::vector<sf::Vector2f>& a, const std::vector<sf::Vector2f>& b);

// returns a sf::FloatRect that is the bounding box of all of the provided vertices (vector of sf::Vector2f)
sf::FloatRect boundingBox(const std::vector<sf::Vector2f>& vertices);

void changeAlpha(sf::Color& color, unsigned int alpha);
void changeAlpha(sf::Color& color, float alpha);
void changeAlpha(sf::Color& color, double alpha);
sf::Color colorFromColorAndAlpha(sf::Color color, unsigned int alpha);
sf::Color colorFromColorAndAlpha(sf::Color color, float alpha);
sf::Color colorFromColorAndAlpha(sf::Color color, double alpha);

sf::Vector2f roundVector(const sf::Vector2f& vector);
sf::Vector3f roundVector(const sf::Vector3f& vector);
sf::Vector2f floorVector(const sf::Vector2f& vector);
sf::Vector3f floorVector(const sf::Vector3f& vector);
sf::Vector2f ceilVector(const sf::Vector2f& vector);
sf::Vector3f ceilVector(const sf::Vector3f& vector);
sf::Vector2f absVector(const sf::Vector2f& vector);
sf::Vector3f absVector(const sf::Vector3f& vector);

	} // namespace Sfml
} // namespace plinth

#endif // PLINTH_SFML_GENERIC_HPP
