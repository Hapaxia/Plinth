#ifndef PLINTH_SFML_ERRBLOCKER_HPP
#define PLINTH_SFML_ERRBLOCKER_HPP

#include "Common.hpp"
#include <SFML/System/Err.hpp>
#include <ios>

namespace plinth
{
	namespace Sfml
	{

class ErrBlocker
{
public:
	ErrBlocker()
		: m_sfErrIoState(sf::err().rdstate())
	{
		sf::err().clear(std::ios::failbit);
	}
	~ErrBlocker()
	{
		sf::err().clear(m_sfErrIoState);
	}

private:
	std::ios_base::iostate m_sfErrIoState;
};

	} // namespace Sfml
} // namespace plinth
#endif // PLINTH_SFML_ERRBLOCKER_HPP
