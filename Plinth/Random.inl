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

#include "Random.hpp"

namespace plinth
{

template<class T>
inline T Random::value(const T min, const T max)
{
	return impl::randomValue(min, max);
}

template<class T, class U>
inline T Random::value(const T min, const U max)
{
	return impl::randomValue(min, static_cast<T>(max));
}

template<class T>
inline T Random::value(const Range<T>& range)
{
	return impl::randomValue(range.min, range.max);
}

template<class SeedT>
inline void Random::seed(const SeedT seed)
{
	impl::randomGeneratorEngine.seed(seed);
}

inline std::size_t Random::rand(const std::size_t rangeSize)
{
	return (rangeSize == 0_uz) ? 0_uz : std::uniform_int_distribution<std::size_t>{ 0_uz, rangeSize - 1_uz }(impl::randomGeneratorEngine);
}

inline bool Random::chance(const std::size_t samplePoints, const std::size_t sampleSpace)
{
	return value(1_uz, sampleSpace) <= samplePoints;
}

inline void Random::randomSeed()
{
	std::random_device rd;
	impl::randomGeneratorEngine.seed(rd());
}

inline std::mt19937& Random::getGenerator()
{
	return impl::randomGeneratorEngine;
}






	namespace Random
	{
		namespace impl
		{

template <class IntegerT>
inline IntegerT randomValue(IntegerT min, IntegerT max)
{
	orderLowHigh(min, max);
	return static_cast<IntegerT>(std::uniform_int_distribution<long long int>{ static_cast<long long int>(min), static_cast<long long int>(max) }(randomGeneratorEngine));
}

inline float randomValue(float min, float max)
{
	orderLowHigh(min, max);
	return std::uniform_real_distribution<float>{ min, max }(randomGeneratorEngine);
}

inline double randomValue(double min, double max)
{
	orderLowHigh(min, max);
	return std::uniform_real_distribution<double>{ min, max }(randomGeneratorEngine);
}

inline long double randomValue(long double min, long double max)
{
	orderLowHigh(min, max);
	return std::uniform_real_distribution<long double>{ min, max }(randomGeneratorEngine);
}

		} // namespace impl
	} // namespace Random
} // namespace plinth
