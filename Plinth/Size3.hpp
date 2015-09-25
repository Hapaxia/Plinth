#ifndef PLINTH_SIZE3_HPP
#define PLINTH_SIZE3_HPP

namespace plinth
{

template <class T>
struct Size3
{
	T width, height, depth;
	inline T getVolume() const { return width * height * depth; };
};

using Size3u = Size3<unsigned int>;
using Size3d = Size3<double>;

} // namespace plinth
#endif // PLINTH_SIZE3_HPP
