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

#ifndef PLINTH_SFML_IMAGECHANNEL_HPP
#define PLINTH_SFML_IMAGECHANNEL_HPP

#include "Common.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Color.hpp>
#include "../Random.hpp"

namespace plinth
{
	namespace Image
	{

enum class ColorChannel
{
	Red,
	Green,
	Blue,
	Alpha,
	Rgb
};

enum class NoiseType
{
	Random
};

class Channel
{
public:
	Channel();
	Channel(sf::Vector2u size);
	Channel(sf::Vector2u size, unsigned char value);
	Channel(const sf::Image& image, ColorChannel colorChannel = ColorChannel::Rgb);
	void setSize(sf::Vector2u size);
	sf::Vector2u getSize() const;
	void setPixel(sf::Vector2u location, unsigned char value);
	unsigned char getPixel(sf::Vector2u location) const;
	void copyFromImage(const sf::Image& image, ColorChannel colorChannel = ColorChannel::Rgb, bool resize = true);
	void copyToImage(sf::Image& image, ColorChannel colorChannel = ColorChannel::Rgb) const;
	void clear(unsigned char value = 0u);
	void invert();
	void generateNoise(NoiseType type = NoiseType::Random);

private:
	const std::string m_exceptionPrefix;
	sf::Vector2u m_size;
	std::vector<unsigned char> m_pixels;
};

	} // namespace Image
} // namespace plinth

#endif // PLINTH_SFML_IMAGECHANNEL_HPP
