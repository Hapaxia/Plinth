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
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace plinth
{

class TextureAtlas
{
public:
	struct Frame
	{
		sf::IntRect rect{};
		sf::Vector2i origin{};
		std::size_t textureIndex{};
		std::size_t category{};
		enum class RotateFlip
		{
			None = 0u,
			Rotate          = 1u << 0u,
			FlipX           = 1u << 1u,
			FlipY           = 1u << 2u, // 3 bits
		} rotateFlip{ RotateFlip::None };
	};

	std::vector<Frame> frames;

	TextureAtlas();

	std::vector<Frame*> getAllFrames();
	std::vector<Frame*> getAllFramesInCategory(std::size_t category);
	std::vector<Frame*> getAllFramesWithTextureIndex(std::size_t textureIndex);
	std::vector<Frame*> getAllFrameInCategoryWithTextureIndex(std::size_t category, std::size_t textureIndex);
};

MAKE_ENUM_BITWISE(TextureAtlas::Frame::RotateFlip);

} // namespace plinth
#include "TextureAtlas.inl"
