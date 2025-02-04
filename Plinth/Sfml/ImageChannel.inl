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

#include "ImageChannel.hpp"

#include "../RandomDistribution.hpp"

namespace plinth
{
	namespace Image
	{

inline Channel::Channel()
	: m_exceptionPrefix{ "SFML/ImageChannel: " }
	, m_size{ 0u, 0u }
	, m_pixels{}
{
}

inline Channel::Channel(const sf::Vector2u size)
	: Channel()
{
	setSize(size);
}

inline Channel::Channel(const sf::Vector2u size, const unsigned char value)
	: Channel(size)
{
	clear(value);
}

inline Channel::Channel(const sf::Image& image, const ColorChannel colorChannel)
	: Channel(image.getSize())
{
	copyFromImage(image, colorChannel, false); // no need to resize as resizing is done in constructor initialisation
}

inline void Channel::setSize(const sf::Vector2u size)
{
	m_size = size;
	m_pixels.resize(static_cast<std::size_t>(m_size.x) * static_cast<std::size_t>(m_size.y));
}

inline sf::Vector2u Channel::getSize() const
{
	return m_size;
}

inline void Channel::setPixel(const sf::Vector2u location, const unsigned char value)
{
	if (location.x >= m_size.x || location.y >= m_size.y)
		throw Exception(m_exceptionPrefix + "Could not set pixel; specified location - (" + std::to_string(location.x) + ", " + std::to_string(location.y) + ") - out of bounds.");
	m_pixels[static_cast<std::size_t>(location.y) * static_cast<std::size_t>(m_size.x) + static_cast<std::size_t>(location.x)] = value;
}

inline unsigned char Channel::getPixel(const sf::Vector2u location) const
{
	if (location.x >= m_size.x || location.y >= m_size.y)
		throw Exception(m_exceptionPrefix + "Could not get pixel; specified location - (" + std::to_string(location.x) + ", " + std::to_string(location.y) + ") - out of bounds.");
	return m_pixels[static_cast<std::size_t>(location.y) * static_cast<std::size_t>(m_size.x) + static_cast<std::size_t>(location.x)];
}

inline void Channel::copyFromImage(const sf::Image& image, const ColorChannel colorChannel, const bool resize)
{
	const sf::Vector2u imageSize{ image.getSize() };
	if (resize)
		setSize(imageSize);
	for (unsigned int y{ 0u }; y < m_size.y; ++y)
	{
		if (!resize && (y >= imageSize.y))
			continue;

		for (unsigned int x{ 0u }; x < m_size.x; ++x)
		{
			if (!resize && (x >= imageSize.x))
				continue;

			switch (colorChannel)
			{
			case ColorChannel::Red:
				setPixel({ x, y }, image.getPixel({ x, y }).r);
				break;
			case ColorChannel::Green:
				setPixel({ x, y }, image.getPixel({ x, y }).g);
				break;
			case ColorChannel::Blue:
				setPixel({ x, y }, image.getPixel({ x, y }).b);
				break;
			case ColorChannel::Alpha:
				setPixel({ x, y }, image.getPixel({ x, y }).a);
				break;
			default:
				const sf::Color color{ image.getPixel({x, y}) };
				setPixel({ x, y }, static_cast<std::uint8_t>((static_cast<unsigned int>(color.r) + color.g + color.b) / 3u));
			}
		}
	}
}

inline void Channel::copyToImage(sf::Image& image, const ColorChannel colorChannel, const bool replaceAlpha) const
{
	const sf::Vector2u imageSize{ image.getSize() };
	for (std::size_t i{ 0_uz }; i < m_pixels.size(); ++i)
	{
		const sf::Vector2u location{ static_cast<unsigned int>(i % imageSize.x), static_cast<unsigned int>(i / imageSize.x) };
		if ((location.x >= imageSize.x) || (location.y >= imageSize.y))
			continue;

		sf::Color color{ image.getPixel(location) };
		if (replaceAlpha)
			color.a = 255_uc;
		switch (colorChannel)
		{
		case ColorChannel::Red:
			color.r = m_pixels[i];
			break;
		case ColorChannel::Green:
			color.g = m_pixels[i];
			break;
		case ColorChannel::Blue:
			color.b = m_pixels[i];
			break;
		case ColorChannel::Alpha:
			color.a = m_pixels[i];
			break;
		default:
			color.r = m_pixels[i];
			color.g = m_pixels[i];
			color.b = m_pixels[i];
		}
		image.setPixel(location, color);
	}
}

inline void Channel::clear(const unsigned char value)
{
	for (auto& pixel : m_pixels)
		pixel = value;
}

inline void Channel::invert()
{
	for (auto& pixel : m_pixels)
		pixel = 255_uc - pixel;
}

inline void Channel::generateNoise(const NoiseType type)
{
	RandomDistribution<unsigned int> random{ 0u, 255u };
	for (auto& pixel : m_pixels)
		pixel = static_cast<unsigned char>(random.value());
}

	} // namespace Image
} // namespace plinth
