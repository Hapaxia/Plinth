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

// REQUIRES C++11

#ifndef PLINTH_SFML_IMAGE_HPP
#define PLINTH_SFML_IMAGE_HPP

#include "Common.hpp"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include "../Generic.hpp"
#include "../Color.hpp"
#include "Generic.hpp"
#include "ImageChannel.hpp"
#include <functional>
#include <string>

namespace plinth
{
	namespace Image
	{

enum class GrayscaleConversionType
{
	Average,
	Lightness,
	Luminosity,
	Median,
	RedChannel,
	GreenChannel,
	BlueChannel
};

void processAllPixelsRgb(sf::Image& image, std::function<void (Color::Rgb&)> process);
void processAllPixelsColor(sf::Image& image, std::function<void (sf::Color&)> process);

void convertToGrayscale(sf::Image& image, GrayscaleConversionType conversionType = GrayscaleConversionType::Luminosity);
void invert(sf::Image& image);
void createMaskFromAlpha(sf::Image& image);
void clearWithColorButRetainTransparency(sf::Image& image, sf::Color color = sf::Color(255, 255, 255, 255));

void setAlpha(sf::Image& image, unsigned char alpha = 255u);
void invertAlpha(sf::Image& image);
void makeOpaque(sf::Image& image);

void setRedFromChannel(sf::Image& image, const Channel& channel);
void setGreenFromChannel(sf::Image& image, const Channel& channel);
void setBlueFromChannel(sf::Image& image, const Channel& channel);
void setRgbFromChannel(sf::Image& image, const Channel& channel);
void setAlphaFromChannel(sf::Image& image, const Channel& channel);
void setAlphaFromMask(sf::Image& image, const Channel& mask);

	} // namspace Image
} // namespace plinth
#endif // PLINTH_SFML_IMAGE_HPP
