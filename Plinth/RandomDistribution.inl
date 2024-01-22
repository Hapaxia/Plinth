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

#ifndef PLINTH_RANDOMDISTRIBUTION_INL
#define PLINTH_RANDOMDISTRIBUTION_INL

#include "RandomDistribution.hpp"

namespace plinth
{

template <class T>
inline RandomDistribution<T>::RandomDistribution(const T max)
	: m_range{ static_cast<T>(0), max }
	, m_intDistribution{ nullptr }
	, m_realDistribution{ nullptr }
{
	priv_updateDistribution();
}

template <class T>
inline RandomDistribution<T>::RandomDistribution(const T min, const T max)
	: m_range{ min, max }
{
	priv_updateDistribution();
}

template <class T>
inline RandomDistribution<T>::RandomDistribution(const Range<T>& range)
	: m_range{ range }
{
	priv_updateDistribution();
}

template <class T>
inline T RandomDistribution<T>::value() const
{
	return priv_value();
}

template <class T>
inline void RandomDistribution<T>::setRange(const T min, const T max)
{
	m_range = { min, max };
	priv_updateDistribution();
}

template <class T>
inline void RandomDistribution<T>::setRange(const Range<T>& range)
{
	m_range = range;
	priv_updateDistribution();
}

template <class T>
inline Range<T> RandomDistribution<T>::getRange() const
{
	return m_range;
}








// PRIVATE
template <class T>
inline void RandomDistribution<T>::priv_updateDistribution()
{
	m_range.order();
	if (m_intDistribution != nullptr)
		delete m_intDistribution;
	m_intDistribution = new std::uniform_int_distribution<T>{ m_range.min, m_range.max };
}
template <>
inline void RandomDistribution<float>::priv_updateDistribution()
{
	m_range.order();
	if (m_realDistribution != nullptr)
		delete m_realDistribution;
	m_realDistribution = new std::uniform_real_distribution<float>{ m_range.min, m_range.max };
}
template <>
inline void RandomDistribution<double>::priv_updateDistribution()
{
	m_range.order();
	if (m_realDistribution != nullptr)
		delete m_realDistribution;
	m_realDistribution = new std::uniform_real_distribution<double>{ m_range.min, m_range.max };
}
template <>
inline void RandomDistribution<long double>::priv_updateDistribution()
{
	m_range.order();
	if (m_realDistribution != nullptr)
		delete m_realDistribution;
	m_realDistribution = new std::uniform_real_distribution<long double>{ m_range.min, m_range.max };
}

template <class T>
inline T RandomDistribution<T>::priv_value() const
{
	return (*m_intDistribution)(Random::getGenerator());
}
template <>
inline float RandomDistribution<float>::priv_value() const
{
	return (*m_realDistribution)(Random::getGenerator());
}
template <>
inline double RandomDistribution<double>::priv_value() const
{
	return (*m_realDistribution)(Random::getGenerator());
}
template <>
inline long double RandomDistribution<long double>::priv_value() const
{
	return (*m_realDistribution)(Random::getGenerator());
}

} // namespace plinth

#endif // PLINTH_RANDOMDISTRIBUTION_INL
