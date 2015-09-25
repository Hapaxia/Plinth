#ifndef PLINTH_SIZE2_HPP
#define PLINTH_SIZE2_HPP

namespace plinth
{

template <class T>
struct Size2
{
	T width, height;
	inline T getArea() const { return width * height; };
};

using Size2u = Size2<unsigned int>;
using Size2d = Size2<double>;

} // namespace plinth
#endif // PLINTH_SIZE2_HPP
