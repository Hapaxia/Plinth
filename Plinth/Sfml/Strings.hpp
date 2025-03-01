//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2025 M.J.Silk
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

#include "Common.hpp"
#include "../Strings.hpp"
#include "Colors.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/View.hpp>
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

enum class SfmlTimeFormat
{
	Seconds,
	Milliseconds,
	Microseconds,
};

template<class T>
std::string stringFrom(sf::Vector2<T>, DecimalPrecision decimalPrecision = DecimalPrecision::None);
std::string stringFrom(sf::Vector2<std::string>);

template<class T>
std::string stringFrom(sf::Vector3<T>, DecimalPrecision decimalPrecision = DecimalPrecision::None);
std::string stringFrom(sf::Vector3<std::string>);

std::string stringFrom(sf::Color, SfmlColorList colorList = SfmlColorList::Extended, bool separateAlpha = true);

std::string stringFrom(sf::VideoMode, bool sizeOnly = false);

std::string stringFrom(sf::View, DecimalPrecision decimalPrecision, bool withoutViewport = false);
std::string stringFrom(sf::View, bool withoutViewport = false);

std::string stringFrom(sf::Keyboard::Key);

std::string stringFrom(sf::Time, DecimalPrecision decimalPrecision, SfmlTimeFormat format = SfmlTimeFormat::Seconds, bool shortUnit = false);
std::string stringFrom(sf::Time, SfmlTimeFormat format = SfmlTimeFormat::Seconds, bool shortUnit = false);

} // namespace plinth
#include "Strings.inl"
