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

#include "TextureAtlas.hpp"

namespace plinth
{

inline TextureAtlas::TextureAtlas()
	: frames{}
{
}

inline std::vector<TextureAtlas::Frame*> TextureAtlas::getAllFrames()
{
	std::vector<TextureAtlas::Frame*> pFrames;
	pFrames.reserve(frames.size());
	for (auto& frame : frames)
		pFrames.push_back(&frame);
	return pFrames;
}

inline std::vector<TextureAtlas::Frame*> TextureAtlas::getAllFramesInCategory(const std::size_t category)
{
	std::vector<TextureAtlas::Frame*> pFrames;
	for (auto& frame : frames)
	{
		if (frame.category == category)
			pFrames.push_back(&frame);
	}
	return pFrames;
}

inline std::vector<TextureAtlas::Frame*> TextureAtlas::getAllFramesWithTextureIndex(const std::size_t textureIndex)
{
	std::vector<TextureAtlas::Frame*> pFrames;
	for (auto& frame : frames)
	{
		if (frame.textureIndex == textureIndex)
			pFrames.push_back(&frame);
	}
	return pFrames;
}

inline std::vector<TextureAtlas::Frame*> TextureAtlas::getAllFrameInCategoryWithTextureIndex(const std::size_t category, const std::size_t textureIndex)
{
	std::vector<TextureAtlas::Frame*> pFrames;
	for (auto& frame : frames)
	{
		if ((frame.category == category) && (frame.textureIndex == textureIndex))
			pFrames.push_back(&frame);
	}
	return pFrames;
}

} // namespace plinth
