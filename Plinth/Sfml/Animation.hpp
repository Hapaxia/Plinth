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

#ifndef PLINTH_SFML_ANIMATION_HPP
#define PLINTH_SFML_ANIMATION_HPP

#include "Common.hpp"
#include "AnimationTracks.hpp"

namespace plinth
{
	namespace Animation
	{

struct Transformable
{
	TrackVector2<float> position;
	Track<float> rotation;
	TrackVector2<float> scale;
	TrackVector2<float> origin;
};

struct Sprite : public Transformable
{
	TrackRect<int> textureRect;
	TrackColor color;
	Track<unsigned int> textureId;
};

struct Text : public Transformable
{
	Track<unsigned int> characterSize;
	TrackColor color;
	Track<unsigned int> style;
	Track<unsigned int> fontId;
	Track<unsigned int> stringId;
	Track<unsigned int> substringOffset;
	Track<unsigned int> substringLength;
};

struct Shape : public Transformable
{
	TrackColor fillColor;
	TrackColor outlineColor;
	Track<float> outlineThickness;
	Track<int> textureId;
};

struct CircleShape : public Shape
{
	Track<float> radius;
	Track<unsigned int> pointCount;
};

struct RectangleShape : public Shape
{
	TrackVector2<float> size;
};

struct ConvexShape : public Shape
{
	Track<unsigned int> pointCount;
};

struct Texture
{
	Track<unsigned int> smooth;
	Track<unsigned int> repeated;
};

struct View
{
	TrackVector2<float> center;
	TrackVector2<float> size;
	Track<float> rotation;
	TrackRect<float> viewport;
};

	} // namespace Animation
} // namespace plinth
//#include "Animation.inl"
#endif // PLINTH_SFML_ANIMATION_HPP
