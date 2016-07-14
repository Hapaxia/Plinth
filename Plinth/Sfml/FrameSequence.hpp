//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2016 M.J.Silk
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

#ifndef PLINTH_SFML_FRAMESEQUENCE_HPP
#define PLINTH_SFML_FRAMESEQUENCE_HPP

#include "Common.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace plinth
{

// Frame Sequence v1.0.0
class FrameSequence
{
public:
	enum class LoopType
	{
		None,
		Cycle,
		PingPong,
	};

	struct Frame
	{
		unsigned int id; // exhibit number when used with Gallery Sprite
		sf::Vector2f offset;
		sf::Vector2f scale;
		float rotation;
		bool flipX;
		bool flipY;
		sf::Time delay; // default to 1/12 of a seconds, which would be a rate of 12 FPS

		Frame(unsigned int newId, sf::Vector2f newOffset = { 0.f, 0.f }, sf::Vector2f newScale = { 1.f, 1.f }, float newRotation = 0.f, bool newFlipX = false, bool newFlipY = false, sf::Time newDelay = sf::seconds(1.f / 12.f))
			: id(newId), offset(newOffset), scale(newScale), rotation(newRotation), flipX(newFlipX), flipY(newFlipY), delay(newDelay)
		{ }
	};

	FrameSequence();
	void setLoopType(LoopType loopType);
	LoopType getLoopType() const;
	void setReverse(bool reverse);
	bool getReverse() const;
	void add(const std::vector<Frame>& frames); // adds multiple frames to end of group
	void add(const Frame& frame); // adds frame to end of group
	void add(unsigned int position, const Frame& frame); // add frame at position (inserts before the frame currently at that position)
	void set(unsigned int position, const Frame& frame); // changes the frame at position
	void remove(unsigned int position); // removes frame at position
	void removeAllWithExhibit(unsigned int exhibit); // removes all instances of exhibit in group
	void clear(); // removes all frames
	unsigned int getNumberOfFrames() const;
	Frame get(unsigned int position) const;
	Frame get(float position) const;
	Frame get() const;
	void setPosition(float position);
	float getPosition() const;
	void setTime(sf::Time time); // not yet implemented
	sf::Time getTime() const; // not yet implemented

	FrameSequence& operator++(); // prefix only
	FrameSequence& operator--(); // prefix only

	void operator+=(unsigned int numberOfFrames);
	void operator-=(unsigned int numberOfFrames);
	void operator+=(float positionOffset);
	void operator-=(float positionOffset);
	void operator+=(sf::Time time);
	void operator-=(sf::Time time);

private:
	std::vector<Frame> m_frames;
	float m_position;
	//unsigned int m_initialFrame;
	LoopType m_loopType;
	bool m_reverse;

	unsigned int priv_getResolvedPosition(int position) const;
	float priv_getPositionFromTime(sf::Time time) const;
	sf::Time priv_getTimeFromPosition(float position) const;
};


} // namespace plinth
#endif // PLINTH_SFML_FRAMESEQUENCE_HPP
