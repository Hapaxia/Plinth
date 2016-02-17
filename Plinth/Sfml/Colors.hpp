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

#ifndef PLINTH_SFML_COLORS_HPP
#define PLINTH_SFML_COLORS_HPP

#include "Common.hpp"
#include <SFML/Graphics/Color.hpp>

namespace plinth
{
	namespace Colors
	{

const sf::Color Transparent(0, 0, 0, 0);

// standard
const sf::Color Black(0, 0, 0);
const sf::Color Blue(0, 0, 255);
const sf::Color Red(255, 0, 0);
const sf::Color Magenta(255, 0, 255);
const sf::Color Green(0, 255, 0);
const sf::Color Cyan(0, 255, 255);
const sf::Color Yellow(255, 255, 0);
const sf::Color White(255, 255, 255);
const sf::Color Brown(128, 80, 32);
const sf::Color Orange(255, 128, 0);
const sf::Color Pink(255, 128, 192);
const sf::Color BabyPink(255, 192, 224);
const sf::Color HotPink(255, 0, 192);
const sf::Color Salmon(255, 128, 128);
const sf::Color Violet(128, 0, 255);
const sf::Color Purple(64, 0, 128);
const sf::Color Peach(255, 128, 96);
const sf::Color Lime(128, 255, 0);
const sf::Color Mint(64, 255, 192);
const sf::Color Gray(128, 128, 128);
const sf::Color MediumGray = Gray;
const sf::Color MidGray = Gray;

// lights
const sf::Color LightBlack(64, 64, 64);
const sf::Color LightBlue(128, 128, 255);
const sf::Color LightRed(255, 128, 128);
const sf::Color LightMagenta(255, 128, 255);
const sf::Color LightGreen(128, 255, 128);
const sf::Color LightCyan(128, 255, 255);
const sf::Color LightYellow(255, 255, 128);
const sf::Color LightBrown(192, 128, 64);
const sf::Color LightOrange(255, 160, 64);
const sf::Color LightPink(255, 160, 224);
const sf::Color LightBabyPink(255, 208, 232);
const sf::Color LightHotPink(255, 96, 224);
const sf::Color LightSalmon(255, 160, 160);
const sf::Color LightViolet(160, 96, 255);
const sf::Color LightPurple(128, 64, 192);
const sf::Color LightPeach(255, 160, 128);
const sf::Color LightLime(192, 255, 128);
const sf::Color LightMint(128, 255, 224);
const sf::Color LightGray(192, 192, 192);

// darks
const sf::Color DarkBlue(0, 0, 128);
const sf::Color DarkRed(128, 0, 0);
const sf::Color DarkMagenta(128, 0, 128);
const sf::Color DarkGreen(0, 128, 0);
const sf::Color DarkCyan(0, 128, 128);
const sf::Color DarkYellow(128, 128, 0);
const sf::Color DarkWhite(128, 128, 128);
const sf::Color DarkBrown(64, 32, 0);
const sf::Color DarkOrange(128, 64, 0);
const sf::Color DarkPink(128, 64, 96);
const sf::Color DarkBabyPink(160, 96, 128);
const sf::Color DarkHotPink(128, 0, 96);
const sf::Color DarkSalmon(128, 64, 64);
const sf::Color DarkViolet(64, 0, 128);
const sf::Color DarkPurple(32, 0, 64);
const sf::Color DarkPeach(128, 64, 48);
const sf::Color DarkLime(64, 128, 0);
const sf::Color DarkMint(32, 128, 96);
const sf::Color DarkGray(64, 64, 64);

// very darks
const sf::Color VeryDarkBlue(0, 0, 64);
const sf::Color VeryDarkRed(64, 0, 0);
const sf::Color VeryDarkMagenta(64, 0, 64);
const sf::Color VeryDarkGreen(0, 64, 0);
const sf::Color VeryDarkCyan(0, 64, 64);
const sf::Color VeryDarkYellow(64, 64, 0);
const sf::Color VeryDarkWhite(64, 64, 64);
const sf::Color VeryDarkBrown(32, 16, 0);
const sf::Color VeryDarkOrange(64, 32, 0);
const sf::Color VeryDarkPink(64, 32, 48);
const sf::Color VeryDarkBabyPink(80, 48, 64);
const sf::Color VeryDarkHotPink(64, 0, 48);
const sf::Color VeryDarkSalmon(64, 32, 32);
const sf::Color VeryDarkViolet(32, 0, 64);
const sf::Color VeryDarkPurple(16, 0, 32);
const sf::Color VeryDarkPeach(64, 32, 24);
const sf::Color VeryDarkLime(32, 64, 0);
const sf::Color VeryDarkMint(16, 64, 48);
const sf::Color VeryDarkGray(32, 32, 32);

	} // namespace Colors
} // namespace plinth
#endif // PLINTH_SFML_COLORS_HPP
