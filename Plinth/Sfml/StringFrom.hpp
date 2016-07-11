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

#ifndef PLINTH_SFML_STRINGFROM_HPP
#define PLINTH_SFML_STRINGFROM_HPP

#include "Common.hpp"
#include "../StringFrom.hpp"
#include "Colors.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>

namespace plinth
{

enum class SfmlColorList
{
	None,
	Standard,
	Extended
};

template<class T>
std::string stringFrom(sf::Vector2<T>);
template<class T>
std::string stringFrom(sf::Vector2<T>, unsigned int decimalPrecision);
std::string stringFrom(sf::Vector2<std::string>);

template<class T>
std::string stringFrom(sf::Vector3<T>);
template<class T>
std::string stringFrom(sf::Vector3<T>, unsigned int decimalPrecision);
std::string stringFrom(sf::Vector3<std::string>);

std::string stringFrom(sf::Color, SfmlColorList colorList = SfmlColorList::Extended, bool separateAlpha = true);

std::string stringFrom(sf::VideoMode, bool sizeOnly = false);

std::string stringFrom(sf::Keyboard::Key);

std::string stringFrom(sf::Time);
std::string stringFrom(sf::Time, unsigned int decimalPrecision);

} // namespace plinth
#include "StringFrom.inl"
#endif // PLINTH_SFML_STRINGFROM_HPP
