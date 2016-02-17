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

#include "Image.hpp"
#include "../Tween.hpp"

namespace
{

const std::string exceptionPrefix = "SFML/Image: ";

} // namespace

namespace plinth
{
	namespace Image
	{

using namespace Sfml;

void processAllPixelsRgb(sf::Image& image, std::function<void (Color::Rgb&)> process)
{
	// preserves pixel alpha
	const sf::Vector2u imageSize{ image.getSize() };
	for (unsigned int y{ 0 }; y < imageSize.y; ++y)
	{
		for (unsigned int x{ 0 }; x < imageSize.x; ++x)
		{
			sf::Color color{ image.getPixel(x, y) };
			Color::Rgb pixel = rgbFromColor(image.getPixel(x, y));
			process(pixel);
			color = colorFromColorAndAlpha(colorFromRgb(pixel), Tween::inverseLinear(0u, 255u, static_cast<unsigned int>(color.a)));
			image.setPixel(x, y, color);
		}
	}
}

void processAllPixelsColor(sf::Image& image, std::function<void (sf::Color&)> process)
{
	const sf::Vector2u imageSize{ image.getSize() };
	for (unsigned int y{ 0 }; y < imageSize.y; ++y)
	{
		for (unsigned int x{ 0 }; x < imageSize.x; ++x)
		{
			sf::Color pixel{ image.getPixel(x, y) };
			process(pixel);
			image.setPixel(x, y, pixel);
		}
	}
}

void convertToGrayscale(sf::Image& image, const GrayscaleConversionType conversionType)
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
			const double value{ pixel.getRelativeLuminance() };
			pixel.r = pixel.g = pixel.b = value;
		});
		break;
	case GrayscaleConversionType::Lightness:
		processAllPixelsRgb(image, [](Color::Rgb& pixel)
		{
			// mean of the highest and lowest component value. the median value is ignored
			const double value{ (max(pixel.r, max(pixel.g, pixel.b)) + min(pixel.r, min(pixel.g, pixel.b))) / 2.0 };
			pixel.r = pixel.g = pixel.b = value;
		});
		break;
	case GrayscaleConversionType::Median:
		processAllPixelsRgb(image, [](Color::Rgb& pixel)
		{
			// only the median component value is used. the highest and lowest values are ignored.
			double value;
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
			const double value{ (pixel.r + pixel.g + pixel.b) / 3.0 };
			pixel.r = pixel.g = pixel.b = value;
		});
		break;
	default:
		processAllPixelsRgb(image, [](Color::Rgb& pixel){}); // make no changes
	}
}

void createMaskFromAlpha(sf::Image& image)
{
	processAllPixelsColor(image, [](sf::Color& pixel)
	{
		pixel.r = pixel.a;
		pixel.g = pixel.a;
		pixel.b = pixel.a;
		pixel.a = 255;
	});
}

void invert(sf::Image& image)
{
	processAllPixelsRgb(image, [](Color::Rgb& pixel)
	{
		pixel.r = 1.0 - pixel.r;
		pixel.g = 1.0 - pixel.g;
		pixel.b = 1.0 - pixel.b;
	});
}

void setAlpha(sf::Image& image, const unsigned char alpha)
{
	processAllPixelsColor(image, [&alpha](sf::Color& pixel)
	{
		pixel.a = alpha;
	});
}

void invertAlpha(sf::Image& image)
{
	processAllPixelsColor(image, [](sf::Color& pixel)
	{
		pixel.a = 255 - pixel.a;
	});
}

void makeOpaque(sf::Image& image)
{
	processAllPixelsColor(image, [](sf::Color& pixel)
	{
		pixel.a = 255;
	});
}

void clearWithColorButRetainTransparency(sf::Image& image, const sf::Color color)
{
	processAllPixelsColor(image, [&color](sf::Color& pixel)
	{
		pixel.r = color.r;
		pixel.g = color.g;
		pixel.b = color.b;
		// or: color.a = pixel.a; pixel = color;
	});
}

void setRedFromChannel(sf::Image& image, const Channel& channel)
{
	if (image.getSize() != channel.getSize())
		throw Exception(exceptionPrefix + "Cannot set image red from channel. Sizes do not match.");
	channel.copyToImage(image, ColorChannel::Red);
}

void setGreenFromChannel(sf::Image& image, const Channel& channel)
{
	if (image.getSize() != channel.getSize())
		throw Exception(exceptionPrefix + "Cannot set image green from channel. Sizes do not match.");
	channel.copyToImage(image, ColorChannel::Green);
}

void setBlueFromChannel(sf::Image& image, const Channel& channel)
{
	if (image.getSize() != channel.getSize())
		throw Exception(exceptionPrefix + "Cannot set image blue from channel. Sizes do not match.");
	channel.copyToImage(image, ColorChannel::Blue);
}

void setRgbFromChannel(sf::Image& image, const Channel& channel)
{
	if (image.getSize() != channel.getSize())
		throw Exception(exceptionPrefix + "Cannot set image rgb from channel. Sizes do not match.");
	channel.copyToImage(image, ColorChannel::Rgb);
}

void setAlphaFromChannel(sf::Image& image, const Channel& channel)
{
	if (image.getSize() != channel.getSize())
		throw Exception(exceptionPrefix + "Cannot set image alpha from channel. Sizes do not match.");
	channel.copyToImage(image, ColorChannel::Alpha);
}

void setAlphaFromMask(sf::Image& image, const Channel& mask)
{
	if (image.getSize() != mask.getSize())
		throw Exception(exceptionPrefix + "Cannot set image alpha from mask. Sizes do not match.");
	mask.copyToImage(image, ColorChannel::Alpha);
}

	} // namspace Image
} // namespace plinth
