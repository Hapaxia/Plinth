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

#include "Common.hpp"
#include <SFML/Graphics/Color.hpp>

namespace plinth
{
	namespace Colors
	{

const sf::Color Transparent{ 0u, 0u, 0u, 0u };

// standard
const sf::Color Black{ 0u, 0u, 0u };
const sf::Color Blue{ 0u, 0u, 255u };
const sf::Color Red{ 255u, 0u, 0u };
const sf::Color Magenta{255u, 0u, 255u };
const sf::Color Green{ 0u, 255u, 0u };
const sf::Color Cyan{ 0u, 255u, 255u };
const sf::Color Yellow{ 255u, 255u, 0u };
const sf::Color White{ 255u, 255u, 255u };
const sf::Color Brown{ 128u, 80u, 32u };
const sf::Color Orange{ 255u, 128u, 0u };
const sf::Color Pink{ 255u, 128u, 192u };
const sf::Color BabyPink{ 255u, 192u, 224u };
const sf::Color HotPink{ 255u, 0u, 192u };
const sf::Color Salmon{ 255u, 128u, 128u };
const sf::Color Violet{ 128u, 0u, 255u };
const sf::Color Purple{ 64u, 0u, 128u };
const sf::Color Peach{ 255u, 128u, 96u };
const sf::Color Lime{ 128u, 255u, 0u };
const sf::Color Mint{ 64u, 255u, 192u };
const sf::Color Gray{ 128u, 128u, 128u };
const sf::Color MediumGray = Gray;
const sf::Color MidGray = Gray;

// lights
const sf::Color LightBlack{ 64u, 64u, 64u };
const sf::Color LightBlue{ 128u, 128u, 255u };
const sf::Color LightRed{ 255u, 128u, 128u };
const sf::Color LightMagenta{ 255u, 128u, 255u };
const sf::Color LightGreen{ 128u, 255u, 128u };
const sf::Color LightCyan{ 128u, 255u, 255u };
const sf::Color LightYellow{ 255u, 255u, 128u };
const sf::Color LightBrown{ 192u, 128u, 64u };
const sf::Color LightOrange{ 255u, 160u, 64u };
const sf::Color LightPink{ 255u, 160u, 224u };
const sf::Color LightBabyPink{ 255u, 208u, 232u };
const sf::Color LightHotPink{ 255u, 96u, 224u };
const sf::Color LightSalmon{ 255u, 160u, 160u };
const sf::Color LightViolet{ 160u, 96u, 255u };
const sf::Color LightPurple{ 128u, 64u, 192u };
const sf::Color LightPeach{ 255u, 160u, 128u };
const sf::Color LightLime{ 192u, 255u, 128u };
const sf::Color LightMint{ 128u, 255u, 22u };
const sf::Color LightGray{ 192u, 192u, 192u };

// darks
const sf::Color DarkBlue{ 0u, 0u, 128u };
const sf::Color DarkRed{ 128u, 0u, 0u };
const sf::Color DarkMagenta{ 128u, 0u, 128u };
const sf::Color DarkGreen{ 0u, 128u, 0u };
const sf::Color DarkCyan{ 0u, 128u, 128u };
const sf::Color DarkYellow{ 128u, 128u, 0u };
const sf::Color DarkWhite{ 128u, 128u, 128u };
const sf::Color DarkBrown{ 64u, 32u, 0u };
const sf::Color DarkOrange{ 128u, 64u, 0u };
const sf::Color DarkPink{ 128u, 64u, 96u };
const sf::Color DarkBabyPink{ 160u, 96u, 128u };
const sf::Color DarkHotPink{ 128u, 0u, 96u };
const sf::Color DarkSalmon{ 128u, 64u, 64u };
const sf::Color DarkViolet{ 64u, 0u, 128u };
const sf::Color DarkPurple{ 32u, 0u, 64u };
const sf::Color DarkPeach{ 128u, 64u, 48u };
const sf::Color DarkLime{ 64u, 128u, 0u };
const sf::Color DarkMint{ 32u, 128u, 96u };
const sf::Color DarkGray{ 64u, 64u, 64u };

// very darks
const sf::Color VeryDarkBlue{ 0u, 0u, 64u };
const sf::Color VeryDarkRed{ 64u, 0u, 0u };
const sf::Color VeryDarkMagenta{ 64u, 0u, 64u };
const sf::Color VeryDarkGreen{ 0u, 64u, 0u };
const sf::Color VeryDarkCyan{ 0u, 64u, 64u };
const sf::Color VeryDarkYellow{ 64u, 64u, 0u };
const sf::Color VeryDarkWhite{ 64u, 64u, 64u };
const sf::Color VeryDarkBrown{ 32u, 16u, 0u };
const sf::Color VeryDarkOrange{ 64u, 32u, 0u };
const sf::Color VeryDarkPink{ 64u, 32u, 48u };
const sf::Color VeryDarkBabyPink{ 80u, 48u, 64u };
const sf::Color VeryDarkHotPink{ 64u, 0u, 48u };
const sf::Color VeryDarkSalmon{ 64u, 32u, 32u };
const sf::Color VeryDarkViolet{ 32u, 0u, 64u };
const sf::Color VeryDarkPurple{ 16u, 0u, 32u };
const sf::Color VeryDarkPeach{ 64u, 32u, 24u };
const sf::Color VeryDarkLime{ 32u, 64u, 0u };
const sf::Color VeryDarkMint{ 16u, 64u, 48u };
const sf::Color VeryDarkGray{ 32u, 32u, 32u };

	} // namespace Colors
} // namespace plinth
