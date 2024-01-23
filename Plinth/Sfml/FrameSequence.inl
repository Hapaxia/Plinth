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

#include "FrameSequence.hpp"

namespace plinth
{

inline FrameSequence::FrameSequence()
	: m_primitiveType{ sf::PrimitiveType::TrianglesStrip }
	, m_numberOfVertices{ 4_uz }
	, m_frames{}
	, m_position{ 0.f }
	, m_reverse{ false }
	, m_loopType{ LoopType::Cycle }
{
}

inline void FrameSequence::setLoopType(LoopType loopType)
{
	m_loopType = loopType;
}

inline FrameSequence::LoopType FrameSequence::getLoopType() const
{
	return m_loopType;
}

inline void FrameSequence::setReverse(const bool reverse)
{
	m_reverse = reverse;
}

inline bool FrameSequence::getReverse() const
{
	return m_reverse;
}

inline void FrameSequence::add(const std::vector<Frame>& frames)
{
	m_frames.insert(m_frames.end(), frames.begin(), frames.end());
}

inline void FrameSequence::add(const Frame& frame)
{
	m_frames.push_back(frame);
}

inline void FrameSequence::removeAllWithFrameId(const std::size_t frameId)
{
	m_frames.erase(std::remove_if(m_frames.begin(), m_frames.end(), [&frameId](const Frame& frame) { return frame.id == frameId; }));
}

inline void FrameSequence::set(const std::size_t position, const Frame& frame)
{
	m_frames[position] = frame;
}

inline void FrameSequence::add(const std::size_t position, const Frame& frame)
{
	m_frames.insert(m_frames.begin() + position, frame);
}

inline void FrameSequence::remove(const std::size_t position)
{
	m_frames.erase(m_frames.begin() + position);
}

inline void FrameSequence::clear()
{
	m_frames.clear();
}

inline std::size_t FrameSequence::getNumberOfFrames() const
{
	return m_frames.size();
}

inline FrameSequence::Frame FrameSequence::get(const std::size_t position) const
{
	return m_frames[priv_getResolvedPosition(static_cast<long long int>(position))];
}

inline FrameSequence::Frame FrameSequence::get(const float position) const
{
	return m_frames[priv_getResolvedPosition(static_cast<long long int>(std::lround(std::floor(position))))];
}

inline FrameSequence::Frame FrameSequence::get() const
{
	return m_frames[priv_getResolvedPosition(static_cast<long long int>(std::lround(std::floor(m_position))))];
}

inline void FrameSequence::setPosition(const float position)
{
	m_position = position;
}

inline float FrameSequence::getPosition() const
{
	return m_position;
}

inline void FrameSequence::setTime(const sf::Time time)
{
	m_position = priv_getPositionFromTime(time);
}

inline sf::Time FrameSequence::getTime() const
{
	return priv_getTimeFromPosition(m_position);
}

inline FrameSequence& FrameSequence::operator++()
{
	++m_position;

	return *this;
}

inline FrameSequence& FrameSequence::operator--()
{
	--m_position;

	return *this;
}

inline void FrameSequence::operator+=(const std::size_t numberOfFrames)
{
	m_position += numberOfFrames;
}

inline void FrameSequence::operator-=(const std::size_t numberOfFrames)
{
	m_position -= numberOfFrames;
}

inline void FrameSequence::operator+=(const float positionOffset)
{
	m_position += positionOffset;
}

inline void FrameSequence::operator-=(const float positionOffset)
{
	m_position -= positionOffset;
}

inline void FrameSequence::operator+=(const sf::Time time)
{
	m_position = priv_getPositionFromTime(priv_getTimeFromPosition(m_position) + time);
}

inline void FrameSequence::operator-=(const sf::Time time)
{
	m_position = priv_getPositionFromTime(priv_getTimeFromPosition(m_position) - time);
}



// PRIVATE

inline std::size_t FrameSequence::priv_getResolvedPosition(long long int position) const
{
	if (m_frames.empty())
		return 0_uz;

	const std::size_t size{ m_frames.size() };
	const long long int maxPosition{ static_cast<long long int>(size - 1_uz) };

	switch (m_loopType)
	{
	case LoopType::PingPong:
		if (position < 0)
			position = -position;
		// maxPosition is used here instead of size so that the end steps are not duplicated (maxPosition is size - 1)
		if ((position % (maxPosition * 2)) < maxPosition)
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
		else if (position > maxPosition)
			position = maxPosition;
	}

	return static_cast<std::size_t>(m_reverse ? (maxPosition - position) : position);
}

inline float FrameSequence::priv_getPositionFromTime(sf::Time time) const
{
	const sf::Time totalTime{ priv_getTotalTime()};
	const LoopType loopType{ priv_getLoopTypeToUse() };

	float position{ 0.f };
	float positionRepeatOffset{ 0.f };
	float timeRepeats{ 0.f };

	switch (loopType)
	{
	case LoopType::PingPong:
	{
		const sf::Time entireTotalTime{ (totalTime * 2.f) - (m_frames.front().delay + m_frames.back().delay) };
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
			for (std::vector<Frame>::const_reverse_iterator begin{ m_frames.rbegin() }, end{ m_frames.rend() }, it{ begin + 1_uz }; it != end - 1_uz; ++it)
			{
				if (time <= it->delay)
				{
					position += time / it->delay;
					break; // for loop
				}
				time -= it->delay;
				++position;
			}
		}
		positionRepeatOffset = timeRepeats * ((m_frames.size() * 2_uz) - 2_uz);
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

inline sf::Time FrameSequence::priv_getTimeFromPosition(float position) const
{
	const sf::Time totalTime{ priv_getTotalTime() };
	const LoopType loopType{ priv_getLoopTypeToUse() };

	sf::Time time{ sf::Time::Zero };
	sf::Time timeRepeatOffset{ sf::Time::Zero };
	float positionRepeats{ 0.f };

	switch (loopType)
	{
	case LoopType::PingPong:
	{
		const std::size_t pingPongFrames{ (m_frames.size() * 2_uz) - 2_uz };
		positionRepeats = std::floor(position / pingPongFrames);
		position -= positionRepeats * pingPongFrames; // effectively modulo result (position % pingPongFrames)

		bool complete{ false };
		for (const auto& frame : m_frames)
		{
			if (position <= 1.f)
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
			for (std::vector<Frame>::const_reverse_iterator begin{ m_frames.rbegin() }, end{ m_frames.rend() }, it{ begin + 1_uz }; it != end - 1_uz; ++it)
			{
				if (position <= 1.f)
				{
					time += it->delay * position;
					break; // for loop
				}
				--position;
				time += it->delay;
			}
		}
		const sf::Time entireTotalTime{ (totalTime * 2.f) - m_frames.front().delay - m_frames.back().delay };
		timeRepeatOffset = positionRepeats * entireTotalTime;
	}
		break;
	case LoopType::Cycle:
	case LoopType::None:
		positionRepeats = std::floor(position / m_frames.size());
		position -= positionRepeats * m_frames.size(); // effectively modulo result (position % m_frames.size())
		for (const auto& frame : m_frames)
		{
			if (position <= 1.f)
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

inline sf::Time FrameSequence::priv_getTotalTime() const
{
	sf::Time totalTime{ sf::Time::Zero };
	for (const auto& frame : m_frames)
		totalTime += frame.delay;
	return totalTime;
}

inline FrameSequence::LoopType FrameSequence::priv_getLoopTypeToUse() const
{
	LoopType loopType{ m_loopType };
	if (m_frames.size() < 2_uz) // no need to loop with a single frame (or none)
		loopType = LoopType::None;
	else if ((m_frames.size() < 3_uz) && (loopType == LoopType::PingPong)) // ping pong with two frames is identical to a cycle
		loopType = LoopType::Cycle;
	return loopType;
}

} // namespace plinth
