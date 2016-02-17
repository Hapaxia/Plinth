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

#ifndef PLINTH_RANDOM_HPP
#define PLINTH_RANDOM_HPP

#include "Common.hpp"
#include <random>
#include "Generic.hpp"

namespace plinth
{

class Random
{
public:
	Random();
	Random(unsigned int min, unsigned int max);

	unsigned int rand(unsigned int rangeSize);

	bool chance(unsigned int samplePoints, unsigned int sampleSpace);

	unsigned int value();

	template <class T>
	T value(T min, T max) { return priv_value(min, max); }

	void setMinimum(unsigned int min);
	void setMaximum(unsigned int max);
	void setRange(unsigned int min, unsigned int max);

	template <class seedT>
	void seed(seedT seed) { m_generator.seed(seed); };

	void randomSeed();

private:
	std::mt19937 m_generator;
	unsigned int m_min, m_max;

	float priv_value(float min, float max);
	double priv_value(double min, double max);
	long double priv_value(long double min, long double max);
	template <class T>
	T priv_value(T min, T max);
};

template <class T>
T Random::priv_value(T min, T max)
{
	orderLowHigh(min, max);
	return static_cast<T>(std::uniform_int_distribution<long long int>{static_cast<long long int>(min), static_cast<long long int>(max)}(m_generator));
}

} // namespace plinth
#endif // PLINTH_RANDOM_HPP
