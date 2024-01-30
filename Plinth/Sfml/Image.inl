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

#include "Image.hpp"
#include "Tween.hpp"
#include "../Tween.hpp"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace
{

const std::string exceptionPrefix = "SFML/Image: ";

} // namespace

namespace plinth
{
	namespace Image
	{

using namespace Sfml;

inline void processAllPixelsRgb(sf::Image& image, std::function<void (Color::Rgb&)> process)
{
	// preserves pixel alpha
	const sf::Vector2u imageSize{ image.getSize() };
	for (unsigned int y{ 0u }; y < imageSize.y; ++y)
	{
		for (unsigned int x{ 0u }; x < imageSize.x; ++x)
		{
			sf::Color color{ image.getPixel(x, y) };
			Color::Rgb pixel{ rgbFromColor(color) };
			process(pixel);
			color = colorFromColorAndAlpha(colorFromRgb(pixel), Tween::inverseLinear(0u, 255u, static_cast<unsigned int>(color.a)));
			image.setPixel(x, y, color);
		}
	}
}

inline void processAllPixelsColor(sf::Image& image, std::function<void (sf::Color&)> process)
{
	const sf::Vector2u imageSize{ image.getSize() };
	for (unsigned int y{ 0u }; y < imageSize.y; ++y)
	{
		for (unsigned int x{ 0u }; x < imageSize.x; ++x)
		{
			sf::Color pixel{ image.getPixel(x, y) };
			process(pixel);
			image.setPixel(x, y, pixel);
		}
	}
}

inline void convertToGrayscale(sf::Image& image, const GrayscaleConversionType conversionType)
{
	switch (conversionType)
	{
	case GrayscaleConversionType::RedChannel:
		processAllPixelsRgb(image, [](Color::Rgb& pixel)
		{
			pixel.g = pixel.b = pixel.r;
		});
		break;
	case GrayscaleConversionType::GreenChannel:
		processAllPixelsRgb(image, [](Color::Rgb& pixel)
		{
			pixel.b = pixel.r = pixel.g;
		});
		break;
	case GrayscaleConversionType::BlueChannel:
		processAllPixelsRgb(image, [](Color::Rgb& pixel)
		{
			pixel.r = pixel.g = pixel.b;
		});
		break;
	case GrayscaleConversionType::Luminosity:
		processAllPixelsRgb(image, [](Color::Rgb& pixel)
		{
			pixel.r = pixel.g = pixel.b = pixel.getRelativeLuminance();
		});
		break;
	case GrayscaleConversionType::Lightness:
		processAllPixelsRgb(image, [](Color::Rgb& pixel)
		{
			// mean of the highest and lowest component value. the median value is ignored
			pixel.r = pixel.g = pixel.b = (max(pixel.r, max(pixel.g, pixel.b)) + min(pixel.r, min(pixel.g, pixel.b))) / 2.0;
		});
		break;
	case GrayscaleConversionType::Median:
		processAllPixelsRgb(image, [](Color::Rgb& pixel)
		{
			// only the median component value is used. the highest and lowest values are ignored.
			double value{};
			if (pixel.r > pixel.g && pixel.r > pixel.b)
				value = max(pixel.g, pixel.b);
			else if (pixel.r < pixel.g && pixel.r < pixel.b)
				value = min(pixel.g, pixel.b);
			else
				value = pixel.r;
			pixel.r = pixel.g = pixel.b = value;
		});
		break;
	case GrayscaleConversionType::Average:
		processAllPixelsRgb(image, [](Color::Rgb& pixel)
		{
			// mean of all three components
			pixel.r = pixel.g = pixel.b = (pixel.r + pixel.g + pixel.b) / 3.0;
		});
		break;
	default:
		processAllPixelsRgb(image, [](Color::Rgb& pixel){}); // make no changes
	}
}

inline void createMaskFromAlpha(sf::Image& image)
{
	processAllPixelsColor(image, [](sf::Color& pixel)
	{
		pixel.r = pixel.a;
		pixel.g = pixel.a;
		pixel.b = pixel.a;
		pixel.a = 255_uc;
	});
}

inline void invert(sf::Image& image)
{
	processAllPixelsRgb(image, [](Color::Rgb& pixel)
	{
		pixel.r = 1.0 - pixel.r;
		pixel.g = 1.0 - pixel.g;
		pixel.b = 1.0 - pixel.b;
	});
}

inline void setAlpha(sf::Image& image, const unsigned char alpha)
{
	processAllPixelsColor(image, [&alpha](sf::Color& pixel)
	{
		pixel.a = alpha;
	});
}

inline void invertAlpha(sf::Image& image)
{
	processAllPixelsColor(image, [](sf::Color& pixel)
	{
		pixel.a = 255_uc - pixel.a;
	});
}

inline void makeOpaque(sf::Image& image)
{
	processAllPixelsColor(image, [](sf::Color& pixel)
	{
		pixel.a = 255_uc;
	});
}

inline void clearWithColorButRetainTransparency(sf::Image& image, const sf::Color color)
{
	processAllPixelsColor(image, [&color](sf::Color& pixel)
	{
		pixel.r = color.r;
		pixel.g = color.g;
		pixel.b = color.b;
		// or: color.a = pixel.a; pixel = color;
	});
}

inline void setRedFromChannel(sf::Image& image, const Channel& channel)
{
	if (image.getSize() != channel.getSize())
		throw Exception(exceptionPrefix + "Cannot set image red from channel. Sizes do not match.");
	channel.copyToImage(image, ColorChannel::Red);
}

inline void setGreenFromChannel(sf::Image& image, const Channel& channel)
{
	if (image.getSize() != channel.getSize())
		throw Exception(exceptionPrefix + "Cannot set image green from channel. Sizes do not match.");
	channel.copyToImage(image, ColorChannel::Green);
}

inline void setBlueFromChannel(sf::Image& image, const Channel& channel)
{
	if (image.getSize() != channel.getSize())
		throw Exception(exceptionPrefix + "Cannot set image blue from channel. Sizes do not match.");
	channel.copyToImage(image, ColorChannel::Blue);
}

inline void setRgbFromChannel(sf::Image& image, const Channel& channel)
{
	if (image.getSize() != channel.getSize())
		throw Exception(exceptionPrefix + "Cannot set image rgb from channel. Sizes do not match.");
	channel.copyToImage(image, ColorChannel::Rgb);
}

inline void setAlphaFromChannel(sf::Image& image, const Channel& channel)
{
	if (image.getSize() != channel.getSize())
		throw Exception(exceptionPrefix + "Cannot set image alpha from channel. Sizes do not match.");
	channel.copyToImage(image, ColorChannel::Alpha);
}

inline void setAlphaFromMask(sf::Image& image, const Channel& mask)
{
	if (image.getSize() != mask.getSize())
		throw Exception(exceptionPrefix + "Cannot set image alpha from mask. Sizes do not match.");
	mask.copyToImage(image, ColorChannel::Alpha);
}



		namespace impl
		{

sf::Image resize_Draw(const sf::Image& image, const sf::Vector2u destinationSize, const bool smooth = false, const bool aa = false, const sf::IntRect sourceRectangle = {})
{
	sf::RenderTexture renderTexture{};
	sf::ContextSettings contextSettings{};
	if (aa)
		contextSettings.antialiasingLevel = 16u;
	{
		pl::Sfml::ErrBlocker sfmlErrBlocker{}; // avoid error output if requested anti-alias level is not available
		renderTexture.create(destinationSize.x, destinationSize.y, contextSettings);
	}
	sf::RectangleShape rectangle{};
	rectangle.setSize(sf::Vector2f(destinationSize));
	sf::Texture texture{};
	texture.loadFromImage(image, sourceRectangle);
	if (smooth)
		texture.setSmooth(true);
	rectangle.setTexture(&texture);
	renderTexture.draw(rectangle);
	renderTexture.display();
	return renderTexture.getTexture().copyToImage();
}

sf::Image resize_Pixel(const sf::Image& image, const sf::Vector2u destinationSize, const sf::IntRect sourceRectangle)
{
	const sf::Vector2u sourcePosition(sourceRectangle.getPosition());
	const sf::Vector2u sourceSize(sourceRectangle.getSize());
	sf::Image result;
	result.create(destinationSize.x, destinationSize.y);
	for (unsigned int y{ 0u }; y < destinationSize.y; ++y)
	{
		const unsigned int sourceY{ sourcePosition.y + (y * (sourceSize.y) / (destinationSize.y)) };
		for (unsigned int x{ 0u }; x < destinationSize.x; ++x)
		{
			const unsigned int sourceX{ sourcePosition.x + (x * (sourceSize.x) / (destinationSize.x)) };
			result.setPixel(x, y, image.getPixel(sourceX, sourceY));
		}
	}
	return result;
}

sf::Image resize_NearestNeighbour(const sf::Image& image, const sf::Vector2u destinationSize, const sf::IntRect sourceRectangle)
{
	const sf::Vector2u sourcePosition(sourceRectangle.getPosition());
	const sf::Vector2u sourceSize(sourceRectangle.getSize());

	const pl::Range<long long int>xRange{ 0ll, static_cast<long long int>(sourceSize.x) - 1ll };
	const pl::Range<long long int>yRange{ 0ll, static_cast<long long int>(sourceSize.y) - 1ll };

	sf::Image result;
	result.create(destinationSize.x, destinationSize.y);
	for (unsigned int y{ 0u }; y < destinationSize.y; ++y)
	{
		const long double targetY{ sourcePosition.y + (((y + 0.5) * sourceSize.y) / (destinationSize.y)) - 0.5 };
		const unsigned int sourceY{ static_cast<unsigned int>(yRange.clamp(std::llround(targetY))) };
		for (unsigned int x{ 0u }; x < destinationSize.x; ++x)
		{
			const long double targetX{ sourcePosition.x + (((x + 0.5) * sourceSize.x) / (destinationSize.x)) - 0.5 };
			const unsigned int sourceX{ static_cast<unsigned int>(xRange.clamp(std::llround(targetX))) };
			result.setPixel(x, y, image.getPixel(sourceX, sourceY));
		}
	}
	return result;
}

sf::Image resize_Bilinear(const sf::Image& image, const sf::Vector2u destinationSize, const sf::IntRect sourceRectangle)
{
	const sf::Vector2u sourcePosition(sourceRectangle.getPosition());
	const sf::Vector2u sourceSize(sourceRectangle.getSize());

	const pl::Range<long long int>xRange{ 0ll, static_cast<long long int>(sourceSize.x) - 1ll };
	const pl::Range<long long int>yRange{ 0ll, static_cast<long long int>(sourceSize.y) - 1ll };

	sf::Image result;
	result.create(destinationSize.x, destinationSize.y);
	for (unsigned int y{ 0u }; y < destinationSize.y; ++y)
	{
		const long double targetY{ sourcePosition.y + (((y + 0.5) * sourceSize.y) / (destinationSize.y)) - 0.5 };
		const unsigned int minY{ static_cast<unsigned int>(yRange.clamp(std::llround(std::floor(targetY)))) };
		const unsigned int maxY{ static_cast<unsigned int>(yRange.clamp(std::llround(std::ceil(targetY)))) };
		const long double yAlpha{ targetY - minY };

		for (unsigned int x{ 0u }; x < destinationSize.x; ++x)
		{
			const long double targetX{ sourcePosition.x + (((x + 0.5) * sourceSize.x) / (destinationSize.x)) - 0.5 };
			const unsigned int minX{ static_cast<unsigned int>(xRange.clamp(std::llround(std::floor(targetX)))) };
			const unsigned int maxX{ static_cast<unsigned int>(xRange.clamp(std::llround(std::ceil(targetX)))) };
			const long double xAlpha{ targetX - minX };

			const sf::Color upper{ Tween::linear(image.getPixel(minX, minY), image.getPixel(maxX, minY), xAlpha) };
			const sf::Color lower{ Tween::linear(image.getPixel(minX, maxY), image.getPixel(maxX, maxY), xAlpha) };

			result.setPixel(x, y, Tween::linear(upper, lower, yAlpha));
		}
	}
	return result;
}

		} // namespace impl



sf::Image resize(const ResizeType type, const sf::Image& image, const sf::Vector2u destinationSize, sf::IntRect sourceRectangle)
{
	const sf::Vector2u imageSize{ image.getSize() };
	if (destinationSize == imageSize)
		return image;

	if ((destinationSize.x == 0u) || (destinationSize.y == 0u) || (imageSize.x == 0u) || (imageSize.y == 0u))
		return sf::Image{};

	if (sourceRectangle.width == 0u)
	{
		sourceRectangle.left = 0u;
		sourceRectangle.width = image.getSize().x;
	}
	if (sourceRectangle.height == 0u)
	{
		sourceRectangle.top = 0u;
		sourceRectangle.height = image.getSize().y;
	}
	switch (type)
	{
	case ResizeType::Draw:
		return impl::resize_Draw(image, destinationSize, false, false, sourceRectangle);
		break;
	case ResizeType::Draw_Smooth:
		return impl::resize_Draw(image, destinationSize, true, false, sourceRectangle);
		break;
	case ResizeType::Draw_AA:
		return impl::resize_Draw(image, destinationSize, false, true, sourceRectangle);
		break;
	case ResizeType::Draw_SmoothAA:
		return impl::resize_Draw(image, destinationSize, true, true, sourceRectangle);
		break;
	case ResizeType::Pixel:
		return impl::resize_Pixel(image, destinationSize, sourceRectangle);
		break;
	case ResizeType::NearestNeighbour:
		return impl::resize_NearestNeighbour(image, destinationSize, sourceRectangle);
		break;
	case ResizeType::Bilinear:
		return impl::resize_Bilinear(image, destinationSize, sourceRectangle);
		break;
	}
	return image;
}

	} // namspace Image
} // namespace plinth
