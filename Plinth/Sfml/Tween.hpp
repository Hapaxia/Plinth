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

#ifndef PLINTH_SFML_TWEEN_HPP
#define PLINTH_SFML_TWEEN_HPP

namespace sf
{
	class Color;
} // namespace sf

namespace plinth
{
	namespace Tween
	{

// Linear Tween (interpolation) of two SFML colours (sf::Color) using a given "alpha" value of the "blend amount"
// Type alphaT should be a POD type in range 0 to 1.
template <class alphaT>
sf::Color linear(const sf::Color& start, const sf::Color& end, const alphaT& alpha);

	} // namespace Tween
} // namespace Tween
#include "Tween.inl"
#endif // PLINTH_SFML_TWEEN_HPP
