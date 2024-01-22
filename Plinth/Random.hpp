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

#ifndef PLINTH_RANDOM_HPP
#define PLINTH_RANDOM_HPP

#include "Common.hpp"
#include <random>
#include "Generic.hpp"
#include "Range.hpp"

namespace plinth
{

class Random
{
public:
	template <class T>
	static T value(T min, T max);
	template <class T, class U>
	static T value(T min, U max);
	template <class T>
	static T value(const Range<T>& range);

	static std::size_t rand(std::size_t rangeSize);
	static bool chance(std::size_t samplePoints, std::size_t sampleSpace);

	template <class SeedT>
	static void seed(SeedT seed);
	static void randomSeed();

	static std::mt19937& getGenerator();







private:
	static std::mt19937 m_generator;

	static float priv_value(float min, float max);
	static double priv_value(double min, double max);
	static long double priv_value(long double min, long double max);
	template <class IntegerT>
	static IntegerT priv_value(IntegerT min, IntegerT max);
};

} // namespace plinth
#include "Random.inl"
#endif // PLINTH_RANDOM_HPP
