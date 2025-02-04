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

#include "Common.hpp"
#include <random>
#include "Generic.hpp"
#include "Range.hpp"

namespace plinth
{

	namespace Random
	{

template <class T>
inline T value(T min, T max);
template <class T, class U>
inline T value(T min, U max);
template <class T>
inline T value(const Range<T>& range);

inline std::size_t rand(std::size_t rangeSize);
inline bool chance(std::size_t samplePoints, std::size_t sampleSpace);

template <class SeedT>
inline void seed(SeedT seed);
inline void randomSeed();

inline std::mt19937& getGenerator();





		namespace impl
		{

static std::mt19937 randomGeneratorEngine;

inline float randomValue(float min, float max);
inline double randomValue(double min, double max);
inline long double randomValue(long double min, long double max);
template <class IntegerT>
inline IntegerT randomValue(IntegerT min, IntegerT max);

	} // namespace Random
		} // namespace impl

} // namespace plinth
#include "Random.inl"
