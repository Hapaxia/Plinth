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
#include "Random.hpp"
#include "Generic.hpp"
#include "Range.hpp"

namespace plinth
{

template <class T = int>
class RandomDistribution
{
public:
	RandomDistribution(T max);
	RandomDistribution(T min, T max);
	RandomDistribution(const Range<T>& range);

	T value() const;

	void setRange(T min, T max);
	void setRange(const Range<T>& range);
	Range<T> getRange() const;







private:
	Range<T> m_range;
	std::uniform_int_distribution<T>* m_intDistribution;
	std::uniform_real_distribution<T>* m_realDistribution;

	void priv_updateDistribution();
	T priv_value() const;
};

} // namespace plinth
#include "RandomDistribution.inl"
