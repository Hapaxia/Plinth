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

#include "FrameSequence.hpp"

#include <SFML/Graphics/PrimitiveType.hpp>

namespace
{

const sf::PrimitiveType primitiveType{ sf::PrimitiveType::TrianglesStrip };
const unsigned int numberOfVertices{ 4u };

int intFromFloor(const float& f)
{
	return static_cast<int>(std::floor(f) + (f < 0.f ? -0.5f : 0.5f));
}

} // namespace

namespace plinth
{

FrameSequence::FrameSequence()
	: m_frames()
	, m_position(0.f)
	//, m_initialFrame(0)
	, m_loopType(LoopType::Cycle)
{
}

void FrameSequence::setLoopType(LoopType loopType)
{
	m_loopType = loopType;
}

FrameSequence::LoopType FrameSequence::getLoopType() const
{
	return m_loopType;
}

void FrameSequence::setReverse(const bool reverse)
{
	m_reverse = reverse;
}

bool FrameSequence::getReverse() const
{
	return m_reverse;
}

void FrameSequence::add(const std::vector<Frame>& frames)
{
	m_frames.insert(m_frames.end(), frames.begin(), frames.end());
}

void FrameSequence::add(const Frame& frame)
{
	m_frames.push_back(frame);
}

void FrameSequence::removeAllWithExhibit(const unsigned int exhibit)
{
	m_frames.erase(std::remove_if(m_frames.begin(), m_frames.end(), [&exhibit](const Frame& frame) { return frame.id == exhibit; }));
}

void FrameSequence::set(const unsigned int position, const Frame& frame)
{
	m_frames[position] = frame;
}

void FrameSequence::add(const unsigned int position, const Frame& frame)
{
	m_frames.insert(m_frames.begin() + position, frame);
}

void FrameSequence::remove(const unsigned int position)
{
	m_frames.erase(m_frames.begin() + position);
}

void FrameSequence::clear()
{
	m_frames.clear();
}

unsigned int FrameSequence::getNumberOfFrames() const
{
	return m_frames.size();
}

FrameSequence::Frame FrameSequence::get(const unsigned int position) const
{
	return m_frames[priv_getResolvedPosition(position)];
}

FrameSequence::Frame FrameSequence::get(const float position) const
{
	return m_frames[priv_getResolvedPosition(intFromFloor(position))];
}

FrameSequence::Frame FrameSequence::get() const
{
	return m_frames[priv_getResolvedPosition(intFromFloor(m_position))];
}

void FrameSequence::setPosition(const float position)
{
	m_position = position;
}

float FrameSequence::getPosition() const
{
	return m_position;
}

void FrameSequence::setTime(const sf::Time time)
{
	m_position = priv_getPositionFromTime(time);
}

sf::Time FrameSequence::getTime() const
{
	return priv_getTimeFromPosition(m_position);
}

FrameSequence& FrameSequence::operator++()
{
	++m_position;

	return *this;
}

FrameSequence& FrameSequence::operator--()
{
	--m_position;

	return *this;
}

void FrameSequence::operator+=(const unsigned int numberOfFrames)
{
	m_position += numberOfFrames;
}

void FrameSequence::operator-=(const unsigned int numberOfFrames)
{
	m_position -= numberOfFrames;
}

void FrameSequence::operator+=(const float positionOffset)
{
	m_position += positionOffset;
}

void FrameSequence::operator-=(const float positionOffset)
{
	m_position -= positionOffset;
}

void FrameSequence::operator+=(const sf::Time time)
{
	m_position = priv_getPositionFromTime(priv_getTimeFromPosition(m_position) + time);
}

void FrameSequence::operator-=(const sf::Time time)
{
	m_position = priv_getPositionFromTime(priv_getTimeFromPosition(m_position) - time);
}



// PRIVATE

unsigned int FrameSequence::priv_getResolvedPosition(int position) const
{
	if (m_frames.size() == 0)
		return 0u;

	const unsigned int size{ m_frames.size() };
	const unsigned int maxPosition{ size - 1 };

	switch (m_loopType)
	{
	case LoopType::PingPong:
		if (position < 0)
			position = -position;
		// maxPosition is used here instead of size so that the end steps are not duplicated (maxPosition is size - 1)
		if (position % (maxPosition * 2) < maxPosition)
			position %= maxPosition;
		else
			position = maxPosition - (position % maxPosition);
		break;
	case LoopType::Cycle:
		position %= size;
		break;
	case LoopType::None:
	default:
		if (position < 0)
			position = 0;
		else if (position > static_cast<int>(maxPosition))
			position = maxPosition;
	}

	return m_reverse ? maxPosition - position : position;
}

float FrameSequence::priv_getPositionFromTime(sf::Time time) const
{
	float position{ 0.f };
	float positionRepeatOffset{ 0.f };
	float timeRepeats{ 0.f };

	sf::Time totalTime;
	for (const auto& frame : m_frames)
		totalTime += frame.delay;

	LoopType loopType{ m_loopType };
	if (m_frames.size() < 2)
		loopType = LoopType::None;
	else if (m_frames.size() < 3 && loopType == LoopType::PingPong)
		loopType = LoopType::Cycle;

	switch (loopType)
	{
	case LoopType::PingPong:
	{
		const sf::Time entireTotalTime{ totalTime * 2.f - m_frames.front().delay - m_frames.back().delay };
		timeRepeats = std::floor(time / entireTotalTime);
		time -= timeRepeats * entireTotalTime; // effectively modulo result (time % entireTotalTime)
		bool complete{ false };
		for (const auto& frame : m_frames)
		{
			if (time <= frame.delay)
			{
				position += time / frame.delay;
				complete = true;
				break; // for loop
			}
			time -= frame.delay;
			++position;
		}
		if (!complete)
		{
			// ping pong return pass (skips first and last frame to avoid duplicating end frames)
			for (std::vector<Frame>::const_reverse_iterator begin = m_frames.rbegin(), end = m_frames.rend(), it = begin; it != end - 1; ++it)
			{
				if (it == begin)
					continue;

				if (time <= it->delay)
				{
					position += time / it->delay;
					break; // for loop
				}
				time -= it->delay;
				++position;
			}
		}
		positionRepeatOffset = timeRepeats * (m_frames.size() * 2 - 2);
	}
	break;
	case LoopType::Cycle:
	case LoopType::None:
		timeRepeats = std::floor(time / totalTime);
		time -= timeRepeats * totalTime; // effectively modulo result (time % totalTime)
		for (const auto& frame : m_frames)
		{
			if (time <= frame.delay)
			{
				position += time / frame.delay;
				break; // for loop
			}
			time -= frame.delay;
			++position;
		}
		positionRepeatOffset = timeRepeats * m_frames.size();
		break;
	default:
		;
	}

	return positionRepeatOffset + position;
}

sf::Time FrameSequence::priv_getTimeFromPosition(float position) const
{
	sf::Time time{ sf::Time::Zero };
	float positionRepeats{ 0.f };
	sf::Time timeRepeatOffset{ sf::Time::Zero };

	sf::Time totalTime;
	for (const auto& frame : m_frames)
		totalTime += frame.delay;

	LoopType loopType{ m_loopType };
	if (m_frames.size() < 2) // no need to loop with a single frame (or none)
		loopType = LoopType::None;
	else if (m_frames.size() < 3 && loopType == LoopType::PingPong) // ping pong with two frames is identical to a cycle
		loopType = LoopType::Cycle;

	switch (loopType)
	{
	case LoopType::PingPong:
	{
		const unsigned int pingPongFrames{ m_frames.size() * 2 - 2 };
		positionRepeats = std::floor(position / pingPongFrames);
		position -= positionRepeats * pingPongFrames; // effectively modulo result (position % m_frames.size())

		bool complete{ false };
		for (const auto& frame : m_frames)
		{
			if (position <= 1)
			{
				time += frame.delay * position;
				complete = true;
				break; // for loop
			}
			--position;
			time += frame.delay;
		}
		if (!complete)
		{
			// ping pong return pass (skips first and last frame to avoid duplicating end frames)
			for (std::vector<Frame>::const_reverse_iterator begin = m_frames.rbegin(), end = m_frames.rend(), it = begin; it != end - 1; ++it)
			{
				if (it == begin)
					continue;

				if (position <= 1)
				{
					time += it->delay * position;
					break; // for loop
				}
				--position;
				time += it->delay;
			}
		}
		const sf::Time entireTotalTime{ totalTime * 2.f - m_frames.front().delay - m_frames.back().delay };
		timeRepeatOffset = positionRepeats * entireTotalTime;
	}
	break;
	case LoopType::Cycle:
	case LoopType::None:
		positionRepeats = std::floor(position / m_frames.size());
		position -= positionRepeats * m_frames.size(); // effectively modulo result (position % m_frames.size())
		for (const auto& frame : m_frames)
		{
			if (position <= 1)
			{
				time += frame.delay * position;
				break; // for loop
			}
			--position;
			time += frame.delay;
		}
		timeRepeatOffset = positionRepeats * totalTime;
		break;
	default:
		;
	}

	return timeRepeatOffset + time;
}

} // namespace plinth
