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

namespace plinth
{

template<class T>
std::string stringFrom(const sf::Vector2<T> from)
{
	return "(" + stringFrom(from.x) + ", " + stringFrom(from.y) + ")";
}

template<class T>
std::string stringFrom(const sf::Vector2<T> from, const unsigned int decimalPrecision)
{
	return "(" + stringFrom(from.x, decimalPrecision) + ", " + stringFrom(from.y, decimalPrecision) + ")";
}

template<class T>
std::string stringFrom(const sf::Vector3<T> from)
{
	return "(" + stringFrom(from.x) + ", " + stringFrom(from.y) + ", " + stringFrom(from.z) + ")";
}

template<class T>
std::string stringFrom(const sf::Vector3<T> from, const unsigned int decimalPrecision)
{
	return "(" + stringFrom(from.x, decimalPrecision) + ", " + stringFrom(from.y, decimalPrecision) + ", " + stringFrom(from.z, decimalPrecision) + ")";
}

} // namespace plinth
