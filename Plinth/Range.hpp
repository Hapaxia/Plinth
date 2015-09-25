#ifndef PLINTH_RANGE_HPP
#define PLINTH_RANGE_HPP

namespace plinth
{

enum class RangeBoundaries
{
	None,
	Min,
	Max,
	Both
};

template<class T>
struct Range
{
	T min;
	T max;
	inline void set(const T& newMin, const T& newMax) { min = newMin; max = newMax; }
	inline T getSize() { order(); return max - min; }
	inline void order() { orderLowHigh(min, max); }
	inline bool isClosed() { return min == max; }
};

} // namespace plinth
#endif // PLINTH_RANGE_HPP
