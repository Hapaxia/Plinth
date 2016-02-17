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

#include "Random.hpp"

namespace plinth
{

Random::Random()
	: m_min(0u)
	, m_max(100u)
{
	randomSeed();
}

Random::Random(const unsigned int min, const unsigned int max)
	: m_min(min)
	, m_max(max)
{
	randomSeed();
}

unsigned int Random::rand(const unsigned int rangeSize)
{
	if (rangeSize == 0u)
		return 0u;
	return std::uniform_int_distribution<unsigned int>{0u, rangeSize - 1}(m_generator);
}

bool Random::chance(const unsigned int samplePoints, const unsigned int sampleSpace)
{
	return value(1u, sampleSpace) <= samplePoints;
}

unsigned int Random::value()
{
	return value(m_min, m_max);
}

void Random::setMinimum(const unsigned int min)
{
	m_min = min;
	orderLowHigh(m_min, m_max);
}

void Random::setMaximum(const unsigned int max)
{
	m_max = max;
	orderLowHigh(m_min, m_max);
}

void Random::setRange(const unsigned int min, const unsigned int max)
{
	setMinimum(min);
	setMaximum(max);
}

void Random::randomSeed()
{
	std::random_device rd;
	m_generator.seed(rd());
}

float Random::priv_value(float min, float max)
{
	orderLowHigh(min, max);
	return std::uniform_real_distribution<float>{min, max}(m_generator);
}

double Random::priv_value(double min, double max)
{
	orderLowHigh(min, max);
	return std::uniform_real_distribution<double>{min, max}(m_generator);
}

long double Random::priv_value(long double min, long double max)
{
	orderLowHigh(min, max);
	return std::uniform_real_distribution<long double>{min, max}(m_generator);
}

} // namespace plinth
